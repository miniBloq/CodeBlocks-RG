// FILE: bgimdemo.cpp
// Written by: Michael Main (main@colorado.edu) -- Oct 5, 1999
// A small demonstration program using Borland's BGI.
// This version has been modified to use the winbgim library that runs
// under Borland C++ 5.02 for Windows instead of the usual BGI files.
// This version also has a modification to wait for a mouse click at
// the end.

#include "winbgim.h"  // Provides the BGI graphics functions for Windows

// Call this function to draw an isosoles triangle with the given base and
// height. The triangle will be drawn just above the botton of the screen.
void triangle(int base, int height)
{
    int maxx = getmaxx( );
    int maxy = getmaxy( );

    line(maxx/2 - base/2, maxy - 10, maxx/2 + base/2, maxy - 10);
    line(maxx/2 - base/2, maxy - 10, maxx/2, maxy - 10 - height);
    line(maxx/2 + base/2, maxy - 10, maxx/2, maxy - 10 - height); 
}

void main(void)
{
    int maxx, maxy;  // Maximum x and y pixel coordinates
    int x, y;        // x and y pixel coordinates of a mouse click
    int divisor;     // Divisor for the length of a triangle side
    bool red_clicked;// Changes to true when a red pixel is clicked
    
    // Put the machine into graphics mode and get the maximum coordinates:
    initwindow(450, 300);         
    maxx = getmaxx( );
    maxy = getmaxy( );
    
    // Draw a white circle with red inside and a radius of 50 pixels:
    setfillstyle(SOLID_FILL, RED);
    setcolor(WHITE);
    fillellipse(maxx/2, maxy/2, 50, 50);
    
    // Print a message and wait for a red pixel to be double clicked:
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(20, 20, "Left click in RED to end.");
    setcolor(BLUE);
    red_clicked = false;
    divisor = 2;
    while (!red_clicked)
    {
        triangle(maxx/divisor, maxy/divisor);
        delay(500);
        divisor++;
	if (ismouseclick(WM_LBUTTONDOWN))
	{
	    getmouseclick(WM_LBUTTONDOWN, x, y);
	    red_clicked = (getpixel(x, y) == RED);
	}
    }

    cout << "The mouse was clicked at: ";
    cout << "x=" << mousex( );
    cout << " y=" << mousey( ) << endl;
    
    // Switch back to text mode:
    closegraph( );
}

