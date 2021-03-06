///////////////////////////////////////////////////////////////////////////////
// Name:        tests/controls/clientsize.cpp
// Purpose:     Client vs. window size handling unit test
// Author:      Vaclav Slavik
// Created:     2008-02-12
// RCS-ID:      $Id: clientsize.cpp 53740 2008-05-25 02:56:22Z VZ $
// Copyright:   (c) 2008 Vaclav Slavik <vslavik@fastmail.fm>
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/app.h"
    #include "wx/window.h"
#endif // WX_PRECOMP

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class ClientSizeTestCase : public CppUnit::TestCase
{
public:
    ClientSizeTestCase() { }

    virtual void setUp();
    virtual void tearDown();

private:
    CPPUNIT_TEST_SUITE( ClientSizeTestCase );
        CPPUNIT_TEST( ClientToWindow );
        CPPUNIT_TEST( WindowToClient );
    CPPUNIT_TEST_SUITE_END();

    void ClientToWindow();
    void WindowToClient();

    wxWindow *m_win;

    DECLARE_NO_COPY_CLASS(ClientSizeTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( ClientSizeTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( ClientSizeTestCase, "ClientSizeTestCase" );

// ----------------------------------------------------------------------------
// test initialization
// ----------------------------------------------------------------------------

void ClientSizeTestCase::setUp()
{
    m_win = wxTheApp->GetTopWindow();
}

void ClientSizeTestCase::tearDown()
{
    m_win = NULL;
}

// ----------------------------------------------------------------------------
// tests themselves
// ----------------------------------------------------------------------------

void ClientSizeTestCase::ClientToWindow()
{
    CPPUNIT_ASSERT(m_win->GetSize() ==
                   m_win->ClientToWindowSize(m_win->GetClientSize()));
}

void ClientSizeTestCase::WindowToClient()
{
    CPPUNIT_ASSERT(m_win->GetClientSize() ==
                   m_win->WindowToClientSize(m_win->GetSize()));
}
