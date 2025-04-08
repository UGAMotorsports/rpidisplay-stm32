/*
 * rpi-display.c
 *
 *  Created on: Mar 10, 2025
 *      Author: bharg
 */

#include <stdint.h>
#include "gpio.h"
#include "spi.h"

#include "gfxfont.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

void startTransaction() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET);
}

void endTransaction() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, SET);
}

void dataOrRegister(uint8_t data) {
	if (data) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);
	} else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);
	}
}

void commandAndData(uint16_t command, uint16_t* data, unsigned int size) {
	startTransaction();

	dataOrRegister(0);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)(&command), 1, 10);

	if (size) {
		dataOrRegister(1);
		HAL_SPI_Transmit(&hspi1, (uint8_t*)data, size, 10);
	}

	endTransaction();
}

void startCommand(uint16_t command) {
	startTransaction();
	dataOrRegister(0);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)(&command), 1, 10);
}

void transmitRepeatedData(uint16_t data16, unsigned int count) {
	dataOrRegister(1);
	for (int i = 0; i < count; i++) {
		HAL_SPI_Transmit(&hspi1, (uint8_t*)(&data16), 1, 10);
	}
}

void transmitSingleData(uint16_t data16) {
	dataOrRegister(1);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)(&data16), 1, 10);
}

void endCommand() {
	endTransaction();
}

void resetScreen() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
	HAL_Delay(100);
}

void initializeScreen() {
	commandAndData(0x01, NULL, 0);
	commandAndData(0x11, NULL, 0);
	{
		uint16_t data[] = {0x0055};
		commandAndData(0x3A, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0019, 0x001a};
		commandAndData(0xC0, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0045, 0x0000};
		commandAndData(0xC1, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0033};
		commandAndData(0xC2, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0000, 0x0028};
		commandAndData(0xC5, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x00A0, 0x0011};
		commandAndData(0xB1, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0002};
		commandAndData(0xB4, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0000, 0x0042, 0x003B};
		commandAndData(0xB6, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x001F, 0x0025, 0x0022, 0x000B, 0x0006, 0x000A, 0x004E, 0x00C6, 0x0039, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
		commandAndData(0xE0, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x001F, 0x003F, 0x003F, 0x000F, 0x001F, 0x000F, 0x0046, 0x0049, 0x0031, 0x0005, 0x0009, 0x0003, 0x001C, 0x001A, 0x0000};
		commandAndData(0xE1, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0000, 0x0022};
		commandAndData(0xB6, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0008};
		commandAndData(0x36, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0000, 0x0000, (uint16_t)((SCREEN_WIDTH - 1) >> 8), (uint16_t)((SCREEN_WIDTH - 1) & 0xFF)};
		commandAndData(0x2A, data, sizeof(data));
	}
	{
		uint16_t data[] = {0x0000, 0x0000, (uint16_t)((SCREEN_HEIGHT - 1) >> 8), (uint16_t)((SCREEN_HEIGHT - 1) & 0xFF)};
		commandAndData(0x2B, data, sizeof(data));
	}
	{
		startCommand(0x2C);
		transmitRepeatedData(0x0000, 320 * 480);
		endCommand();
	}
	{
		commandAndData(0x29, NULL, 0);
	}
}

/**
 * Final pixel in row/column is one less than x2/y2
 */
void modifySpace(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	{
		y2 -= 1;
		uint16_t data[] = {y1 >> 8, y1 & 0xFF, y2 >> 8, y2 & 0xFF};
		commandAndData(0x2A, data, sizeof(data));
	}
	{
		x2 -= 1;
		uint16_t data[] = {x1 >> 8, x1 & 0xFF, x2 >> 8, x2 && 0xFF};
		commandAndData(0x2B, data, sizeof(data));
	}
}

/**
 * must be used in ocnjunction with modifySpace()
 */

void fillArea(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color) {
	modifySpace(x1, y1, x1 + length, y1 + height);
	startCommand(0x2C);
	transmitRepeatedData(color, length * height);
	endCommand();
}

void drawHLine(uint16_t x1, uint16_t y1, uint16_t length, uint16_t color) {
	fillArea(x1, y1, length, 1, color);
}

void drawVLine(uint16_t x1, uint16_t y1, uint16_t height, uint16_t color) {
	fillArea(x1, y1, 1, height, color);
}

void drawPoint(uint16_t x, uint16_t y, uint16_t color) {
	modifySpace(x, y, x, y);
	startCommand(0x2C);
	transmitSingleData(color);
	endCommand();

}


void drawRectangleFilled(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color) {
	fillArea(x1, y1, length, height, color);
}

void drawRectangleOutline(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color) {
	drawVLine(x1, y1, height, color);
	drawVLine(x1 + length, y1, height, color);
	drawHLine(x1, y1, length, color);
	drawHLine(x1, y1 + height, length, color);
}

/**
 * Will check to see if a given point is within a given ellipse. This is used to determine what pixels to draw when shading in ellipse.
 * @param cx This is the center x
 * @param cy center y
 * @param rx radius x
 * @param ry radius y
 * @param x x coord to check
 * @param y y coord to check
 * @return number that represents where your point lies (< 1 then in ellipse, > 1 then outside ellipse)
 */
int checkPointInEllipse(int cx, int cy, int rx, int ry, int x, int y) {
	int diffx = cx - x;
	int diffy = cy - y;
	int result = (diffy*diffy*rx*rx) + (diffx*diffx*ry*ry) - (rx*rx*ry*ry);
	return result;
}

/**
 * draws ellipse at given coordinates based on parameters
 */
void drawEllipseFilled(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color) {
	int rx = length / 2, ry = height / 2;
	int startx = x - (length/2), endx = x + (length/2), starty = y - (height/2), endy = y + (height/2);
	for (int i = startx; i < endx; i++) {
		for (int j = starty; j < endy; j++) {
			if (checkPointInEllipse(x, y, rx, ry, i, j) < 0) {
				int sliceHeight = height - (2 * (j - starty));
				drawVLine(i, j, sliceHeight, color);
				break;
			}
		}
	}
}

void drawEllipseOutline(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color) {
	int rx = length / 2, ry = height / 2;
	int startx = x - (length/2), starty = y - (height/2);
	int lastending = y;
	for (int i = startx; i < x; i++) {
		for (int j = lastending; j > starty - 1; j--) {
			if (checkPointInEllipse(x, y, rx, ry, i, j) > 0) {
				int lineheight = lastending - j + 1;
				drawVLine(i, j, lineheight, color); //2nd quadrant
				drawVLine(i, y + y - j - lineheight, lineheight, color); //3rd quadrant
				drawVLine(x + x - i, j, lineheight, color); //1st quadrant
				drawVLine(x + x - i, y + y - j - lineheight, lineheight, color); //4th quadrant
				lastending = j;
				break;
			}
		}
	}
}

//void drawCharacter(char letter, GFXfont* font, uint16_t xpos, uint16_t ypos) {
//	GFXglyph *toDraw = &((font->glyph)[letter - 32]);
//	uint8_t width = toDraw->width, height = toDraw->height;
//	uint8_t xo = toDraw->xOffset, yo = toDraw->yOffset;
//	uint8_t bitlist[] = font->bitmap;
//
//	uint16_t bo = toDraw->bitmapOffset;
//	uint8_t atbit = 0;
//	uint8_t atbyte = bitlist[bo];
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			if (!(atbit & 7)) {
//				bo++;
//				atbyte = bitlist[bo];
//			}
//			if (bitlist[atbyte] & 128) {
//				drawPoint(x + xo + xpos, y + yo + ypos, 0xFFFF);
//			}
//			atbit++;
//			atbyte <<= 1;
//		}
//	}
//}



