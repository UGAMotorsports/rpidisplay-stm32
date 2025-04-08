/*
 * rpi-display.h
 *
 *  Created on: Mar 10, 2025
 *      Author: bharg
 */

#ifndef SRC_RPI_DISPLAY_RPI_DISPLAY_H_
#define SRC_RPI_DISPLAY_RPI_DISPLAY_H_


void initializeScreen();
void resetScreen();
void drawVLine(uint16_t x1, uint16_t y1, uint16_t height, uint16_t color);
void drawHLine(uint16_t x1, uint16_t y1, uint16_t height, uint16_t color);
void drawPoint(uint16_t x, uint16_t y, uint16_t color);
void drawRectangleFilled(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color);
void drawRectangleOutline(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color);
void drawEllipseFilled(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color);
void drawEllipseOutline(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color);
//void drawCharacter(char letter, GFXfont* font, uint16_t xpos, uint16_t ypos);


#endif /* SRC_RPI_DISPLAY_RPI_DISPLAY_H_ */
