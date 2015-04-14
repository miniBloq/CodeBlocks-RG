////////////////////////////////////////////////////////////////////
// Name:		camera header
// File:		camera.h
// Purpose:		interface for the CCamera class.
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:	
//
////////////////////////////////////////////////////////////////////

#ifndef _CAMERA_H
#define _CAMERA_H

//define externall classes
class CCamView;
class CwxopencvWorker;
class CGUIFrame;

class CCamera 
{

// public methods
public:
	// contructor
	CCamera( );
	~CCamera( );
	// get frame method
	IplImage *GetIFrame( );

	// initialize camera frame def
	int Init(  );
	int Run();
	void Start( );
	void Stop( );
	void PauseResume( );
	int GetSize( );
	void IsChanged( );

// data
public:
	// status flags
	bool m_isRunning;
	bool m_isAvi;
	bool m_isPause;

	bool m_bProcBusy;
	int m_bIsChange;

	CvCapture*			m_pCapture;
	CCamView*			m_pCameraView;
	CGUIFrame*			m_pFrame;
	CwxopencvWorker*	m_pWorker;

	int			m_nWidth;
	int			m_nHeight;

// protected data
protected:
	IplImage*	m_pVideoImg;

	double		m_nFpsAlpha;
	double		m_nFps;
	char		m_strFps[255];
	double		m_timePrevFrameStamp;
	double		m_timeCurrFrameStamp;
	int			m_nTotalFrames;

// Implementation
protected:
	void GetNextFrame( void* );
	
};

#endif 
