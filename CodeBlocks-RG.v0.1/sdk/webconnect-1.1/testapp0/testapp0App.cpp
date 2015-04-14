/***************************************************************
 * Name:      testapp0App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2011-01-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "testapp0App.h"
#include "testapp0Main.h"

IMPLEMENT_APP(testapp0App);

bool testapp0App::OnInit()
{
    testapp0Frame* frame = new testapp0Frame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
