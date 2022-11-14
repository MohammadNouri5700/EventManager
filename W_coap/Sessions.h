//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_SESSIONS_H
#define W_COAP_SESSIONS_H
#include <coap3/coap.h>
#include <coap3/coap_session.h>



namespace CoAP
{
class Sessions
{
private:
    coap_session_t *apSession{nullptr};
public:

    Sessions();
    ~Sessions();
    Sessions(const Sessions&) = delete;
    Sessions operator=(const Sessions&) = delete;
    bool bNewClient(coap_context_t *ctx, coap_address_t *dst, coap_proto_t protocol);
    void Release()
    {
        coap_session_release(apSession);
    }
    void Send(coap_pdu_t *pdu)
    {
        coap_send(apSession, pdu);
    }
    coap_session_t * pGet()
    {
        return apSession;
    }
    bool operator!()
    {
        return !apSession;
    }

    coap_session_t * pReference ();
    void Disconnected (coap_nack_reason_t reason);
    void SetAppData (void *pData);
    void * pGetAppData ();
    const coap_address_t * 	pGetAddrRemote ();
    const coap_address_t * 	PGetAddrLocal ();
    coap_proto_t GetProto();
    coap_session_type_t GetType();
    coap_session_state_t GetState ();
    int iGetIfindex();
    void * pGetTls (coap_tls_library_t *tls_lib);
    coap_context_t *  pGetContext();
    int iSetTypeClient ();
    void SetMtu (unsigned mtu);
    size_t MaxPduSize ();
    void ClientSession (coap_context_t *pCtx, const coap_address_t *pLocal_if, const coap_address_t *pServer, coap_proto_t proto);
    void ClientSessionPsk (coap_context_t *pCtx, const coap_address_t *pLocal_if, const coap_address_t *pServer, coap_proto_t proto, const char *pIdentity, const uint8_t *pKey, unsigned key_len);
    void NewClientSessionPsk2 (coap_context_t *pCtx, const coap_address_t *pLocal_if, const coap_address_t *pServer, coap_proto_t proto, coap_dtls_cpsk_t *pSetup_data);
    const coap_bin_const_t *  pGetPskHint ();
    const coap_bin_const_t *  pGetPskKey ();
    void NewClientSessionPki (coap_context_t *pCtx, const coap_address_t *pLocal_if, const coap_address_t *pLServer, coap_proto_t proto, coap_dtls_pki_t *pSetup_data);
    void InitToken (size_t length, const uint8_t *pToken);
    void NewToken (size_t *pLength, uint8_t *pToken);
};
}

#endif //W_COAP_SESSIONS_H
