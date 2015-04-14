#include "winbgim.h"  // Provides the BGI graphics functions for Windows
#include <iostream.h>

#define RGB_COLOR(c) (c & 0xFFFFFF)

void main(void)
{
    int loopCounterx,loopCountery,inputChar,i,j;
    void *myImage1,*myImage2;

    // Put the machine into graphics mode and set the maximum coordinates:
    initwindow(600, 400);

    for (loopCounterx=0;loopCounterx<600;loopCounterx+=20)
    	for (loopCountery=0;loopCountery<200;loopCountery+=20)
	{
	    setfillstyle(SOLID_FILL, COLOR(255*loopCounterx/600, 255*loopCountery/200, 0));
	    bar(loopCounterx , loopCountery, loopCounterx+20, loopCountery+20);
	}
    
    for (loopCounterx=0;loopCounterx<600;loopCounterx+=20)
    	for (loopCountery=200;loopCountery<400;loopCountery+=20)
	{
	    setfillstyle(SOLID_FILL, COLOR(0, 255*loopCounterx/600, 255*(loopCountery-200)/200));
	    bar(loopCounterx , loopCountery, loopCounterx+20, loopCountery+20);
	}

    cout << "Press return in the graphics window to end program." << endl;
    getch( );
    
    // Switch back to text mode:
    closegraph( );
}

