//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_PDU_H
#define W_COAP_PDU_H
#include <coap3/coap.h>
#include <string>
namespace CoAP
{
class Pdu
{
private:
    coap_pdu_t *apPdu {nullptr};
public:

    Pdu();
    Pdu(coap_pdu_t *pdu);
    Pdu(const Pdu&) = delete;
    Pdu operator=(const Pdu&) = delete;

    virtual ~Pdu();

    coap_pdu_t *pGetPdu() const;

    void SetPdu(coap_pdu_t *pdu);
    Pdu( coap_pdu_type_t type, coap_pdu_code_t code, coap_session_t * pSession ) ;


    void AddData(std::string data);
    void AddOption(const std::string &data, coap_option_num_t option_num);
    std::string strGetData();
    bool Init(coap_pdu_type_t type, coap_pdu_code_t code, coap_session_t* session);
    coap_pdu_t * pGet()
    {
        return apPdu;
    };


    void AddDataAfter();
    int  AddToken(std::string data);
    int  AddToken(const uint8_t data);
    void DeletePdu();
    void GetDataLarge();
    void Duplicate();
    coap_pdu_code_t GetCode();
    coap_mid_t GetMid();
    std::string strGetToken();
    coap_pdu_type_t GetType();
    void SetCode(coap_pdu_code_t code);
    void SetMid(coap_mid_t mid );
    void SetType(coap_pdu_type_t type);
    void ResponsePhrase();
    void Show(coap_log_t level = LOG_WARNING)
    {
        coap_show_pdu(level, apPdu);
    };

    void send(coap_session_t *session)
    {
        coap_send(session, apPdu);
    }

};
std::string strGet_data(const coap_pdu_t *P);
}



#endif //W_COAP_PDU_H
