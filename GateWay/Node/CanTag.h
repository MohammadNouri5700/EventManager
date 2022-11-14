//
// Created by aziz on 08.10.21.
//

#ifndef EVENT_MANAGER_CANTAG_H
#define EVENT_MANAGER_CANTAG_H

#include "Tag.h"
#include "../Connection/ConnectionCan.h"
namespace ProtocolS
{
    class CANTag : public Tag
    {
    private:
        int data;

    protected:
        void SendEvent() override;

    public:
        u16Tag StartingAddress{};
        u16Tag BitNumber{};
        u32Tag CANID{};
        u16Tag BitCount{};
        // strTag MessageType;
        void Print() override;
        void UpdateValue() override;
        ~CANTag() override;
        int GetType() override;
        void setSubject(Protocol *subject) override;
        CANTag(xmlCAN *can);
        virtual bool compare(Tag *t)
        {
            auto tag = dynamic_cast<CANTag *>(t);
            if (tag == NULL)
            {
                return false;
            }
            return this->conn->Address.Value == tag->conn->Address.Value;
        }

        int SbitExtracted(int number, int k, int p);
    };

};
#endif // EVENT_MANAGER_CANTag_H
