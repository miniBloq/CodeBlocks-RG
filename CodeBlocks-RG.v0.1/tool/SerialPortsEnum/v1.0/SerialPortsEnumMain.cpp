/***************************************************************
 * Name:      SerialPortsEnumMain.cpp
 * Purpose:   This little app lists all serial ports fast.
 * Author:    Alan Kharsansky; Julián da Silva Gillig
 * Created:   2010.09.09
 * Copyright: (c) 2010 Multiplo (http://multiplo.org)
 * License:   Multiplo Pacifist License (MPL).
              NOTE: If this license (the MPL) results in some
              inconpatibility with the wxWidgets license, then
              the wxWidgets applies (because this work is based
              on wxWidgets libraries).
 **************************************************************/

#include "SerialPortsEnumMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(SerialPortsEnumDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SerialPortsEnumDialog)
const long SerialPortsEnumDialog::ID_TEXTCTRL1 = wxNewId();
const long SerialPortsEnumDialog::ID_CHKSTAYONTOP = wxNewId();
const long SerialPortsEnumDialog::ID_BTNABOUT = wxNewId();
//*)

BEGIN_EVENT_TABLE(SerialPortsEnumDialog,wxDialog)
    //(*EventTable(SerialPortsEnumDialog)
    //*)
END_EVENT_TABLE()

SerialPortsEnumDialog::SerialPortsEnumDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SerialPortsEnumDialog)
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, _("SerialPortsEnum v1.0"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(154,152));
    Move(wxPoint(-1,-1));
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    txtSerialPorts = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(101,125), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(txtSerialPorts, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    chkStayOnTop = new wxCheckBox(this, ID_CHKSTAYONTOP, _("&Stay on top"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHKSTAYONTOP"));
    chkStayOnTop->SetValue(true);
    BoxSizer1->Add(chkStayOnTop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnAbout = new wxButton(this, ID_BTNABOUT, _("&About..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTNABOUT"));
    BoxSizer1->Add(btnAbout, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_CHKSTAYONTOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SerialPortsEnumDialog::OnchkStayOnTopClick);
    Connect(ID_BTNABOUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SerialPortsEnumDialog::OnAbout);
    //*)

    timer = new Ticker(this);
    timer->Start(500);
}

SerialPortsEnumDialog::~SerialPortsEnumDialog()
{
    //(*Destroy(SerialPortsEnumDialog)
    //*)
}

void SerialPortsEnumDialog::OnQuit(wxCommandEvent& event)
{
    timer->Stop(); //It doesn't matter if the timer is running or not, it's stoped anyway.
	if (timer)
		delete timer;
    Close();
}

void SerialPortsEnumDialog::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    //##It's "Julián", not "Julian", but it does not work well on the message box:
    wxString msg = "(c) 2010 Multiplo (http://multiplo.org)\n\nProgrammers:\n\tAlan Kharsansky\n\tJulian da Silva Gillig";
    wxMessageBox(msg, _("SerialPortsEnum v1.0"));
}

void SerialPortsEnumDialog::OnchkStayOnTopClick(wxCommandEvent& event)
{
    if (chkStayOnTop->IsChecked())
		SetWindowStyle(GetWindowStyle()|wxSTAY_ON_TOP);
	else
		SetWindowStyle(GetWindowStyle()&(~wxSTAY_ON_TOP));
}
