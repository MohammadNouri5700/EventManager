#pragma once

#include "mqttpod.grpc.pb.h"



class MqttPodNodeConfigService final : public MqttPodNodeConfig::Service {  
    private: 
        //CONNECTION::ConnectionManager *connMan;
        void ExtractMqttPodNodeConfig();
        virtual ::grpc::Status SendMqttPodNodeConfig(::grpc::ServerContext* context, const ::MqttPodNode* request, ::PodResponse* response) override;
        //std::map<std::string,std::shared_ptr<mosqpp::mosquittopp>> mosq;
    public:
        //MqttPodNodeConfigService();
};
