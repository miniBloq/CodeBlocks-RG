/***************************************************************
 * Name:      SerialPortsEnumApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Alan Kharsansky; Julián da Silva Gillig ()
 * Created:   2010-09-09
 * Copyright: Alan Kharsansky; Julián da Silva Gillig (http://multiplo.org)
 * License:
 **************************************************************/

#include "SerialPortsEnumApp.h"

//(*AppHeaders
#include "SerialPortsEnumMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SerialPortsEnumApp);

bool SerialPortsEnumApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SerialPortsEnumDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
