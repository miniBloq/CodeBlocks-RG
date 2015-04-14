/***************************************************************
 * Name:      SerialPortsEnumApp.h
 * Purpose:   Defines Application Class
 * Author:    Alan Kharsansky; Julián da Silva Gillig ()
 * Created:   2010-09-09
 * Copyright: Alan Kharsansky; Julián da Silva Gillig (http://multiplo.org)
 * License:
 **************************************************************/

#ifndef SERIALPORTSENUMAPP_H
#define SERIALPORTSENUMAPP_H

#include <wx/app.h>

class SerialPortsEnumApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // SERIALPORTSENUMAPP_H
