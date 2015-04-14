////////////////////////////////////////////////////////////////////
// Name:		wxopencv Main Routine
// File:		wxopencv.cpp
// Purpose:		Main routine for wxopencv
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:
//
////////////////////////////////////////////////////////////////////

// opencv headers
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"

// wxwindows headers
#include "wx/wxprec.h"
#include "wx/statline.h"
#include "wx/minifram.h"
#include "wx/thread.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// custom headers
#include "gui/frame.h"
#include "gui/camview.h"
#include "camera/camera.h"
#include "worker.h"

// include main header
#include "wxopencv.h"


IMPLEMENT_APP(Cwxopencv)

//		***** CLASS Cwxopencv *****
////////////////////////////////////////////////////////////////////
// events table
BEGIN_EVENT_TABLE(Cwxopencv, wxApp)
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////
// Method:	On Init
// Class:	Cwxopencv
// Purose:	initialize my application
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
bool Cwxopencv::OnInit( )
{
	// create camera object
	m_pCamera = new CCamera( );

	// create widows frame
	CGUIFrame* m_pFrame = new CGUIFrame( NULL, "wxOpenCv Demo",
		                 wxPoint(-1, -1), wxSize(640, 600) );

	// Show the frame
	m_pFrame->Show(TRUE);
	SetTopWindow(m_pFrame);

	// set parent
	m_pFrame->m_pWxopencv = this;

	// build worker thread to process video stream
	m_pWxopencvWorker = new CwxopencvWorker( m_pFrame );
	// create thread or fail on exit
	if ( m_pWxopencvWorker->Create() != wxTHREAD_NO_ERROR )
	{
		wxExit( );
	}

	// exchange data if gui defined
	CCamView *pCamView = m_pFrame->GetCameraView();

	// link robot to GUI
	m_pFrame->m_pWorker = m_pWxopencvWorker;
	m_pWxopencvWorker->m_pCamera = m_pCamera;
	m_pCamera->m_pWorker = m_pWxopencvWorker;

	// initialize camera 
    if( m_pCamera->Init(  ) == 0 )
    {		
        wxMessageBox( "Can't initialize camera. Try to change format",
					"Error" );
    }

	m_pCamera->m_pCameraView = pCamView;
	m_pCamera->m_pFrame = m_pFrame;

	// Link camera view to camera object
	pCamView->m_pCamera = m_pCamera;

	// start the thread
	if ( m_pWxopencvWorker->Run() != wxTHREAD_NO_ERROR )
	{
		wxExit( );
	} 

	return TRUE;
}

////////////////////////////////////////////////////////////////////
// Method:	OnExit
// Class:	Cwxopencv
// Purose:	clean on app exit
// Input:	nothing
// Output:	status ?
////////////////////////////////////////////////////////////////////
int Cwxopencv::OnExit( )
{
	if( m_pWxopencvWorker != NULL )
	{
		m_pWxopencvWorker->Delete( );
	}
	m_pWxopencvWorker = NULL;

	delete( m_pCamera );

	return wxApp::OnExit();
}

