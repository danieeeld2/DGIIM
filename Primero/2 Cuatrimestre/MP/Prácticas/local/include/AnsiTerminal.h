/**
 * @file AnsiTerminal.h
 * @author DECSAI
 * @brief Full functional static library of tools to use a coloured terminal (4 bits per pixel),
 * manage cursor position, resize the terminal window according to standard
 * ANSI escape codes. See https://en.wikipedia.org/wiki/ANSI_escape_code for further details
 * @note Fully implemented. No further implementation required.
 */
#ifndef ANSITERMINAL_H
#define ANSITERMINAL_H

#define ESC (string) "\033"
#define black setColor(0,0,0)
#define red setColor(0.5,0,0)
#define green setColor(0,0.5,0)
#define brown setColor(0.5,0.5,0)
#define blue setColor(0,0,0.5)
#define magenta setColor(0.5,0,0.5)
#define cyan setColor(0,0.5,0.5)
#define gray setColor(0.5,0.5,0.5)
#define lightred setColor(1,0,0)
#define lightgreen setColor(0,1,0)
#define yellow setColor(1,1,0)
#define lightblue setColor(0,0,1)
#define lightmagenta setColor(1,0,1)
#define lightcyan setColor(0,1,1)
#define white setColor(1,1,1)

/**
 * @brief Encodes a RGB color as an integer value with 4 bits per pixel. 
 * Each RGB value is specified as a real number in the range 
 * from 0 (darker) to 1 (brighter). 
 * @param r Red value
 * @param g Green Value
 * @param b Blue Value
 * @return An integer value which can be used to reference the color
 * @warning Since only 4 bpp are used, that is, 16 possible values for each RGB, rounding differences might appear.
 */
int setColor(double r, double g, double b);
/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Red component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getRed(int color);
/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Green component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getGreen(int color);
/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Blue component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getBlue(int color);

/**
 * @brief Returns the current color of text as an encoded color (4 bpp)
 * @return An integer that encodes the RGB color with 4 bits per pixel
 */
int getText();
/**
 * @brief Returns the current color of the background as an encoded color (4 bpp)
 * @return An integer that encodes the RGB color with 4 bits per pixel
 */
int getBackground();
/**
 * @brief Defines the color of the background
 * @param color To be assigned to the background of the terminal
 */
void setBackground(int color);
/**
 * @brief Defines the color of the text in the terminal
 * @param color The color to be assigned to the text
 */
void setText(int color);
/**
 * @brief Clears the screen with the existing background color.
 */
void clearScreen();
/**
 * @brief Locates the cursor, and therfore any further cout operation, 
 * in a position of the screen of the terminal given by @p x and @p y
 * @param x Horizontal coordinate from top-left corner, which is x=1
 * @param y vertical coordinate from top-left corner, which is y=1
 */
void setCursorXY(int x, int y);
/**
 * @brief Shows the cursor in the screen
 */
void setCursorOn();
/**
 * @brief Hides the cursor in the screen
 */
void setCursorOff();
/**
 * @brief Fills a rectangle in the screen
 * @param x Top ledt
 * @param y Top left
 * @param w Width of the rectangle, specified as text-columns in the terminal
 * @param h Height of the rectangle, specified as text-rows in the terminal
 * @param color Filling color
 */
void doRectangle(int x, int y, int w, int h, int color);
/**
 * @brief Waits until RETURN is pressed and does not leave any trail
 * in cin
 */
void pressReturn();
/**
 * @brief Fixes the size of the terminal 
 * @param r Number of rows
 * @param c Number of columns
 */
void setSize(int r, int c);




#endif /* ANSITERMINAL_H */

