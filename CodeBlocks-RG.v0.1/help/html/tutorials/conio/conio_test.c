/* A conio testing program.
 *
 * Written by:
 * Michal Molhanec <michal@molhanec.net>
 *
 * Offered for use in the public domain without any warranty.
 */

#include <conio2.h>
#include <stdlib.h>

int main() {
  struct text_info info;
  struct char_info * screen_buffer;
  int i;
  int cursor_pos_x, cursor_pos_y;
  char password[10];

  /* we want to restore current text attributes on the end of application */
  inittextinfo();

  /* get the info about screen */
  gettextinfo( &info );
  
  /* save the cursor position */
  cursor_pos_x = info.curx;
  cursor_pos_y = info.cury;
  
  /* set normal cursor */
  _setcursortype( _NORMALCURSOR );

  /* first we save the existing screen so we can restore it on end */
  screen_buffer = (struct char_info *) malloc(
    info.screenwidth * info.screenheight * sizeof(struct char_info) );
  gettext( 1, 1, info.screenwidth, info.screenheight, screen_buffer );

  /* clear the screen */
  clrscr();

  /* paint border around screen */
  gotoxy( 1, 1 );
  for (i = 1; i <= info.screenwidth; i++) putch( '*' );
  gotoxy( 1, info.screenheight );
  for (i = 1; i < info.screenwidth; i++) putch( '*' );
  for (i = 2; i < info.screenheight; i++) {
      putchxy( 1, i, '*' );
      putchxy( info.screenwidth, i, '*' );
  }

  /* test delline */
  cputsxy( 10,  9, "before" );
  cputsxy( 10, 10, "press any key to delete me" );
  cputsxy( 10, 11, "after" );
  getch();
  gotoxy( 20, 10 );
  delline();

  /* test insline */
  getch();
  insline();

  /* get the info about screen */
  gettextinfo( &info );

  /* paint border around screen */
  gotoxy( 1, 1 );
  for (i = 1; i <= info.screenwidth; i++) putch( '*' );
  gotoxy( 1, info.screenheight );
  for (i = 1; i < info.screenwidth; i++) putch( '*' );
  for (i = 2; i < info.screenheight; i++) {
      putchxy( 1, i, '*' );
      putchxy( info.screenwidth, i, '*' );
  }

  /* test movetext */
  getch();
  movetext( 10, 9, 15, 9, 10, 12 );
  
  gotoxy( 10, 15 );
  password[0] = 7;
  getpass( "Guma: ", password );
  gotoxy( 10, 16 );
  cprintf( "%i     %s", password[1], &password[2] );

  /* test lowvideo/highvideo */
  gotoxy( 20, 10 );
  textcolor( CYAN );
  textbackground( GREEN );
  cputs( "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" );
  highvideo();
  gotoxy( 20, 11 );
  cputs( "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" );
  lowvideo();
  gotoxy( 20, 12 );
  cputs( "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" );
  
#ifdef UNICODE
  /* test unicode */
  gotoxy( 40, 15 );
  textcolor( BLACK );
  textbackground( WHITE );
  cputws( L"UNICODE" );
#endif

  /* do some writing */
  gotoxy( 10, 20 );
  textcolor( YELLOW );
  textbackground( BLUE );
  cputs( "Press any key to quit" );
  getch();

  /* restore the original screen */
  puttext( 1, 1, info.screenwidth, info.screenheight, screen_buffer );
  normvideo();
  gotoxy( cursor_pos_x, cursor_pos_y );

  free( screen_buffer );
  return 0;
}

