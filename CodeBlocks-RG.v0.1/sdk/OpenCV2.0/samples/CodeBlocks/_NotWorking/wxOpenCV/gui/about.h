////////////////////////////////////////////////////////////////////
// Package:		GUI About definition
// File:		about.h
// Purpose:		define about window
//
// Created by:	Larry Lart on 22-Jul-2006
// Updated by:  
//
// Copyright:	(c) 2006 Larry Lart
// Licence:		Digital Entity
////////////////////////////////////////////////////////////////////

#ifndef _ABOUT_H 
#define _ABOUT_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

// class:	CWxOpencvAbout
///////////////////////////////////////////////////////
class CWxOpencvAbout : public wxDialog
{
// methods
public:
    CWxOpencvAbout(wxWindow *parent);
};


#endif
