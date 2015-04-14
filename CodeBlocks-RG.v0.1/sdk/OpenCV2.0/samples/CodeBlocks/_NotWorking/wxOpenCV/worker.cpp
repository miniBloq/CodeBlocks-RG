////////////////////////////////////////////////////////////////////
// Package:		worker implementation
// File:		worker.cpp
// Purpose:		manage checking, switching tasks
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:
//
////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation
#pragma interface
#endif

// system headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>

// wxwidgets includes
#include "wx/wxprec.h"
#include "wx/thread.h"
#include <wx/string.h>
#include <wx/regex.h>

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// opencv includes
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"

#include "wxopencv.h"
#include "gui/frame.h"
#include "camera/camera.h"

// main header include
#include "worker.h"

////////////////////////////////////////////////////////////////////
// Method:	Constructor
// Class:	CwxopencvWorker
// Purpose:	Initialize my worker thread
// Input:	pointer to reference frame
// Output:	nothing
////////////////////////////////////////////////////////////////////
CwxopencvWorker::CwxopencvWorker( CGUIFrame *pFrame ) : wxThread( wxTHREAD_DETACHED )
{
	// get frame refrence
	m_pFrame = pFrame;

	// start life
	m_bLife = 1;

	m_pMutex = new wxMutex( );

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	Destructor
// Class:	CwxopencvWorker
// Purpose:	object destructor
// Input:	nothing
// Output:	nothing	
////////////////////////////////////////////////////////////////////
CwxopencvWorker::~CwxopencvWorker( )
{
	m_pMutex=NULL;
	m_pCamera=NULL;
	m_pFrame = NULL;
}

////////////////////////////////////////////////////////////////////
// Method:	On Exit
// Class:	CwxopencvWorker
// Purpose:	do soemthing on exit
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CwxopencvWorker::OnExit( )
{
	// destroy - clean my place
	delete( m_pMutex );
}

////////////////////////////////////////////////////////////////////
// Method:	GetTime
// Class:	CwxopencvWorker
// Purose:	routine to get time accurate - this would be called by
//			all other components to keep in sync
// Input:	nothing
// Output:	number = accurate time count
////////////////////////////////////////////////////////////////////
double CwxopencvWorker::GetTime( void )
{
	//
	struct timeb timeStamp;
	// get a time stamp
	ftime( &timeStamp );

	double nTime = (double) timeStamp.time*1000 + timeStamp.millitm;

	return( nTime );
	// i removed this for the moment - this was used to calculate time 
	//based on the cpu tick count
	//return (double)cvGetTickCount()*1e-3/(m_nCpuFreq+1e-10);
}

////////////////////////////////////////////////////////////////////
// Method:		Entry
// Class:		CwxopencvWorker
// Purpose:		the main executable body of my thread
// Input:		nothing
// Output:		void pointer
////////////////////////////////////////////////////////////////////
void *CwxopencvWorker::Entry( )
{
	int i = 0;
	m_bLife = 1;

	m_pCamera->Start( );

	////////////////////////////////////////////////////////////////
	// Start Life Cycle
	////////////////////////////////////////////////////////////////
	// loop as long as flag m_bLife = 1
	while( m_bLife )
	{
		if( TestDestroy( ) == 1 ) 
			break;

		///////////////////////////////////////////////////////////
		// START PROCESING BLOCK
		// first tell camera object to process one frame - if camera
		// is running
		if( m_pCamera->m_isRunning )
		{
			m_pCamera->Run( );

		}
		// the here you can insert your extra bit of processing
		// .... code

		// END PROCESSING BLOCK
		///////////////////////////////////////////////////////////

		wxThread::Sleep( 5 );

	}

	m_pCamera->Stop( );

    return NULL;
}
