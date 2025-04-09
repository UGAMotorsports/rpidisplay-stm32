/*
 * rpi-display.h
 *
 *  Created on: Mar 10, 2025
 *      Author: bharg
 */

#ifndef SRC_RPI_DISPLAY_RPI_DISPLAY_H_
#define SRC_RPI_DISPLAY_RPI_DISPLAY_H_

#include "gfxfont.h"

const uint8_t flip_object = 1;
const uint8_t no_flip_object = 0;

/**
 * initializes the screen, run this before ever doing anything else with the screen
 */
void initializeScreen();

/**
 * resets the screen as if it was power cycled, preferrably run this before you initialize
 */
void resetScreen();

/**
 * draws a vertical line on the screen
 * @param x1 This is the x coordinate to start
 * @param y1 This is the y coordinate to start
 * @param height This is how far to draw the line
 * @param color This is the color of the line
 */
void drawVLine(uint16_t x1, uint16_t y1, uint16_t height, uint16_t color);

/**
 * draws a horizontal line on the screen
 * @param x1 This is the x coordinate to start
 * @param y1 This is the y coordinate to start
 * @param height This is how far to draw the line
 * @param color This is the color of the line
 */
void drawHLine(uint16_t x1, uint16_t y1, uint16_t height, uint16_t color);

void drawPoint(uint16_t x, uint16_t y, uint16_t color);
void drawRectangleFilled(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color);
void drawRectangleOutline(uint16_t x1, uint16_t y1, uint16_t length, uint16_t height, uint16_t color);
void drawEllipseFilled(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color);
void drawEllipseOutline(uint16_t x, uint16_t y, uint16_t length, uint16_t height, uint16_t color);
void drawChar(char letter, const GFXfont* font, uint16_t xpos, uint16_t ypos, uint8_t flip);

#endif /* SRC_RPI_DISPLAY_RPI_DISPLAY_H_ */
