//
// Created by aziz on 16.08.21.
//

#include "Pdu.h"

CoAP::Pdu::Pdu()
{
    apPdu = nullptr;
}

CoAP::Pdu::Pdu( coap_pdu_type_t type, coap_pdu_code_t code, coap_session_t * session = nullptr )
{
    apPdu = coap_new_pdu(type, code, session);
}

CoAP::Pdu::~Pdu()
{
}

void CoAP::Pdu::AddData(std::string data)
{
    coap_add_data (apPdu, data.size(), reinterpret_cast<const uint8_t *>(data.c_str()));
}

void CoAP::Pdu::AddOption(const std::string &data, coap_option_num_t option_num = COAP_OPTION_URI_PATH)
{
    coap_add_option(apPdu, option_num, data.size(), reinterpret_cast<const uint8_t *>(data.c_str()));
}

std::string CoAP::Pdu::strGetData()
{

    const uint8_t *data;
    size_t l;
    coap_get_data(apPdu, &l, &data);

    std::string s;
    for (size_t i = 0; i < l; i++) {
        s += data[i];
    }
    return s;
}

bool CoAP::Pdu::Init(coap_pdu_type_t type, coap_pdu_code_t code, coap_session_t *session)
{
    apPdu = coap_pdu_init(type, code, coap_new_message_id(session), coap_session_max_pdu_size(session));
    if (!apPdu) {
        coap_log( LOG_EMERG, "cannot create Pdu\n" );
        return false;
    }
    return true;
}

void CoAP::Pdu::AddDataAfter() {}
int CoAP::Pdu::AddToken(std::string data)
{
    return coap_add_token(apPdu, data.size(), reinterpret_cast<const uint8_t *>(data.c_str()));
}

int CoAP::Pdu::AddToken(const uint8_t data)
{
    return coap_add_token(apPdu, sizeof(data), &data);
}


void CoAP::Pdu::DeletePdu()
{
    coap_delete_pdu(apPdu);
}
void CoAP::Pdu::GetDataLarge() {}
void CoAP::Pdu::Duplicate() {}
coap_pdu_code_t CoAP::Pdu::GetCode()
{
    return coap_pdu_get_code(apPdu);
}
coap_mid_t CoAP::Pdu::GetMid()
{
    return coap_pdu_get_mid(apPdu);
}
std::string CoAP::Pdu::strGetToken()
{
    coap_bin_const_t str = coap_pdu_get_token(apPdu);
    std::string str1;

    for (size_t i = 0; i < str.length; i++) {
        str1 += str.s[i];
    }

    return str1;
}

coap_pdu_type_t CoAP::Pdu::GetType()
{
    return coap_pdu_get_type(apPdu);
}
void CoAP::Pdu::SetCode(coap_pdu_code_t code )
{
    coap_pdu_set_code(apPdu, code);
}
void CoAP::Pdu::SetMid(coap_mid_t mid )
{
    coap_pdu_set_mid (apPdu, mid	) ;
}
void CoAP::Pdu::SetType(coap_pdu_type_t type)
{
    coap_pdu_set_type(apPdu, type);
}

void CoAP::Pdu::ResponsePhrase()
{

}

coap_pdu_t *CoAP::Pdu::pGetPdu() const
{
    return apPdu;
}

void CoAP::Pdu::SetPdu(coap_pdu_t *pdu)
{
    Pdu::apPdu = pdu;
}

CoAP::Pdu::Pdu(coap_pdu_t *pdu) : apPdu(pdu) {}

std::string CoAP::strGet_data(const coap_pdu_t *P)
{
    const uint8_t *data;
    size_t l;
    coap_get_data(P, &l, &data);

    std::string s;
    for (size_t i = 0; i < l; i++) {
        s += data[i];
    }
    return s;
}
