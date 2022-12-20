//
// Created by MohammadNouri on 12.10.22.
//

#ifndef EVENT_MANAGER_GPSTAG_H
#define EVENT_MANAGER_GPSTAG_H
#include "Tag.h"
#include "../Connection/ConnectionGPS.h"

namespace ProtocolS
{
    class GPSTag : public Tag
    {
    protected:
        void SendEvent() override;

    public:
//        u16Tag dataType{};
//        strTag MessageType;t
        void setValue(void *value, size_t Size) override;
        void Print() override;
        void UpdateValue() override;
        ~GPSTag() override;
        int GetType() override;
        void setSubject(Protocol *subject) override;
        GPSTag(xmlGPS *gps);
        virtual bool compare(Tag *t)
        {
            auto tag = dynamic_cast<GPSTag *>(t);
            if (tag == NULL)
            {
                return false;
            }
            return this->conn->Address.Value == tag->conn->Address.Value;
        }

        std::string jsonvalue;
    };

};










#endif // EVENT_MANAGER_GPSTAG_H