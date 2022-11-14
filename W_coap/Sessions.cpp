//
// Created by aziz on 16.08.21.
//

#include "Sessions.h"

CoAP::Sessions::Sessions()
{

}

CoAP::Sessions::~Sessions()
{

}

bool CoAP::Sessions::bNewClient(coap_context_t *ctx, coap_address_t *dst, coap_proto_t protocol)
{

    if (!(apSession = coap_new_client_session(ctx, nullptr, dst, protocol)))
        return false;
    else
        return true;
}

///////////////
coap_session_t *CoAP::Sessions::pReference()
{
    return coap_session_reference (apSession);
}

void CoAP::Sessions::Disconnected(coap_nack_reason_t reason)
{
    coap_session_disconnected (apSession, reason);
}

void CoAP::Sessions::SetAppData(void *data)
{
    coap_session_set_app_data (apSession, data);
}

void *CoAP::Sessions::pGetAppData()
{
    return coap_session_get_app_data (apSession);
}

const coap_address_t *CoAP::Sessions::pGetAddrRemote()
{
    return coap_session_get_addr_remote (apSession);
}

const coap_address_t *CoAP::Sessions::PGetAddrLocal()
{
    return coap_session_get_addr_local (apSession);
}

coap_proto_t CoAP::Sessions::GetProto()
{
    return coap_session_get_proto (apSession);
}

coap_session_type_t CoAP::Sessions::GetType()
{
    return coap_session_get_type (apSession);
}

coap_session_state_t CoAP::Sessions::GetState()
{
    return coap_session_get_state (apSession);
}

int CoAP::Sessions::iGetIfindex()
{
    return coap_session_get_ifindex(apSession);
}

void *CoAP::Sessions::pGetTls(coap_tls_library_t *tls_lib)
{
    return coap_session_get_tls (apSession, tls_lib);
}
coap_context_t *CoAP::Sessions::pGetContext()
{
    return coap_session_get_context (apSession);
}

int CoAP::Sessions::iSetTypeClient()
{
    return coap_session_set_type_client (apSession);
}

void CoAP::Sessions::SetMtu(unsigned int mtu)
{
    coap_session_set_mtu (apSession, mtu);
}

size_t CoAP::Sessions::MaxPduSize()
{
    return coap_session_max_pdu_size (apSession);
}

void CoAP::Sessions::ClientSession(coap_context_t *ctx, const coap_address_t *local_if, const coap_address_t *server, coap_proto_t proto)
{
    apSession =  coap_new_client_session (ctx, local_if, server, proto);
}

void CoAP::Sessions::ClientSessionPsk(coap_context_t *ctx, const coap_address_t *local_if, const coap_address_t *server,
                                      coap_proto_t proto, const char *identity, const uint8_t *key, unsigned int key_len)
{
    apSession = coap_new_client_session_psk (ctx, local_if, server, proto, identity, key, key_len);
}

void CoAP::Sessions::NewClientSessionPsk2(coap_context_t *ctx, const coap_address_t *local_if,
        const coap_address_t *server, coap_proto_t proto,
        coap_dtls_cpsk_t *setup_data)
{
    apSession =coap_new_client_session_psk2 (ctx, local_if, server, proto, setup_data);
}

const coap_bin_const_t *CoAP::Sessions::pGetPskHint()
{
    return coap_session_get_psk_hint (apSession);
}

const coap_bin_const_t *CoAP::Sessions::pGetPskKey()
{
    return coap_session_get_psk_key (apSession);
}

void CoAP::Sessions::NewClientSessionPki(coap_context_t *ctx, const coap_address_t *local_if,
        const coap_address_t *server, coap_proto_t proto,
        coap_dtls_pki_t *setup_data)
{
    apSession = coap_new_client_session_pki (ctx, local_if, server, proto, setup_data);
}

void CoAP::Sessions::InitToken(size_t length, const uint8_t *token)
{
    coap_session_init_token (apSession, length, token);
}

void CoAP::Sessions::NewToken(size_t *length, uint8_t *token)
{
    coap_session_new_token (apSession, length, token);
}

