/***************************************************************
 * Name:      dlgMain.h
 * Purpose:   Defines Application Frame
 * Author:    j ()
 * Created:   2009-10-02
 * Copyright: j ()
 * License:
 **************************************************************/

#ifndef dlgMain_h
#define dlgMain_h

//(*Headers(dlgMain)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/spinbutt.h>
//*)

#include <wx/timer.h>
#include <wx/strconv.h>
#include "include/win32/serport.h"


//Forward declarations:
class Ticker;

//Class declarations:
class MyTextCtrl : public wxTextCtrl
{
private:
	wxWindow *Parent;
	wxSerialPort *Serial;
	wxTextCtrl *TxtPartner;

public:
	//##Mejorar el pasaje de textTx:
    MyTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value,
               const wxPoint &pos, const wxSize &size, int style = 0,
               const wxValidator& validator = wxDefaultValidator,
               const wxString& name = wxTextCtrlNameStr)
        : wxTextCtrl(parent, id, value, pos, size, style)
    {
        //m_hasCapture = false;
        Parent = parent;
        Serial = NULL;
        TxtPartner = NULL;
    }

	void setSerialPort(wxSerialPort* serial)
	{
		Serial = serial;
	}

	void SetPartner(wxTextCtrl *partner)
	{
		TxtPartner = partner;
	}

	//void OnKeyDown(wxKeyEvent& event);
    //void OnKeyUp(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);
/*
    void OnText(wxCommandEvent& event);
    void OnTextEnter(wxCommandEvent& event);
    void OnTextURL(wxTextUrlEvent& event);
    void OnTextMaxLen(wxCommandEvent& event);

    void OnTextCut(wxClipboardTextEvent & event);
    void OnTextCopy(wxClipboardTextEvent & event);
    void OnTextPaste(wxClipboardTextEvent & event);

    void OnMouseEvent(wxMouseEvent& event);

    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);

    static bool ms_logKey;
    static bool ms_logChar;
    static bool ms_logMouse;
    static bool ms_logText;
    static bool ms_logFocus;
    static bool ms_logClip;

private:
    static inline wxChar GetChar(bool on, wxChar c) { return on ? c : _T('-'); }

    void LogKeyEvent(const wxChar *name, wxKeyEvent& event) const;
    void LogClipEvent(const wxChar *what, wxClipboardTextEvent& event);

    bool m_hasCapture;
*/
//##:
private:
    DECLARE_EVENT_TABLE()
};


class dlgMain: public wxDialog
{
	private:
		bool firstTime;

    public:
        dlgMain(wxWindow* parent,wxWindowID id = -1);
        virtual ~dlgMain();

        //(*Handlers(dlgMain)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnbuttonOpenClick(wxCommandEvent& event);
        void OnbtnOpenClick(wxCommandEvent& event);
        void OnbtnOpenCommClick(wxCommandEvent& event);
        void OnbtnCloseCommClick(wxCommandEvent& event);
        void OnchcBaudRateSelect(wxCommandEvent& event);
        void OnspinCommNumberChange(wxSpinEvent& event);
        //void OntxtTxRxText(wxCommandEvent& event);
        void OnchkStayOnTopClick(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnbtnDTRClick(wxCommandEvent& event);
        void OnbtnRTSClick(wxCommandEvent& event);
        void OnchkStayOnTopClick1(wxCommandEvent& event);
        void OnchkShowConfigClick(wxCommandEvent& event);
        //*)

		void OnResize(wxSizeEvent& event);
		void OnShow(wxShowEvent& event);

        //(*Identifiers(dlgMain)
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL2;
        static const long ID_TEXTCTRL4;
        static const long ID_TEXTCTRL3;
        static const long ID_SPLITRXTX;
        static const long ID_PANEL1;
        static const long ID_NOTEBOOK1;
        static const long ID_CHECKSTAYONTOP;
        static const long ID_CHECKSHOWCONFIG;
        static const long ID_BUTTONDTR;
        static const long ID_CHECKDTR;
        static const long ID_CHECKDSR;
        static const long ID_CHECKDCD;
        static const long ID_BUTTONRTS;
        static const long ID_CHECKRTS;
        static const long ID_CHECKCTS;
        static const long ID_CHECKRING;
        static const long ID_PANEL_FLAGS;
        static const long ID_STATICTEXT4;
        static const long ID_CHCHANDSHAKING;
        static const long ID_STATICDATABITS;
        static const long ID_CHCDATABITS;
        static const long ID_STATICPARITY;
        static const long ID_CHCPARITY;
        static const long ID_STATICSTOPBITS;
        static const long ID_CHOICSTOPBITS;
        static const long ID_STATICBAUDRATE;
        static const long ID_CHCBAUDRATE;
        static const long ID_STATICCOMM;
        static const long ID_TEXTCOMM;
        static const long ID_SPINCOMM;
        static const long ID_BUTTONOPEN;
        static const long ID_BUTTONCLOSE;
        static const long ID_PANEL3;
        //*)

		void dlgMain::ArrangeGUI();

        //(*Declarations(dlgMain)
        wxStaticText* staticBaudrate;
        wxTextCtrl* txtCommNumber;
        wxPanel* pnlControls;
        wxCheckBox* chkCTS;
        wxButton* btnOpenComm;
        wxChoice* chcStopBits;
        wxTextCtrl* txtRx;
        wxChoice* chcParity;
        wxStaticText* staticDataBits;
        wxFlexGridSizer* flexControls;
        wxNotebook* noteRxTx;
        wxChoice* chcDataBits;
        wxCheckBox* chkShowConfig;
        wxPanel* Panel1;
        wxChoice* chcBaudRate;
        wxStaticText* staticStopBits;
        wxPanel* pnlFlags;
        wxBoxSizer* boxTxRx;
        wxStaticText* staticParity;
        MyTextCtrl* txtTx;
        wxCheckBox* chkDTR;
        wxCheckBox* chkRING;
        wxButton* btnRTS;
        wxStaticText* staticHandshaking;
        wxStaticText* staticCommNumber;
        wxButton* btnDTR;
        wxChoice* chcHandshaking;
        wxSplitterWindow* splitRxTx;
        wxButton* btnCloseComm;
        wxCheckBox* chkStayOnTop;
        wxCheckBox* chkDSR;
        wxFlexGridSizer* flexHandshaking;
        wxPanel* Panel2;
        wxSpinButton* spinCommNumber;
        MyTextCtrl* txtTxRx;
        wxCheckBox* chkRTS;
        wxCheckBox* chkDCD;
        //*)

        Ticker* timer;
        int rxSampleTime_ms;

        DECLARE_EVENT_TABLE()

public:
		char *commDevName;
        wxSerialPort_DCS dcs;
        wxSerialPort serialPort;
        wxString strComPortName;

		//##Borrar: void OntxtTxRxChar(wxKeyEvent& event);
		//##Borrar: void OnKeyUp(wxKeyEvent& event);
};

/*
##Esto habría que pasarlo a threads, sobre todo por los múltiples terminales que se espera que puedan
correr simultáneamente, ya que puede que haya límite de timers en los diferentes sistemas operativos:
##Es más: Habría que unificar la clase de puerto serie con SNAPI y meter este timer adentro para emular
interrupciones, etc.:
*/
class Ticker : public wxTimer
{
	protected:
		wxWindow *Owner;
	public:
		Ticker(wxWindow *owner) : wxTimer(owner)
		{
			Owner = owner;
		};

		void Notify()
		{
			//##Debug: ((dlgMain*)Owner)->txtTxRx->AppendText(wxT("."));

			//Datos recibidos:
			char buffer[10]; //##Hacer el tamaño configurable.
			unsigned int readCount = ((dlgMain*)Owner)->serialPort.Read(buffer, sizeof(buffer)-1);
			if ( (readCount < sizeof(buffer)) && (readCount > 0) )
			{
				buffer[readCount] = '\0';
				//##Esto tiene que ser configurable:
				((dlgMain*)Owner)->txtTxRx->SetDefaultStyle(wxTextAttr(*wxGREEN));

				//##Esto debería hacerse sólo una vez, cuando se cambia la configuración de color, no hace falta aquí:
				//((dlgMain*)Owner)->txtRx->SetDefaultStyle(wxTextAttr(*wxGREEN));

				//##Ver si hay que reemplazar las funciones de conversión por algo tipo FromWChar, o ToWChar:
				((dlgMain*)Owner)->txtTxRx->AppendText(wxConvLocal.cMB2WC(buffer));
				((dlgMain*)Owner)->txtRx->AppendText(wxConvLocal.cMB2WC(buffer));
				//((dlgMain*)Owner)->txtTxRx->WriteText(wxConvLocal.cMB2WC(buffer));

				//##Esto tiene que restaurar el color que había, no el azul necesariamente:
				((dlgMain*)Owner)->txtTxRx->SetDefaultStyle(wxTextAttr(*wxBLUE));
			}

			//Líneas del port:
			int flags = ((dlgMain*)Owner)->serialPort.GetLineState();
			if (flags & wxSERIAL_LINESTATE_CTS)
				((dlgMain*)Owner)->chkCTS->SetValue(true);
			else
				((dlgMain*)Owner)->chkCTS->SetValue(false);

			if (flags & wxSERIAL_LINESTATE_DSR)
				((dlgMain*)Owner)->chkDSR->SetValue(true);
			else
				((dlgMain*)Owner)->chkDSR->SetValue(false);

			if (flags & wxSERIAL_LINESTATE_RING)
				((dlgMain*)Owner)->chkRING->SetValue(true);
			else
				((dlgMain*)Owner)->chkRING->SetValue(false);

			if (flags & wxSERIAL_LINESTATE_DCD)
				((dlgMain*)Owner)->chkDCD->SetValue(true);
			else
				((dlgMain*)Owner)->chkDCD->SetValue(false);
		};
};


#endif // dlgMain_h
