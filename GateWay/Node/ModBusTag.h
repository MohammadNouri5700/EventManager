//
// Created by aziz on 12.10.21.
//

#ifndef EVENT_MANAGER_MODBUSTAG_H
#define EVENT_MANAGER_MODBUSTAG_H
#include "Tag.h"
#include "../Connection/ConnectionModbus.h"
#define SLEEP_MODBUS 5000
namespace ProtocolS
{
    class ModBusTag : public Tag
    {
        u16Tag StartingAddress;
        u16Tag NumberOfRegisters;
        u16Tag Scale;
        u16Tag Function;

    public:
        uint16_t getStartingAddress() const;
        uint16_t getNumberOfRegisters() const;
        uint16_t getScale() const;
        uint16_t getFunction() const;
        void setSubject(Protocol *subject) override;
        void SendEvent() override;
        void UpdateValue() override;
        ~ModBusTag() override;
        int GetType() override;
        void Print() override;
        ModBusTag(xmlModBus *node);
        ModBusTag(uint16_t startingAddress, uint16_t numberOfRegisters, uint16_t scale, uint16_t function);

        void setStartingAddress(uint16_t startingAddress);
        void setNumberOfRegisters(uint16_t numberOfRegisters);
        void setScale(uint16_t scale);
        void setFunction(uint16_t function);

        virtual bool compare(Tag *t)
        {
            auto tag = dynamic_cast<ModBusTag *>(t);
            if (tag == NULL)
            {
                return false;
            }
            return this->conn->Address.Value == tag->conn->Address.Value;
        }
    };
}

#endif // EVENT_MANAGER_MODBUSTAG_H
