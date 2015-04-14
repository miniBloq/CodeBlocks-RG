#include "winbgim.h"  // Provides the BGI graphics functions for Windows
#include <iostream.h>

#define RGB_COLOR(c) (c & 0xFFFFFF)

void main(void)
{
    int loopCounterx,loopCountery,inputChar,i,j;
    void *myImage1,*myImage2;

    // Put the machine into graphics mode and set the maximum coordinates:
    initwindow(128, 256);

    for (loopCounterx=0;loopCounterx<255;loopCounterx+=2)
    	for (loopCountery=0;loopCountery<255;loopCountery+=2)
	    putpixel(loopCounterx/2,loopCountery/2,COLOR(loopCounterx, loopCountery, 0));

    for (loopCounterx=0;loopCounterx<255;loopCounterx+=2)
    	for (loopCountery=0;loopCountery<255;loopCountery+=2)
	    putpixel(loopCounterx/2,loopCountery/2+128,COLOR(0, loopCounterx, loopCountery));

    myImage1=new char[imagesize(68,68,118,118)];
    myImage2=new char[imagesize(68,196,118,246)];

    getimage(68,68,118,118,myImage1);
    getimage(68,196,118,246,myImage2);
    putimage(68,196,myImage1,0);
    putimage(68,68,myImage2,0);

    setcolor(BLUE);
    line(10,10,100,10);
    line(100,10,100,100);
    line(100,100,10,100);
    line(10,100,10,10);

    cout << "Press return in the graphics window to end program." << endl;
    getch( );
    
    // Switch back to text mode:
    closegraph( );
}

