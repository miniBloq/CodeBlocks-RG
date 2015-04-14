// FILE: testget.cpp
// Written by Michael Main -- Nov 4, 1998
//
// Illustrates several features of the modified winbgim functions.
// To use these features, please download the newest versions of
// winbgim.h and winbgim.cpp as described in:
// http://www.cs.colorado.edu/~main/bgi/README.html
// Then create a project file that contains testget.cpp and winbgim.cpp.
// The project file should use have:
//   Target type: Application (exe)
//   Platform: Win32
//   Target model: Console
//   Using Static Libraries
//
// Compile and run the program to see:
//   1. Numbers that print in the graphics window.
//   2. Using the getch( ) function to get arrow and other special keys.
//
// Note:
//   winbgim contains its own versions of getch, delay, and kbhit.
//   You do not need to include conio.h to use these functions.
//   If you are going to print numbers to the graphics screen as shown below,
//   you do need to include stdio.h (which contains sprintf).

#include <cstdio>       // Provides sprintf
#include <iostream>     // Provides cout
#include <graphics.h>
using namespace std;

void outintxy(int x, int y, int value);

int main( )
{
    int i;
    char c;
    int height;
    
    // Initialize the graphics window.
    initwindow(300, 400);

    // Convert some numbers to strings and draw them in graphics window:
    height = textheight("M") + 2;
    outtextxy(10, height, "Here are some numbers:");
    for (i = 2*height; i <= height*10; i += height)
        outintxy(20, i, i);

    // Get some characters from the keyboard until an X is typed:
    outtextxy(20, 13*height, "Click in this graphics window,");
    outtextxy(20, 14*height, "and then press arrow keys.");
    outtextxy(20, 15*height, "Watch the console window while pressing.");
    outtextxy(20, 16*height, "Press X to exit.");
    do
    {
        c = (char) getch( );
        if (c != 0)
            cout << "That is ASCII value: " << (int) c << endl;
        else
        {   // Process one of the special keys:
            c = (char) getch( );
            switch (c)
            {
                case KEY_HOME:    cout << "Home key."   << endl; break;
                case KEY_UP:      cout << "Up key."     << endl; break;
                case KEY_PGUP:    cout << "PgUp key."   << endl; break;
                case KEY_LEFT:    cout << "Left key."   << endl; break;
                case KEY_CENTER:  cout << "Center key." << endl; break;
                case KEY_RIGHT:   cout << "Right key."  << endl; break;
                case KEY_END:     cout << "End key."    << endl; break;
                case KEY_DOWN:    cout << "Down key."   << endl; break;
                case KEY_PGDN:    cout << "PgDn key."   << endl; break;
                case KEY_INSERT:  cout << "Insert key." << endl; break;
                case KEY_DELETE:  cout << "Delete key." << endl; break;
                case KEY_F1:      cout << "F1 key."     << endl; break;
                case KEY_F2:      cout << "F2 key."     << endl; break;
                case KEY_F3:      cout << "F3 key."     << endl; break;
                case KEY_F4:      cout << "F4 key."     << endl; break;
                case KEY_F5:      cout << "F5 key."     << endl; break;
                case KEY_F6:      cout << "F6 key."     << endl; break;
                case KEY_F7:      cout << "F7 key."     << endl; break;
                case KEY_F8:      cout << "F8 key."     << endl; break;
                case KEY_F9:      cout << "F9 key."     << endl; break;
                default: cout << "Unknown extended key." << endl;
            }
        }
    }   while ((c != 'x') && (c != 'X'));

}


void outintxy(int x, int y, int value)
{
   char digit_string[20];
   sprintf(digit_string, "%d", value);
   outtextxy(x, y, digit_string);
}



