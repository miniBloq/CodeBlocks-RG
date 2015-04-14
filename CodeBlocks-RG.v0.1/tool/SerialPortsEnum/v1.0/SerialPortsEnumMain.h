/***************************************************************
 * Name:      SerialPortsEnumMain.h
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

#ifndef SERIALPORTSENUMMAIN_H
#define SERIALPORTSENUMMAIN_H

//(*Headers(SerialPortsEnumDialog)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/timer.h>
#include <windows.h>

//Forward declarations:
class Ticker;

class SerialPortsEnumDialog: public wxDialog
{
    private:
        //(*Handlers(SerialPortsEnumDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnchkStayOnTopClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(SerialPortsEnumDialog)
        static const long ID_TEXTCTRL1;
        static const long ID_CHKSTAYONTOP;
        static const long ID_BTNABOUT;
        //*)

    public:
        SerialPortsEnumDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~SerialPortsEnumDialog();

        //(*Declarations(SerialPortsEnumDialog)
        wxTextCtrl* txtSerialPorts;
        wxButton* btnAbout;
        wxCheckBox* chkStayOnTop;
        //*)

        Ticker* timer;

        DECLARE_EVENT_TABLE()
};


class Ticker : public wxTimer
{
	private:
		wxWindow *Owner;
        //vector<string> port_str;

	public:
		Ticker(wxWindow *owner) : wxTimer(owner)
		{
			Owner = owner;
		};

		void Notify()
        {
            //Debug:
            //((SerialPortsEnumDialog*)Owner)->txtSerialPorts->AppendText(".\n");

            ((SerialPortsEnumDialog*)Owner)->txtSerialPorts->Clear();

            //##256?
            for (int port_number = 1; port_number < 256; ++port_number)
            {
                wxString strCommNumber = wxT("\\\\.\\com");
                strCommNumber << port_number;
                HANDLE hFile = ::CreateFile(strCommNumber.c_str(), GENERIC_READ |
                                            GENERIC_WRITE, 0, NULL,
                                            OPEN_EXISTING, 0, NULL);

                if(hFile != INVALID_HANDLE_VALUE)
                {
                    ((SerialPortsEnumDialog*)Owner)->txtSerialPorts->AppendText(strCommNumber + "\n");
                }
                else
                {
                    DWORD err = GetLastError();
                    if (err == ERROR_ACCESS_DENIED ||
                        err == ERROR_SHARING_VIOLATION)
                    {
                        ((SerialPortsEnumDialog*)Owner)->txtSerialPorts->AppendText(strCommNumber + "\n");
                    }
                }
                CloseHandle(hFile);
            }
        }
};


#endif // SERIALPORTSENUMMAIN_H
