GLUT 3.7.6-5.mp for MinGW

This package contains a MinGW header, import library, and DLL built using the
MinGW compiler. The package is built from the source code from Nate Robins’ site
(http://www.xmission.com/~nate/glut.html), and is binary compatible with the DLL
available from there.

The “glut.h” header has an additional preprocessor definition to allow it to
work with MinGW, and the DLL has had a version resource added to it so the
version information and copyright is viewable using Windows Explorer. Otherwise,
the package is identical to the original.

It should be noted that this package comes with very little support, and is
provided only for reasons of backwards compatibility. Unless you have some
specific reason to use GLUT for Win32, then I would recommend using freeglut
(http://freeglut.sourceforge.net/) instead. It’s a much more up to date GLUT
package which is actively maintained, and switching from GLUT for Win32 to
freeglut should be a matter of a simple recompile.


Installation

Create a folder on your PC which is readable by all users, for example
“C:\Program Files\Common Files\MinGW\GLUT\” on a typical Windows system. Copy
the “lib\” and “include\” folders from this zip archive to that location.

The GLUT for Win32 DLL should either be placed in the same folder as your
application, or can be installed in a system-wide folder which appears in your
%PATH% environment variable. On a 32 bit Windows system this is typically
“C:\Windows\System32\”, and on a 64 bit Windows system this is typically
“C:\Windows\SysWOW64\”.


Compiling Applications

Given a source file “test.c”, which you want to compile to an application
“test.exe”, you can compile and link it with the following commands (replacing
the include and lib paths with the ones you created above if necessary):

  gcc -c -o test.o test.c -I"C:\Program Files\Common Files\MinGW\GLUT\include"
  gcc -o test.exe test.o -L"C:\Program Files\Common Files\MinGW\GLUT\lib" -lglut32 -lopengl32 -Wl,--subsystem,windows

The “-Wl,--subsystem,windows” is needed so that the application builds as a
Windows GUI application rather than a console application. If you are using GLU
functions you should also include “-lglu32” on the command line.

Don’t forget to either include the freeglut DLL when distributing applications,
or provide your users with some method of obtaining it if they don’t already
have it!

Please visit http://www.transmissionzero.co.uk/computing/using-glut-with-mingw/
for further information and usage.


Cross-Compilation

I’ve not covered the setup of GLUT for Win32 for use in cross-compilation, i.e.
when building Windows GLUT applications using a Linux system. Setting GLUT up
with MinGW on other operating systems can be done following the instructions
above, except that the paths will be different.


Changelog

2009–12–22: Release 3.7.6-5.mp

  • Updated documentation to take into account the fact that 32 bit DLLs should
    be placed in the “SysWOW64” folder on 64 bit Windows versions, rather than
    “System32”.

2009–09–27: Release 3.7.6-4.mp

  • Included a Windows DLL built with MinGW, rather than relying on Nate Robins’
    DLL which is statically linked against an old version of Microsoft’s C
    runtime.
  • Added a version resource to the DLL, allowing the version information and
    copyright to be viewed using Windows Explorer.


Martin Payne
2009–12–22

http://www.transmissionzero.co.uk/
