////////////////////////////////////////////////////////////////////
// Name:		implementation of the CCamView class
// File:		camview.cpp
// Purpose:		eye/camera view/GUI system control methods
//
// Created by:	Larry Lart on 22-Feb-2006
// Updated by:
//
// Copyright:	(c) 2006 Larry Lart
////////////////////////////////////////////////////////////////////

// system header
#include <math.h>
#include <stdio.h>
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"

#ifdef __GNUG__
#pragma implementation
#pragma interface
#endif

#include "wx/wxprec.h"
#include <wx/image.h>

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// other headers
#include "../wxopencv.h"
#include "../camera/camera.h"

// main header
#include "camview.h"

// implement message map
BEGIN_EVENT_TABLE(CCamView, wxWindow)
	EVT_PAINT( CCamView::OnPaint )
	EVT_SIZE( CCamView::OnSize )
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////
// Method:	Constructor
// Class:	CCamView
// Purose:	build my CCamView object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamView::CCamView( wxWindow *frame, const wxPoint& pos, const wxSize& size ):
			wxWindow(frame, -1, pos, size, wxSIMPLE_BORDER )
{
	m_pCamera = NULL;

	// set my canvas width/height
	m_nWidth = size.GetWidth( );
	m_nHeight = size.GetHeight( );

	m_bDrawing = false;

	m_bNewImage = 0;
}

////////////////////////////////////////////////////////////////////
// Method:	Destructor
// Class:	CCamView
// Purose:	destroy my object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamView::~CCamView( )
{
	m_pCamera = NULL;
}

////////////////////////////////////////////////////////////////////
// Method:	Is Capture Enabled
// Class:	CCamView
// Purose:	check if camera is initialized
// Input:	nothing
// Output:	bool yes/no
////////////////////////////////////////////////////////////////////
bool CCamView::IsCaptureEnabled( )
{
//	return( m_pCamera->IsInitialized( ) );
	return( 1 );
}

////////////////////////////////////////////////////////////////////
// Method:	OnPaint
// Class:	CCamView
// Purose:	on paint event
// Input:	reference to paint event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	Draw( dc );
}

////////////////////////////////////////////////////////////////////
// Method:	Draw
// Class:	CCamView
// Purose:	camera drawing
// Input:	reference to dc
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::Draw( wxDC& dc )
{
	//##2010.08.08:
	// check if dc available
	//if( !dc.Ok( ) || m_bDrawing == true ){ return; }
	if( !dc.IsOk( ) || m_bDrawing == true ){ return; }

		m_bDrawing = true;

        //##2010.08.08:
		//dc.BeginDrawing();

		int x,y,w,h;
		dc.GetClippingBox( &x, &y, &w, &h );
		// if there is a new image to draw
		if( m_bNewImage )
		{
			dc.DrawBitmap( m_pBitmap, x, y );
			m_bNewImage = false;
		} else
		{
			// draw inter frame ?
		}

        //##2010.08.08:
		//dc.EndDrawing();

		m_bDrawing = false;

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	OnDraw
// Class:	CCamView
// Purose:	CCamView drawing
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::DrawCam( IplImage* pImg )
{
//	return;
	if( m_bDrawing ) return;
	m_bDrawing = true;
	int i = 0;

	// if there was an image then we need to update view
    if( pImg )
    {
        IplImage* pDstImg = cvCloneImage( pImg ); //m_Canvas.GetImage();

		int nCamWidth = m_pCamera->m_nWidth;
		int nCamHeight = m_pCamera->m_nHeight;

		// draw a rectangle
		cvRectangle( pDstImg,
					cvPoint( 10, 10 ),
					cvPoint( nCamWidth-10, nCamHeight-10 ),
					CV_RGB( 0,255,0 ), 1 );


		// process image from opencv to wxwidgets
		unsigned char *rawData;
		// draw my stuff to output canvas
		CvSize roiSize;
		int step = 0;
		// get raw data from ipl image
		cvGetRawData( pDstImg, &rawData, &step, &roiSize );
		// convert data from raw image to wxImg
		wxImage pWxImg = wxImage( nCamWidth, nCamHeight, rawData, TRUE );
		// convert to bitmap to be used by the window to draw
		m_pBitmap = wxBitmap( pWxImg.Scale(m_nWidth, m_nHeight) );

		m_bNewImage = true;
		m_bDrawing = false;

		Refresh( FALSE );

		Update( );

		cvReleaseImage( &pDstImg );

    }

}

////////////////////////////////////////////////////////////////////
// Method:	CheckUpdate
// Class:	CCamView
// Purose:	CHeck for updates
// Input:	reference to size event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::CheckUpdate()
{
	Update( );
}

////////////////////////////////////////////////////////////////////
// Method:	OnSize
// Class:	CCamView
// Purose:	adjust on windows resize
// Input:	reference to size event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::OnSize( wxSizeEvent& even )
{
	int nWidth = even.GetSize().GetWidth();
	int nHeight = even.GetSize().GetHeight();

	m_nWidth = nWidth;
	m_nHeight = nHeight;

}
