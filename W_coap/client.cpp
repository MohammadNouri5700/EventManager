//
// Created by aziz on 16.08.21.
//

#include "client.h"
#include <iostream>



CoAP::client::client():Coap("Coap.me", "5683"), pdu(), Session(), handler(NULL)
{

}

CoAP::client::~client()
{

}

void CoAP::client::Act()
{

    make_pdu();

    Process();
}

void CoAP::client::End()
{
    Session.Release();
    Coap::End();
}

void CoAP::client::Init()
{
    Coap::Init();
    ctx.Handler(handler);
    make_session();

}

void CoAP::client::make_pdu()
{

    pdu.Init(type, code, Session.pGet());

}

void CoAP::client::Process()
{
    pdu.Show();
    //pdu.Send(Session);
    Session.Send(pdu.pGet());
    ctx.iIoProcess(COAP_IO_WAIT);
}

void CoAP::client::make_session()
{

    if (!Session.bNewClient(ctx.pGet(), &Destination, Protocol)) {
        coap_log(LOG_EMERG, "cannot create aClient apSession(aClient)\n");
        End();
    }

}