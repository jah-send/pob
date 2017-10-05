/** 
 *
 * @brief HelloWorld. 
 *
 * @file Describe how to write text on the lcd
 *
 * @author Sylvain FAY-CHATELARD
 */

#include <pobRoboticSuite.h>

 int main(void)
 {
    // declare a ScrollOption structure:
    ScrollOption option;

    // init pob-robotics-suite:
    InitCpu();
    InitRobot();

    // set option in the scructure: loop, text go from left to right at speed 2:
    option.mode     = SCROLL_MODE_LOOP;
    option.sens     = SCROLL_LEFT_RIGHT;
    option.speed    = 2;

    // write parameters:
    SetLCDScrollParam(&option);

    // write text to the lcd:
    SetLCDScrollText((UInt8*)"Hello cruel world!",18);

    // ... and start the scrolling!
    StartLCDScroll();

    return 0;
 }