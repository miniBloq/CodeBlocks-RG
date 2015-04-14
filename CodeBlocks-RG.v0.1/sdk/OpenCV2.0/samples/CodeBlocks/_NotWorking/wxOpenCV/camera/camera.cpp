////////////////////////////////////////////////////////////////////
// Name:		implementation of the CCamera class 
// File:		camera.cpp
// Purpose:		camera system control methods
//
// Created by:	Larry Lart based in various samples by OpenCV team
// Updated by:	Larry Lart on 22-Feb-2004
//				Larry Lart on 24-Feb-2004
//				Larry Lart on 18-Mar-2005
//
// Copyright:	(c) 2004-2005 Larry Lart
////////////////////////////////////////////////////////////////////

#define _GUI_RUN 1

// system includes

// other system includes
#include "highgui.h"
//#include <vfw.h>
#include "cv.h"
#include "cvaux.h"
#include "cvcam.h"

// switch
#define WIN32_LARRY

#ifndef WIN32_LARRY
#include "cvcam.h"
#endif

// other local includes
#include "../wxopencv.h"
#include "../worker.h"

// GUI include
#ifdef _GUI_RUN
#include "../gui/camview.h"
#include "../gui/frame.h"
#endif

// Main header
#include "camera.h"

#ifndef WIN32_LARRY
        void testcallback(void* _image);
        IplImage* m_pLnxFrame;
#endif
                                                                                                                             
////////////////////////////////////////////////////////////////////
// Method:	Constructor
// Class:	CCamera
// Purose:	build my Camera object  
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamera::CCamera(  )
{
	m_pWorker = NULL;
	m_isRunning = false;
	m_isPause = false;
	// the new camera implementation
	m_pVideoImg = NULL;
	m_nFps = -1;
	m_nFpsAlpha = 0.1;
	m_isAvi = false;
	
	m_bIsChange = 0;
}

////////////////////////////////////////////////////////////////////
// Method:	Destructor
// Class:	CCamera
// Purose:	destroy my object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamera::~CCamera( )
{
    //Uninitialize( );
	if( m_isRunning ) cvReleaseCapture( &m_pCapture );
	if( m_pVideoImg )
	{
		cvReleaseImage( &m_pVideoImg );
	}

	m_pVideoImg = NULL;
	m_pWorker = NULL;
	m_pCapture = NULL;
	m_pCameraView = NULL;
	m_pFrame = NULL;
}

////////////////////////////////////////////////////////////////////
// Method:	Init
// Class:	CCamera
// Purose:	initialize my startup variables
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
int CCamera::Init(  )
{
	m_timeCurrFrameStamp = m_pWorker->GetTime( );
	m_timePrevFrameStamp = m_timeCurrFrameStamp;
	
	return( 1 );
}

////////////////////////////////////////////////////////////////////
// Method:	GetSize
// Class:	CCamera
// Purose:	initialize my startup variables
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
int CCamera::GetSize( )
{
	// now get my properties
	m_nWidth = (int) cvGetCaptureProperty( m_pCapture, CV_CAP_PROP_FRAME_WIDTH );
	m_nHeight = (int) cvGetCaptureProperty( m_pCapture, CV_CAP_PROP_FRAME_HEIGHT );
	// set camview size
	m_pCameraView->SetSize( m_nWidth, m_nHeight );
	m_pFrame->ResetLayout( );

	return( 0 );
}

////////////////////////////////////////////////////////////////////
// Method:	Start
// Class:	CCamera
// Purose:	Start capture
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamera::Start( )
{
#ifdef WIN32_LARRY
	m_pCapture = cvCaptureFromCAM( -1 );

	// grab first frame to initialize format
	IplImage* pFrame = cvQueryFrame( m_pCapture );
	// get camera's size
	GetSize( );

#else
	int ncameras = cvcamGetCamerasCount();
	printf("DEBUG :: Found cameras=%d\n", ncameras );
	int w = 640;
	int h = 480;
	int nCam = 0;
	int t=1;
	int p=1;
	
	cvcamSetProperty(nCam, CVCAM_RNDWIDTH,  &w );
	cvcamSetProperty(nCam, CVCAM_RNDHEIGHT, &h );

	cvcamSetProperty(nCam, CVCAM_PROP_ENABLE, &t );

	int width = 320;
	int height = 200;


	HWND MyWin = (HWND)m_pCameraView->GetHandle();
	cvcamSetProperty(nCam, CVCAM_PROP_WINDOW, &MyWin ); 
	cvcamSetProperty(nCam, CVCAM_PROP_RENDER, &p );  

	
	cvcamSetProperty(0, CVCAM_PROP_CALLBACK, (void*)testcallback );
	cvcamInit();
	Sleep( 5000 );
	cvcamStart();
#endif	

	m_isRunning = true;
}

////////////////////////////////////////////////////////////////////
// Method:	PauseResume
// Class:	CCamera
// Puprose:	pause/resume capture
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamera::PauseResume( )
{
	if( m_isPause )
	{
		m_isPause = false;
	} else
	{
		m_isPause = true;
	}
}

////////////////////////////////////////////////////////////////////
// Method:	IsChanged
// Class:	CCamera
// Puprose:	mark flag change
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamera::IsChanged( )
{
	m_bIsChange = 1;
	m_isPause = true;
}

////////////////////////////////////////////////////////////////////
// Method:	Stop
// Class:	CCamera
// Purose:	Stop capture
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void  CCamera::Stop( )
{
	m_isRunning = false;
#ifdef WIN32_LARRY
	cvReleaseCapture( &m_pCapture );
	if( m_pVideoImg )
	{
		cvReleaseImage( &m_pVideoImg );
		m_pVideoImg = NULL;
	}
#else
	cvcamExit();
#endif

}

////////////////////////////////////////////////////////////////////
// feedback - only for linux
#ifndef WIN32_LARRY
void testcallback(void* _image)
{
	IplImage* image = (IplImage*)_image;
	cvLine(image, cvPoint(0, 0), cvPoint(image->width, image->height),CV_RGB(255, 0, 0), 1);
	m_pLnxFrame = image ;
}
#endif

////////////////////////////////////////////////////////////////////
// Method:	Get Next Frame
// Class:	CCamera
// Purpose:	get next frame from camera buffer
// Input:	pointer to void
// Output:	Nothing
////////////////////////////////////////////////////////////////////
void CCamera::GetNextFrame( void* )
{
    static int repositioning = 0;
    IplImage* pFrame = NULL;

	// get current frame time stamp
    m_timeCurrFrameStamp = m_pWorker->GetTime( );
	if( m_timeCurrFrameStamp - m_timePrevFrameStamp  < 5 )
		return;
	else
		m_timePrevFrameStamp = m_timeCurrFrameStamp;

#ifdef WIN32_LARRY	
	// get frame if any
 	pFrame = cvQueryFrame( m_pCapture );
#else
	// to test this - don't remmember how i got this working 
	// on linux 
	pFrame = m_pLnxFrame;
	// get frame in linux ?

	cvcamPause();
	cvcamGetProperty(0,CVCAM_PROP_RAW,&pFrame);
	cvcamResume();

	pFrame = cvCloneImage( fimg );

	Sleep(400);
#endif

	// if this was avi and frame is zero(end or none?) stop
    if( pFrame == 0 && m_isAvi )
    {
        //this->StopAvi( 0,0 );
        return;
	}

	////////////////////////////
	// if video window ? & frame ?
    if( pFrame )
    {
		// if no video image 
        if( !m_pVideoImg ) 
        {
            cvReleaseImage( &m_pVideoImg );
			m_pVideoImg = cvCreateImage( cvSize( m_nWidth, m_nHeight ), 8, 3 );
        }
		
		// check for the last origin of the frame
		if( pFrame->origin == 1 )
		{
			cvConvertImage( pFrame, m_pVideoImg, CV_CVTIMG_FLIP | CV_CVTIMG_SWAP_RB );
		} else
		{
			cvCopy( pFrame, m_pVideoImg, 0 );
		}		

#ifdef _GUI_RUN
		// Update gui
		m_pCameraView->DrawCam( m_pVideoImg );
#endif	
		
    }


	// If camera started
    if( m_isRunning )
    {
		// get current frame time stamp
        m_timeCurrFrameStamp = m_pWorker->GetTime( );
        // update fps
        if( m_nFps < 0 )
		{
            m_nFps = 1000 / ( m_timeCurrFrameStamp - m_timePrevFrameStamp );
		} else
		{	
            m_nFps = ( 1 - m_nFpsAlpha ) * m_nFps + m_nFpsAlpha * 
						1000 / ( m_timeCurrFrameStamp - m_timePrevFrameStamp );
		}
		// set current time stamp as previuos
        m_timePrevFrameStamp = m_timeCurrFrameStamp;
		// get info of number of frames per second in a string
		// for debuging/etc
        sprintf( m_strFps, "FPS: %5.1f", m_nFps );
		m_pFrame->SetStatusBarText( m_strFps );

    }
}

////////////////////////////////////////////////////////////////////
// Method:	GetIFrame
// Class:	CCamera
// Purose:	get last frame grabbed
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
IplImage *CCamera::GetIFrame( )
{
	return( m_pVideoImg );
}


////////////////////////////////////////////////////////////////////
// Method:	Run
// Class:	CCamera
// Purose:	Start to run my camera thread
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
int CCamera::Run( ) 
{

	if( !m_isPause )
	{
		// Get my next frame
		this->GetNextFrame( NULL );
	} else
	{
		if( m_bIsChange == 1 )
		{
			// check size
			Stop( );
			Start( );
			m_bIsChange = 0;
			m_isPause = 0;
		}
	}

	return( 0 );
}
