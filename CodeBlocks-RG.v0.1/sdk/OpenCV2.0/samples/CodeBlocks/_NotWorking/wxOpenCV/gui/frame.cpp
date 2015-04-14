////////////////////////////////////////////////////////////////////
// Name:		implementation of the CGUIFrame class 
// File:		mainframe.cpp
// Purpose:		GUI mainframe system control methods
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:	
//
// Copyright:	(c) 2004 Larry Lart
// Licence:		Digital Entity
////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation
#pragma interface
#endif

// system includes
//#include "../stdafx.h"
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"


#include "wx/wxprec.h"
#include "wx/statline.h"
#include "wx/minifram.h"
#include "wx/thread.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// other includes
#include "about.h"
#include "../wxopencv.h"
#include "camview.h"
#include "../camera/camera.h"
#include "../worker.h"

// WIDOWS specific define
#if defined(_WINDOWS)
#include <vfw.h>
#endif

#include "../camera.xpm"

// main header
#include "frame.h"

/////////////////////////////////////////////////////////////////////////////
// CGUIFrame

BEGIN_EVENT_TABLE(CGUIFrame, wxFrame)
	// menu items
	EVT_MENU( wxID_CAMSRC, CGUIFrame::OnVideoSource )
	EVT_MENU( wxID_CAMFORMAT, CGUIFrame::OnVideoFormat )
	EVT_MENU( wxID_ABOUT, CGUIFrame::OnAbout )
	EVT_MENU( wxID_EXIT, CGUIFrame::OnExit )
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////
// Method:	Constructor
// Class:	CGUIFrame
// Purose:	build my MainFrame object  
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CGUIFrame::CGUIFrame( wxFrame *frame, const wxString& title, 
					   const wxPoint& pos, const wxSize& size ):
	wxFrame(frame, -1, title, pos, size, wxSYSTEM_MENU | wxMAXIMIZE_BOX | wxMINIMIZE_BOX |wxCLOSE_BOX| wxCAPTION |wxRESIZE_BORDER )
{

	wxIcon icon( camera_xpm );
	SetIcon( icon );

	// set bg color for my frame 
	SetBackgroundColour( *wxLIGHT_GREY );

	// create status bar
	CreateStatusBar( 1 );

	// make file menu bar
	wxMenu *pFileMenu = new wxMenu( "", wxMENU_TEAROFF );
	pFileMenu->Append( wxID_ABOUT, "About" );
	pFileMenu->AppendSeparator( );
	pFileMenu->Append( wxID_EXIT, "Exit" );

	// make Vision menu bar
	wxMenu *pVisionMenu = new wxMenu;
	pVisionMenu->Append( wxID_CAMSRC, "Camera Source" );
	pVisionMenu->Append( wxID_CAMFORMAT, "Camera Format" );
	
	// make menu toolbar
	menuBar = new wxMenuBar;
	menuBar->Append( pFileMenu, "File" );
	menuBar->Append( pVisionMenu, "Camera");
	this->SetMenuBar(menuBar);
	
	// get client size 
	int width, height;
	this->GetClientSize(&width, &height);

	m_pMainPanel = new wxPanel(this, -1, wxPoint(0,0), wxSize(width,height), 0 );
	// build static/logical boxes

	// build static/logical boxes
	wxStaticBox *pCameraBox = new wxStaticBox( m_pMainPanel, -1, "camera", 
							wxPoint(2,0), wxSize(360,275) );

	// get my main static sizer by the box
	wxStaticBoxSizer *pMainSizer = new wxStaticBoxSizer( pCameraBox, wxHORIZONTAL );
	
	// build cam canvas
	m_pCamView = new CCamView( m_pMainPanel, wxPoint(5,15), wxSize(354, 256) );
	pMainSizer->Add( m_pCamView, 1, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL|wxEXPAND );

	m_pMainPanel->SetSizer( pMainSizer );
	pMainSizer->SetSizeHints( m_pMainPanel );	
	m_pMainPanel->SetAutoLayout( TRUE );


	wxBoxSizer *pTopSizer = new wxBoxSizer(wxVERTICAL);
	pTopSizer->Add( m_pMainPanel, 1, wxALIGN_CENTER|wxEXPAND, 0 );
	SetSizer( pTopSizer );
	
	// display my stuff
	SetAutoLayout( TRUE );

}

////////////////////////////////////////////////////////////////////
// Method:	Destructor
// Class:	CGUIFrame
// Purose:	delete/destroy GUI MainFrame object  
// Input:	mothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CGUIFrame::~CGUIFrame( )
{
	// first pause camera
	m_pCamView->m_pCamera->PauseResume( );

	// tell first to the worker to exit
//	m_pWorker->Pause( );
	m_pWorker->Delete( );

	// clean on exit
	delete( m_pCamView );
	delete( m_pMainPanel );

	// set to null
	m_pWxopencv->m_pWxopencvWorker = NULL;
	m_pMainPanel = NULL;
	m_pCamView = NULL;
	m_pWorker = NULL;
	m_pWxopencv = NULL;
}

////////////////////////////////////////////////////////////////////
// Method:	SetParentApp
// Class:	CGUIFrame
// Purose:	Set/propagate pointer to parrent application here 
// Input:	pointer to parent app - umouse
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::SetParentApp( Cwxopencv *pWxopencv )
{
	m_pWxopencv = pWxopencv;
}

////////////////////////////////////////////////////////////////////
// Method:	Get Camera view
// Class:	CGUIFrame
// Purose:	return pointer to camera view
// Input:	nothing
// Output:	pointer to camera view
////////////////////////////////////////////////////////////////////
CCamView* CGUIFrame::GetCameraView()
{
	return( m_pCamView );
}

////////////////////////////////////////////////////////////////////
// Method:		On About
// Class:		CGUIFrame
// Purpose:		display about dialog
// Input:		pointer to event
// Output:		nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::OnAbout( wxCommandEvent& event )
{
	CWxOpencvAbout dialog(this);
    dialog.ShowModal();

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	On Video Source
// Class:	CGUIFrame
// Purose:	when video source menu option selected
// Input:	reference to event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::OnVideoSource( wxCommandEvent& event )
{
    CCamView *pView = GetCameraView();

// for widnows do this
#ifdef _WINDOWS
	// hack to get the windows handler
	typedef struct CvCaptureCAM_VFW
	{
		void* vtable;
		CAPDRIVERCAPS caps;
		HWND   capWnd;
		VIDEOHDR* hdr;
		DWORD  fourcc;
		HIC    hic;
		IplImage* rgb_frame;
		IplImage frame;
	} CvCaptureCAM_VFW;


	CvCapture* ptest = pView->m_pCamera->m_pCapture;
	CvCaptureCAM_VFW* p = (CvCaptureCAM_VFW*) ptest;

	capDlgVideoSource( p->capWnd );
#elif _LINUX
	// else ... TODO
#endif

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	On Video Format
// Class:	CGUIFrame
// Purose:	when video format menu option selected
// Input:	reference to event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::OnVideoFormat( wxCommandEvent& event )
{
    CCamView *pView = GetCameraView();

// for widnows do this
#ifdef _WINDOWS
	// hack to get the windows handler
	typedef struct CvCaptureCAM_VFW
	{
		void* vtable;
		CAPDRIVERCAPS caps;
		HWND   capWnd;
		VIDEOHDR* hdr;
		DWORD  fourcc;
		HIC    hic;
		IplImage* rgb_frame;
		IplImage frame;
	} CvCaptureCAM_VFW;


	CvCapture* ptest = pView->m_pCamera->m_pCapture;
	CvCaptureCAM_VFW* p = (CvCaptureCAM_VFW*) ptest;

	// first pause camera
	pView->m_pCamera->PauseResume( );

	capDlgVideoFormat( p->capWnd );

	// mark change and wait for thread to restart camera
	pView->m_pCamera->IsChanged( );

#elif _LINUX
	// else ... TODO
#endif

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	SetStatusBarText
// Class:	CGUIFrame
// Purose:	when minimize
// Input:	mothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::SetStatusBarText( const char* strText )
{
	GetStatusBar()->SetStatusText( strText );

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	ResetLayout
// Class:	CGUIFrame
// Purose:	tell all components to reset layout 
// Input:	mothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::ResetLayout( )
{
	GetSizer()->Layout( );
	m_pMainPanel->Layout();
}

////////////////////////////////////////////////////////////////////
// Method:		On Exit
// Class:		CGUIFrame
// Purpose:		exit program
// Input:		pointer to event
// Output:		nothing
////////////////////////////////////////////////////////////////////
void CGUIFrame::OnExit( wxCommandEvent& WXUNUSED(pEvent) )
{
	Close( );
	return;
}
