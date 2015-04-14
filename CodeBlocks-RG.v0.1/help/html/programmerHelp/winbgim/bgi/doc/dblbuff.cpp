// FILE: dblbuff.cpp
// Demostrates double-buffering with the winbgim library.
// Michael Main -- Nov 25, 1998

#include <stdio.h>   // Provides sprintf function
#include "winbgim.h" // Provides Windows BGI functions

int main( )
{
    const int COLUMNS = 8;
    const int ROWS = 16;

    int x, y;        // x and y pixel locations
    int row, column; // Row and column number
    int box_width;   // Width of a color box in pixels
    int box_height;  // Height of a color box in pixels
    int color;       // Color number, now ranging from 0 to 127

    // Initialize the graphics window and set the box size.
    initwindow(400,300);
    box_width = getmaxx( ) / COLUMNS;
    box_height = getmaxy( ) / ROWS;

    // Draw some items on pages 1 and 0:
    setactivepage(1);
    line(0, 0, getmaxx( ), getmaxy( ));
    outtextxy(100, 100, "This is page #1.");
    outtextxy(100, 120, "Press a key to end the program.");
    setactivepage(0);
    line(getmaxx( ), 0, 0, getmaxy( ));
    outtextxy(100, 100, "This is page #0.");
    outtextxy(100, 120, "Press a key to see page #1.");

    // Get the user to press a key to move to page 1:
    getch( );
    setvisualpage(1);
    getch( );

}


