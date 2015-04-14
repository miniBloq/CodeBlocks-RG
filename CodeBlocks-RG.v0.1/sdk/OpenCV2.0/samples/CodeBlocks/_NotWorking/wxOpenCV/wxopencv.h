////////////////////////////////////////////////////////////////////
// Name:		wxopencv Header
// File:		wxopencv.h
// Purpose:		Main header with main defines for wxopencv
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:	
//
////////////////////////////////////////////////////////////////////

#ifndef _WXOPENCV_H
#define _WXOPENCV_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

#include "wx/wxprec.h"
#include "wx/thread.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers


// external classes
class CwxopencvWorker;
class CCamera;

class Cwxopencv : public wxApp
{
// public methods
public:

// public data
public:
	CwxopencvWorker*	m_pWxopencvWorker;
	CCamera*			m_pCamera;

// protected methods
protected:
	bool OnInit( );
	int OnExit( );

	DECLARE_EVENT_TABLE()
};

#endif
