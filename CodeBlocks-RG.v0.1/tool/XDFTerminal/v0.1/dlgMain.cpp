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

#include "dlgMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(dlgMain)
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

//(*IdInit(dlgMain)
const long dlgMain::ID_TEXTCTRL1 = wxNewId();
const long dlgMain::ID_PANEL2 = wxNewId();
const long dlgMain::ID_TEXTCTRL4 = wxNewId();
const long dlgMain::ID_TEXTCTRL3 = wxNewId();
const long dlgMain::ID_SPLITRXTX = wxNewId();
const long dlgMain::ID_PANEL1 = wxNewId();
const long dlgMain::ID_NOTEBOOK1 = wxNewId();
const long dlgMain::ID_CHECKSTAYONTOP = wxNewId();
const long dlgMain::ID_CHECKSHOWCONFIG = wxNewId();
const long dlgMain::ID_BUTTONDTR = wxNewId();
const long dlgMain::ID_CHECKDTR = wxNewId();
const long dlgMain::ID_CHECKDSR = wxNewId();
const long dlgMain::ID_CHECKDCD = wxNewId();
const long dlgMain::ID_BUTTONRTS = wxNewId();
const long dlgMain::ID_CHECKRTS = wxNewId();
const long dlgMain::ID_CHECKCTS = wxNewId();
const long dlgMain::ID_CHECKRING = wxNewId();
const long dlgMain::ID_PANEL_FLAGS = wxNewId();
const long dlgMain::ID_STATICTEXT4 = wxNewId();
const long dlgMain::ID_CHCHANDSHAKING = wxNewId();
const long dlgMain::ID_STATICDATABITS = wxNewId();
const long dlgMain::ID_CHCDATABITS = wxNewId();
const long dlgMain::ID_STATICPARITY = wxNewId();
const long dlgMain::ID_CHCPARITY = wxNewId();
const long dlgMain::ID_STATICSTOPBITS = wxNewId();
const long dlgMain::ID_CHOICSTOPBITS = wxNewId();
const long dlgMain::ID_STATICBAUDRATE = wxNewId();
const long dlgMain::ID_CHCBAUDRATE = wxNewId();
const long dlgMain::ID_STATICCOMM = wxNewId();
const long dlgMain::ID_TEXTCOMM = wxNewId();
const long dlgMain::ID_SPINCOMM = wxNewId();
const long dlgMain::ID_BUTTONOPEN = wxNewId();
const long dlgMain::ID_BUTTONCLOSE = wxNewId();
const long dlgMain::ID_PANEL3 = wxNewId();
//*)




BEGIN_EVENT_TABLE(MyTextCtrl,wxTextCtrl)
    //EVT_KEY_DOWN(MyTextCtrl::OnKeyDown)
    EVT_CHAR(MyTextCtrl::OnChar)

    //##Agregar evento click, y ahí pasar el color del texto al color que esté configurado para Tx, ya que se encontró
    //que a veces, si se escribe y se dan clicks medio rápido, se intercalan teclas negras con las azules.
/*
    EVT_KEY_UP(MyTextCtrl::OnKeyUp)
    EVT_CHAR(MyTextCtrl::OnChar)

    EVT_TEXT(wxID_ANY, MyTextCtrl::OnText)
    EVT_TEXT_ENTER(wxID_ANY, MyTextCtrl::OnTextEnter)
    EVT_TEXT_URL(wxID_ANY, MyTextCtrl::OnTextURL)
    EVT_TEXT_MAXLEN(wxID_ANY, MyTextCtrl::OnTextMaxLen)
    EVT_TEXT_CUT(wxID_ANY,   MyTextCtrl::OnTextCut)
    EVT_TEXT_COPY(wxID_ANY,  MyTextCtrl::OnTextCopy)
    EVT_TEXT_PASTE(wxID_ANY, MyTextCtrl::OnTextPaste)

    EVT_MOUSE_EVENTS(MyTextCtrl::OnMouseEvent)

    EVT_SET_FOCUS(MyTextCtrl::OnSetFocus)
    EVT_KILL_FOCUS(MyTextCtrl::OnKillFocus)
*/
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(dlgMain,wxDialog)
	EVT_SIZE(dlgMain::OnResize)
	//EVT_SHOW(dlgMain::OnShow)
    //(*EventTable(dlgMain)
    //*)
/*
    EVT_CHAR(dlgMain::OntxtTxRxChar)
    EVT_KEY_UP(dlgMain::OnKeyUp)
*/
END_EVENT_TABLE()

dlgMain::dlgMain(wxWindow* parent,wxWindowID id)
{
	//##Tiene que ir al principio, si no el evento OnResize entra antes de que
	//esté terminada la construcción del form, por lo que se cuelga todo:
	//resizeReady = false;
	firstTime = true;

    //(*Initialize(dlgMain)
    wxFlexGridSizer* flexParity;
    wxBoxSizer* boxRxTx;
    wxBoxSizer* BoxSizer2;
    wxFlexGridSizer* flexBaudrate;
    wxFlexGridSizer* flexDataBits;
    wxGridSizer* GridSizer1;
    wxFlexGridSizer* flexCommNumber;
    wxFlexGridSizer* flexStopBits;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("XDFTerminal v0.1"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(432,226));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    FlexGridSizer1 = new wxFlexGridSizer(2, 3, 0, 0);
    FlexGridSizer1->AddGrowableCol(3);
    FlexGridSizer1->AddGrowableRow(0);
    noteRxTx = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(287,190), 0, _T("ID_NOTEBOOK1"));
    noteRxTx->SetMinSize(wxSize(-1,-1));
    Panel2 = new wxPanel(noteRxTx, ID_PANEL2, wxDefaultPosition, wxSize(139,87), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    boxRxTx = new wxBoxSizer(wxHORIZONTAL);
    txtTxRx = new MyTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(269,113), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_RICH2, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    boxRxTx->Add(txtTxRx, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    Panel2->SetSizer(boxRxTx);
    boxRxTx->SetSizeHints(Panel2);
    Panel1 = new wxPanel(noteRxTx, ID_PANEL1, wxDefaultPosition, wxSize(142,87), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(-1,30));
    boxTxRx = new wxBoxSizer(wxVERTICAL);
    splitRxTx = new wxSplitterWindow(Panel1, ID_SPLITRXTX, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DSASH, _T("ID_SPLITRXTX"));
    splitRxTx->SetMinSize(wxSize(10,10));
    splitRxTx->SetMinimumPaneSize(10);
    txtTx = new MyTextCtrl(splitRxTx, ID_TEXTCTRL4, wxEmptyString, wxPoint(-113,0), wxSize(269,180), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_RICH2, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    txtTx->SetMinSize(wxSize(-1,30));
    txtRx = new wxTextCtrl(splitRxTx, ID_TEXTCTRL3, wxEmptyString, wxPoint(0,152), wxSize(269,180), wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    txtRx->SetMinSize(wxSize(-1,30));
    splitRxTx->SplitHorizontally(txtTx, txtRx);
    splitRxTx->SetSashPosition(90);
    boxTxRx->Add(splitRxTx, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(boxTxRx);
    boxTxRx->SetSizeHints(Panel1);
    noteRxTx->AddPage(Panel2, _("Single Tx/Rx"), false);
    noteRxTx->AddPage(Panel1, _("Separated Tx/Rx"), false);
    FlexGridSizer1->Add(noteRxTx, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    pnlControls = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxSize(188,115), wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    pnlControls->SetMinSize(wxSize(-1,-1));
    flexControls = new wxFlexGridSizer(1, 1, 0, 0);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    chkStayOnTop = new wxCheckBox(pnlControls, ID_CHECKSTAYONTOP, _("Stay on top"), wxDefaultPosition, wxSize(84,13), 0, wxDefaultValidator, _T("ID_CHECKSTAYONTOP"));
    chkStayOnTop->SetValue(false);
    BoxSizer2->Add(chkStayOnTop, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkShowConfig = new wxCheckBox(pnlControls, ID_CHECKSHOWCONFIG, _("Show config"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKSHOWCONFIG"));
    chkShowConfig->SetValue(true);
    BoxSizer2->Add(chkShowConfig, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    pnlFlags = new wxPanel(pnlControls, ID_PANEL_FLAGS, wxDefaultPosition, wxSize(190,59), wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL_FLAGS"));
    GridSizer1 = new wxGridSizer(4, 4, 0, 0);
    btnDTR = new wxButton(pnlFlags, ID_BUTTONDTR, _("DTR"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTONDTR"));
    btnDTR->Disable();
    GridSizer1->Add(btnDTR, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkDTR = new wxCheckBox(pnlFlags, ID_CHECKDTR, _("DTR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKDTR"));
    chkDTR->SetValue(false);
    chkDTR->Disable();
    GridSizer1->Add(chkDTR, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkDSR = new wxCheckBox(pnlFlags, ID_CHECKDSR, _("DSR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKDSR"));
    chkDSR->SetValue(false);
    chkDSR->Disable();
    GridSizer1->Add(chkDSR, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkDCD = new wxCheckBox(pnlFlags, ID_CHECKDCD, _("DCD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKDCD"));
    chkDCD->SetValue(false);
    chkDCD->Disable();
    GridSizer1->Add(chkDCD, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    btnRTS = new wxButton(pnlFlags, ID_BUTTONRTS, _("RTS"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTONRTS"));
    btnRTS->Disable();
    GridSizer1->Add(btnRTS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkRTS = new wxCheckBox(pnlFlags, ID_CHECKRTS, _("RTS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKRTS"));
    chkRTS->SetValue(false);
    chkRTS->Disable();
    GridSizer1->Add(chkRTS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkCTS = new wxCheckBox(pnlFlags, ID_CHECKCTS, _("CTS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKCTS"));
    chkCTS->SetValue(false);
    chkCTS->Disable();
    GridSizer1->Add(chkCTS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkRING = new wxCheckBox(pnlFlags, ID_CHECKRING, _("RING"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKRING"));
    chkRING->SetValue(false);
    chkRING->Disable();
    GridSizer1->Add(chkRING, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    pnlFlags->SetSizer(GridSizer1);
    GridSizer1->SetSizeHints(pnlFlags);
    flexControls->Add(pnlFlags, 1, wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    flexHandshaking = new wxFlexGridSizer(0, 2, 0, 0);
    staticHandshaking = new wxStaticText(pnlControls, ID_STATICTEXT4, _("Handshaking:"), wxDefaultPosition, wxSize(75,13), 0, _T("ID_STATICTEXT4"));
    flexHandshaking->Add(staticHandshaking, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chcHandshaking = new wxChoice(pnlControls, ID_CHCHANDSHAKING, wxDefaultPosition, wxSize(114,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHCHANDSHAKING"));
    chcHandshaking->SetSelection( chcHandshaking->Append(_("None")) );
    chcHandshaking->Append(_("RTS/CTS"));
    chcHandshaking->Append(_("XON/XOFF"));
    chcHandshaking->Append(_("RTS/CTS + XON/XOFF"));
    chcHandshaking->Append(_("RTS on Tx"));
    chcHandshaking->Disable();
    flexHandshaking->Add(chcHandshaking, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexHandshaking, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexDataBits = new wxFlexGridSizer(0, 2, 0, 0);
    staticDataBits = new wxStaticText(pnlControls, ID_STATICDATABITS, _("Data bits:"), wxDefaultPosition, wxSize(75,13), 0, _T("ID_STATICDATABITS"));
    flexDataBits->Add(staticDataBits, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chcDataBits = new wxChoice(pnlControls, ID_CHCDATABITS, wxDefaultPosition, wxSize(114,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHCDATABITS"));
    chcDataBits->Append(_("5"));
    chcDataBits->Append(_("6"));
    chcDataBits->Append(_("7"));
    chcDataBits->SetSelection( chcDataBits->Append(_("8")) );
    chcDataBits->Disable();
    flexDataBits->Add(chcDataBits, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexDataBits, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexParity = new wxFlexGridSizer(0, 2, 0, 0);
    staticParity = new wxStaticText(pnlControls, ID_STATICPARITY, _("Parity:"), wxDefaultPosition, wxSize(75,13), 0, _T("ID_STATICPARITY"));
    flexParity->Add(staticParity, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chcParity = new wxChoice(pnlControls, ID_CHCPARITY, wxDefaultPosition, wxSize(114,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHCPARITY"));
    chcParity->SetSelection( chcParity->Append(_("None")) );
    chcParity->Append(_("Even"));
    chcParity->Append(_("Odd"));
    chcParity->Disable();
    flexParity->Add(chcParity, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexParity, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexStopBits = new wxFlexGridSizer(0, 2, 0, 0);
    staticStopBits = new wxStaticText(pnlControls, ID_STATICSTOPBITS, _("Stop bits:"), wxDefaultPosition, wxSize(75,13), 0, _T("ID_STATICSTOPBITS"));
    flexStopBits->Add(staticStopBits, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chcStopBits = new wxChoice(pnlControls, ID_CHOICSTOPBITS, wxDefaultPosition, wxSize(114,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICSTOPBITS"));
    chcStopBits->SetSelection( chcStopBits->Append(_("1")) );
    chcStopBits->Append(_("2"));
    chcStopBits->Disable();
    flexStopBits->Add(chcStopBits, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexStopBits, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexBaudrate = new wxFlexGridSizer(0, 2, 0, 0);
    staticBaudrate = new wxStaticText(pnlControls, ID_STATICBAUDRATE, _("Baudrate:"), wxDefaultPosition, wxSize(75,13), 0, _T("ID_STATICBAUDRATE"));
    flexBaudrate->Add(staticBaudrate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chcBaudRate = new wxChoice(pnlControls, ID_CHCBAUDRATE, wxDefaultPosition, wxSize(114,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHCBAUDRATE"));
    chcBaudRate->Append(_("1200"));
    chcBaudRate->Append(_("2400"));
    chcBaudRate->Append(_("4800"));
    chcBaudRate->Append(_("9600"));
    chcBaudRate->Append(_("19200"));
    chcBaudRate->Append(_("38400"));
    chcBaudRate->Append(_("57600"));
    chcBaudRate->SetSelection( chcBaudRate->Append(_("115200")) );
    chcBaudRate->Append(_("230400"));
    chcBaudRate->Append(_("460800"));
    chcBaudRate->Append(_("921600"));
    flexBaudrate->Add(chcBaudRate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexBaudrate, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    flexCommNumber = new wxFlexGridSizer(0, 3, 0, 0);
    staticCommNumber = new wxStaticText(pnlControls, ID_STATICCOMM, _("COM:"), wxDefaultPosition, wxSize(30,13), 0, _T("ID_STATICCOMM"));
    flexCommNumber->Add(staticCommNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtCommNumber = new wxTextCtrl(pnlControls, ID_TEXTCOMM, wxEmptyString, wxDefaultPosition, wxSize(109,21), wxTE_READONLY|wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCOMM"));
    flexCommNumber->Add(txtCommNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    spinCommNumber = new wxSpinButton(pnlControls, ID_SPINCOMM, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINCOMM"));
    spinCommNumber->SetRange(1, 1000);
    flexCommNumber->Add(spinCommNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(flexCommNumber, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    btnOpenComm = new wxButton(pnlControls, ID_BUTTONOPEN, _("&Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONOPEN"));
    BoxSizer3->Add(btnOpenComm, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    btnCloseComm = new wxButton(pnlControls, ID_BUTTONCLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCLOSE"));
    btnCloseComm->Disable();
    BoxSizer3->Add(btnCloseComm, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    flexControls->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    pnlControls->SetSizer(flexControls);
    flexControls->SetSizeHints(pnlControls);
    FlexGridSizer1->Add(pnlControls, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHECKSTAYONTOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMain::OnchkStayOnTopClick);
    Connect(ID_CHECKSHOWCONFIG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMain::OnchkShowConfigClick);
    Connect(ID_BUTTONDTR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMain::OnbtnDTRClick);
    Connect(ID_BUTTONRTS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMain::OnbtnRTSClick);
    Connect(ID_CHCHANDSHAKING,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dlgMain::OnchcBaudRateSelect);
    Connect(ID_CHCDATABITS,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dlgMain::OnchcBaudRateSelect);
    Connect(ID_CHCPARITY,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dlgMain::OnchcBaudRateSelect);
    Connect(ID_CHOICSTOPBITS,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dlgMain::OnchcBaudRateSelect);
    Connect(ID_CHCBAUDRATE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dlgMain::OnchcBaudRateSelect);
    Connect(ID_SPINCOMM,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&dlgMain::OnspinCommNumberChange);
    Connect(ID_BUTTONOPEN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMain::OnbtnOpenCommClick);
    Connect(ID_BUTTONCLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMain::OnbtnCloseCommClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgMain::OnInit);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&dlgMain::OnPaint);
    //*)

	//Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dlgMain::OntxtTxRxText);
	//Connect(wxEVT_CHAR,(wxObjectEventFunction)&dlgMain::OntxtTxRxChar);
	//Connect(ID_TEXTCTRL1,wxEVT_CHAR,wxKeyEventHandler(dlgMain::OntxtTxRxChar));


	//##¡NO OLVIDAR PARA TODOS LOS TXT DE TX!
	txtTxRx->setSerialPort(&serialPort);
	txtTx->setSerialPort(&serialPort);
	serialPort.ClrLineState(wxSERIAL_LINESTATE_DTR);
	chkDTR->SetValue(false);
	serialPort.ClrLineState(wxSERIAL_LINESTATE_RTS);
	chkRTS->SetValue(false);

    //##Ver luego bien qué ocurre con los objetos temporales construidos con el "wxT":
	//##Verificar que éste código esté bien, no pierda memoria, etc.:
	spinCommNumber->SetValue(15);

	//##Pasar esto a un método y unificarlo con el evento change del spinControl:
	spinCommNumber->SetValue(15); //##Levantar este valor de archivo.
    unsigned int commNumber = spinCommNumber->GetValue();
    wxString strCommNumber = wxT("\\\\.\\com"); //##Probar que esta sintaxis de nombre de port funcione con ports menores a COM10.
	strCommNumber << commNumber;
	txtCommNumber->SetValue(strCommNumber);

	txtTxRx->SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...
	txtTx->SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...
	txtRx->SetDefaultStyle(wxTextAttr(*wxGREEN)); //##Hacer esto configurable...

	//##Ver si esto queda así:
	txtTxRx->SetPartner(txtTx);
	txtTx->SetPartner(txtTxRx);

	//##Corregir esto, lo cual se corregirá sólo cuando esta info se levante de un archivo
	//de configuración:
	wxSize splitSize = boxTxRx->GetSize();
	//splitRxTx->SetSashPosition(splitSize.GetHeight()/2);
	splitRxTx->SetSashPosition(180);

	//txtTx->SetSize(wxDefaultCoord, splitSize.GetHeight()/2);
	//txtRx->SetSize(wxDefaultCoord, splitSize.GetHeight()/2);

	//##Timer para leer el puerto serie (recepción):
	rxSampleTime_ms = 1; //Levantar este valor del INI.
	timer = new Ticker(this);
}

dlgMain::~dlgMain()
{
    //(*Destroy(dlgMain)
    //*)
}

void dlgMain::OnQuit(wxCommandEvent& event)
{
	timer->Stop(); //It doesn't matter if the timer is running or not, it's stoped anyway.
	if (timer)
		delete timer;
    if (serialPort.IsOpen())
        serialPort.Close();
    Close();
}

void dlgMain::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void dlgMain::OnInit(wxInitDialogEvent& event)
{
}


void dlgMain::OnbtnOpenCommClick(wxCommandEvent& event)
{
	//resizeReady = true; //##debug: borrar esto.

	//##A la clase serialPort va a haber que modificarla también para pasarla a tipos
	//de datos wxWidgets (como wxChar, wxString, etc.).

	//Disables the button and tries to open the port:
	btnOpenComm->Enable(false);

	//char *devname = wxCOM15; //Test.

	//##Ver para qué se utiliza:
	//int timeout = 1000;

	//##Por ahora paridad, stopbits, etc. están cableados en el DCS por defecto,
	//pero debería heredar del wxSerial y hacer los métodos setParity, etc., tipo SNAPI:
	//wxPARITY_NONE


	//Port number:
	wxString devName = txtCommNumber->GetValue();

	//txtTxRx->AppendText(devName);		//Test
	//txtTxRx->AppendText(wxT("\r\n"));	//Test

    if (!serialPort.IsOpen())
    {
		serialPort.Open(devName.char_str());
	}

	//Si logró abrir el puerto, inicia también la recepción de caracteres:
	if (serialPort.IsOpen())
	{
		timer->Start(rxSampleTime_ms);
	}

	//##Borrar (se usó para probar el timer):
	//timer->Start(rxSampleTime_ms);

	//Port baudrate:
	//##¡Muy importante! El baudrate se setea en esta librería, con el PORT ABIERTO
	//(O SEA: DESPUÉS DEL OPEN):
	//##Refactorizar: Mandar esto a un método y llamarlo también desde el evento change del choice:
    unsigned long baudRate;
    wxString strBaudRate = chcBaudRate->GetStringSelection();
    strBaudRate.ToULong(&baudRate);
    serialPort.SetBaudRate((enum wxBaud)baudRate);//##Ojo con esto, hay que cambiar este código por algo mejor...

	//##Debug:
	/*
	wxString baudTest = wxT("");
	baudTest << baudRate;
	txtTxRx->AppendText(baudTest);
	txtTxRx->AppendText(wxT("\r\n"));
	*/

	//wxBaud baudrate = wxBAUD_115200;
	//wxBaud baudrate = wxBAUD_19200;
	//serialPort.SetBaudRate(baudrate);

	//##Pasar esto a un método:
	bool portIsOpen = serialPort.IsOpen();
	btnOpenComm->Enable(!portIsOpen);
	btnCloseComm->Enable(portIsOpen);
	btnDTR->Enable(portIsOpen);
	btnRTS->Enable(portIsOpen);
}

void dlgMain::OnbtnCloseCommClick(wxCommandEvent& event)
{
    if (serialPort.IsOpen())
    {
		timer->Stop();
        serialPort.Close();

        //##Pasar esto a un método:
        bool portIsOpen = serialPort.IsOpen();
        btnOpenComm->Enable(!portIsOpen);
        btnCloseComm->Enable(portIsOpen);
		btnDTR->Enable(portIsOpen);
		btnRTS->Enable(portIsOpen);
    }
}


void dlgMain::OnchcBaudRateSelect(wxCommandEvent& event)
{
    unsigned long baudRate;
    wxString strBaudRate = chcBaudRate->GetStringSelection();
    strBaudRate.ToULong(&baudRate);
    serialPort.SetBaudRate((enum wxBaud)baudRate);//##Ojo con esto, hay que cambiar este código por algo mejor...
}


void dlgMain::OnspinCommNumberChange(wxSpinEvent& event)
{
	//##Verificar que éste código esté bien, no pierda memoria, etc.:
    unsigned int commNumber = spinCommNumber->GetValue();
    wxString strCommNumber = wxT("\\\\.\\com"); //##Probar que esta sintaxis de nombre de port funcione con ports menores a COM10.
	strCommNumber << commNumber;
	txtCommNumber->SetValue(strCommNumber);
}


//##Eventos de pruebas, no asignado: ¡Borrarlo luego!
#if 0
void dlgMain::OntxtTxRxText(wxCommandEvent& event)
{
	//##: wxLogMessage(_T("Text entered: '%s'"), event.GetString().c_str());

	wxString str = event.GetString();
	serialPort.Write(str.char_str(), sizeof(str.char_str()));
}


void dlgMain::OntxtTxRxChar(wxKeyEvent& event)
{
	SetTitle(wxT("Hola"));
	/*
	txtTxRx->AppendText(wxT("hola"));	//Test


	wxString str = event.GetUnicodeKey();
	serialPort.Write(str.char_str(), sizeof(str.char_str()));
	//##Ver si tengo que agregar el event.Skip(), sobre todo cuando tenga que integrar este terminal al ¡¡XDFCenter!!

    //##Ver si con esta llamada, se soluciona o al menos reduce el Bug: Cuando se inicia la aplicación, se escribe algo, y se da un doble click, vuelve a negro el font:
    txtTxRx->SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...
    */
}


void dlgMain::OnKeyUp(wxKeyEvent& event)
{
	SetTitle(wxT("Chau"));
}
#endif


void dlgMain::OnchkStayOnTopClick(wxCommandEvent& event)
{
	/*##Pruebas (que funcionan):
	wxString str;
	wxPoint point = flexControls->GetPosition();
	str << point.x;
	SetTitle(str);
	*/


	if (chkStayOnTop->IsChecked())
		SetWindowStyle(GetWindowStyle()|wxSTAY_ON_TOP);
	else
		SetWindowStyle(GetWindowStyle()&(~wxSTAY_ON_TOP));
}


void dlgMain::ArrangeGUI()
{
	//if (resizeReady)
	if (IsShown())
	{
		/*
		wxString str;
		//wxPoint point = btnOpenComm->GetPosition();
		wxPoint point = flexControls->GetPosition();
		str << point.x;
		SetTitle(str);
		*/

		//##Sacar todo esto fuera en un método, y llamarlo desde algún evento tipo Show():
		int space = 10; //pixels.
		wxSize windowSize = GetClientSize();
		wxSize pnlSize = pnlControls->GetSize();

		//x, y, h, w:
		pnlControls->SetSize(windowSize.GetWidth()-pnlSize.GetWidth()-space,	//x
							 wxDefaultCoord, 									//y
							 wxDefaultCoord, 									//w
							 windowSize.GetHeight()-space);						//h
		//pnlSize = pnlControls->GetSize();
		noteRxTx->SetSize(windowSize.GetWidth()-pnlSize.GetWidth()-space-space,	//w
						  windowSize.GetHeight()-space);						//h

		/*##Debug:
		wxRect noteRect = noteRxTx->GetSize();
		wxString str;
		str << noteRect.GetX();
		SetTitle(str);
		*/
	}
}


void dlgMain::OnShow(wxShowEvent& event)
{
}


void dlgMain::OnResize(wxSizeEvent& event)
{
	//##Si se realiza este resize a mano, nada funciona automáticamente, a menos que se haga el Skip():
	//event.Skip();
	ArrangeGUI();
}




//##Más adelante refactorizar estos nombres, separar en otros archivos, etc.:
/*
void MyTextCtrl::OnKeyDown(wxKeyEvent& event)
{
	//Test: ((wxDialog*)Parent)->SetTitle(wxT("Hola"));

	//##Filtrar cosas como los arroykeys, etc. OPCIONALMENTE
	//(o sea: dar la opción al usuario de que los tome como código y los envíe, o de que los utilice en el soft para moverse
	//a través del texto, etc.). Además, de enviarse, debería mostrar el equivalente en decimal y en hexa de la última línea,
	//formateada con separaciones, etc..
	wxString str = event.GetUnicodeKey();
	((dlgMain*)Parent)->serialPort.Write(str.char_str(), sizeof(str.char_str()));

    //##Ver si con esta llamada, se soluciona o al menos reduce el Bug: Cuando se inicia la aplicación, se escribe algo, y se da un doble click, vuelve a negro el font:
    SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...

	//##Si no se llama a este método, no escribe en pantalla:
	event.Skip();
}
*/


void MyTextCtrl::OnChar(wxKeyEvent& event)
{
	wxChar wchr = event.GetUnicodeKey();
	char *chr = (char*)&wchr; //##Ver si esta conversión de tipos se puede mejorar un poco, o si con este cast alcanza...
	if (Serial)
		Serial->Write(chr, 1);

	//##TxtPartner May be null:
	if (TxtPartner)
	{
		/*Funciona, salvo con las teclas raras, tipo el Delete:
		wxString str = wxT("");
		str << wchr;
		TxtPartner->AppendText(str);
		*/
		//También funciona, y del mismo modo que el texto anterior:
		TxtPartner->AppendText(wchr);
	}

	//##Ver qué se hace con las teclas tipo la de borrado, las flechas, etc., tanto con respecto a lo que se envía por
	//serial como a lo qu ese escribe en el txt asociado...

    //##Ver si con esta llamada, se soluciona o al menos reduce el Bug: Cuando se inicia la aplicación,
    //se escribe algo, y se da un doble click, vuelve a negro el font:
    SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...

	//##Si no se llama a este método, no escribe en pantalla:
	event.Skip();
}

#if 0
//##Borrar:
void MyTextCtrl::OnChar(wxKeyEvent& event)
{
	//Test: ((wxDialog*)Parent)->SetTitle(wxT("Hola"));

/*
	wxString str = event.GetUnicodeKey();
	((dlgMain*)Parent)->serialPort.Write(str.char_str(), 1);
*/
	wxChar wchr = event.GetUnicodeKey();
	char *chr = (char*)&wchr; //##Ver si esta conversión de tipos se puede mejorar un poco, o si con este cast alcanza...
	((dlgMain*)Parent)->serialPort.Write(chr, 1);

    //##Ver si con esta llamada, se soluciona o al menos reduce el Bug: Cuando se inicia la aplicación, se escribe algo, y se da un doble click, vuelve a negro el font:
    SetDefaultStyle(wxTextAttr(*wxBLUE)); //##Hacer esto configurable...

	//##Si no se llama a este método, no escribe en pantalla:
	event.Skip();
}
#endif

/*
void dlgMain::OnbtnTestClick(wxCommandEvent& event)
{
	//Only for testing:
	char aux[] = "pwm(+100,+100)\n";
	serialPort.Write(aux, sizeof(aux));
}
*/


void dlgMain::OnPaint(wxPaintEvent& event)
{
	if (firstTime)
	{
		firstTime = false;
		ArrangeGUI();
	}
	event.Skip();
}

void dlgMain::OnbtnDTRClick(wxCommandEvent& event)
{
	if (chkDTR->IsChecked())
	{
		serialPort.ClrLineState(wxSERIAL_LINESTATE_DTR);
		chkDTR->SetValue(false);
	}
	else
	{
		serialPort.SetLineState(wxSERIAL_LINESTATE_DTR);
		chkDTR->SetValue(true);
	}
}

void dlgMain::OnbtnRTSClick(wxCommandEvent& event)
{
	if (chkRTS->IsChecked())
	{
		serialPort.ClrLineState(wxSERIAL_LINESTATE_RTS);
		chkRTS->SetValue(false);
	}
	else
	{
		serialPort.SetLineState(wxSERIAL_LINESTATE_RTS);
		chkRTS->SetValue(true);
	}
}


void dlgMain::OnchkShowConfigClick(wxCommandEvent& event)
{
	//##No oculta baudrate ni Open/Close porque se pueden necesitar.
	//Sí oculta el número de puerto, que no se puede cambiar con el port abierto.
	if (chkShowConfig->IsChecked())
	{
		pnlFlags->Show();
		staticHandshaking->Show();
		chcHandshaking->Show();
		staticDataBits->Show();
		chcDataBits->Show();
		staticParity->Show();
		chcParity->Show();
		staticStopBits->Show();
		chcStopBits->Show();
		staticCommNumber->Show();
		txtCommNumber->Show();
		spinCommNumber->Show();
	}
	else
	{
		pnlFlags->Hide();
		staticHandshaking->Hide();
		chcHandshaking->Hide();
		staticDataBits->Hide();
		chcDataBits->Hide();
		staticParity->Hide();
		chcParity->Hide();
		staticStopBits->Hide();
		chcStopBits->Hide();
		txtCommNumber->Hide();
		staticCommNumber->Hide();
		spinCommNumber->Hide();
	}
	//pnlFlags->Update();
	ArrangeGUI();
	Update(); //##No parece ser imprescindible, pero por las dudas se lo llama. Verificar.
}
