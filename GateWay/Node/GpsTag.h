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
    private:
        std::string jsonvalue;
        FloatTag latitude;
        FloatTag longitude;
        FloatTag SpeedOverGround;
        u16Tag UTC;
        u16Tag Date;

    protected:
        void SendEvent() override;

    public:
//        u16Tag dataType{};
//        strTag MessageType;t
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
    };

};










#endif // EVENT_MANAGER_GPSTAG_H