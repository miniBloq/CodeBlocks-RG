/***************************************************************
 * Name:      testapp0Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2011-01-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TESTAPP0MAIN_H
#define TESTAPP0MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "testapp0App.h"

class testapp0Frame: public wxFrame
{
    public:
        testapp0Frame(wxFrame *frame, const wxString& title);
        ~testapp0Frame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // TESTAPP0MAIN_H
