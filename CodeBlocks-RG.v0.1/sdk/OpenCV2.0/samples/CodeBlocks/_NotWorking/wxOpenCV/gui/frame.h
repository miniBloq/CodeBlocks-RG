////////////////////////////////////////////////////////////////////
// Name:		Main Frame header
// File:		mainframe.h
// Purpose:		interface for the CMainFrame class.
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:	
//
////////////////////////////////////////////////////////////////////

#ifndef _MAINFRAME_H
#define _MAINFRAME_H

// DEBUG
#ifndef CRTDBG_MAP_ALLOC
#define CRTDBG_MAP_ALLOC
#endif

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// external classes
class Cwxopencv;
class CCamView;
class CwxopencvWorker;

//// IDs for the controls and the menu commands
enum
{
	// menu items
	wxID_CAMSRC			= 1800,
	wxID_CAMFORMAT		= 1801,
};

static wxMenuBar *menuBar = NULL;

class CGUIFrame : public wxFrame
{
// public methods	
public:
	CGUIFrame( wxFrame *frame, const wxString& title, 
				const wxPoint& pos, const wxSize& size );
	virtual ~CGUIFrame( );
	CCamView* GetCameraView( );
	void SetParentApp( Cwxopencv *pWxopencv );
	void SetStatusBarText( const char* strText );
	void ResetLayout( );

// public data
public:
	Cwxopencv*			m_pWxopencv;
	CwxopencvWorker*	m_pWorker;

// Protected data
protected: 
	CCamView*	m_pCamView;
	wxPanel*	m_pMainPanel;

// message map functions
protected:
	void OnVideoSource( wxCommandEvent& event );
	void OnVideoFormat( wxCommandEvent& event );
	void OnAbout( wxCommandEvent& event );
	void OnExit( wxCommandEvent& WXUNUSED(pEvent) );

	DECLARE_EVENT_TABLE()
};

#endif
