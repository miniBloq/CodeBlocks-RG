/***************************************************************
 * Name:      SerialPortsEnumMain.cpp
 * Purpose:   This little app lists all serial ports fast.
 * Author:    Julián da Silva Gillig
 * Created:   2010.09.09
 * Copyright: (c) 2010 Julián da Silva Gillig
 * License:   Multiplo Pacifist License (MPL).
              NOTE: If this license (the MPL) results in some
              inconpatibility with the wxWidgets license, then
              the wxWidgets applies (because this work is based
              on wxWidgets libraries).
 **************************************************************/

#include "App.h"

//(*AppHeaders
#include "dlgMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(App);

bool App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	dlgMain Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;
}
