#include "wifiservice.h"
#include <iostream>
#include "../wireless/wifi.h"

using namespace grpc;

::grpc::Status SystemWifiConfigService::SendSystemWifiConfig(::grpc::ServerContext* context, const ::ConfigWifi* request, ::ConfigWifi* response)
{
    wifi gwifi;
    char cmd[128];
    std::cout << "WIFI_CONFIG" << std::endl;
    if(request->nemtworkname().length() > 0)
    {
    //"data": "{\"networkName\":\"khatam\",\"networkPassword\":\"891700000\"}"
        std::string d = "{\"networkName\":\"" +request->nemtworkname()
                    +"\",\"networkPassword\":\""
                    +request->networkpassword()+"\"}";
        std::cout << d << std::endl;
        gwifi.Connect(d);
        
    }
    sprintf(cmd,"ip link set %s down","wlan0");
	system(cmd);
    std::cout<<cmd<<std::endl;
    if(request->ip().length() >0){
        std::string d = "ifconfig wlan0 " + request->ip() + " netmask " + request->mask();
        std::cout<<d<<std::endl;
	    system(d.c_str());	 
    }

    if(request->gateway().length()>0){
        std::string d  = "route add default gw " + request->gateway() + " wlan0";
        std::cout<<d<<std::endl;
	    system(d.c_str()); 
    }
    sprintf(cmd,"ip link set %s up","wlan0");
	system(cmd);
    std::vector<std::string> x = gwifi.getifconfig();
    //response->commandresponce().isok_= true;
    
    response->set_dns(x.back());
    x.pop_back();
    response->set_gateway(x.back());
    x.pop_back();
    response->set_mask(x.back());
    x.pop_back();
    response->set_ip(x.back());
    x.pop_back();
    response->set_nemtworkname(gwifi.findEssidName());
    CommandResponce *commandResponce = new CommandResponce();
    commandResponce->set_isok(true);
    response->set_allocated_commandresponce(commandResponce);
    return Status::OK;
}




::grpc::Status SystemCommandService::SendSystemCommand(::grpc::ServerContext* context, const ::Command* request, ::CommandResponce* response)
{

    wifi gwifi;
    string d , state;
    switch (request->commandtype()) {
    case CommandType::WIFI_SCAN : {
        std::cout << "WIFI_SCAN" << std::endl;
        auto tempNetwork =gwifi.SystemScan();
        for (auto& x : tempNetwork) {
            auto wifilist = response->add_wifilist();
            wifilist->set_networkname(x.second.Essid);
            wifilist->set_networksignal(x.second.Quality);
        }
        response->set_networkname(gwifi.findEssidName());
        response->set_isok(true);
    }
    break;
    case CommandType::WIFI_CONNECT :
        std::cout << "WIFI_Connect" << std::endl;
        d =  request->data();
        state = gwifi.Connect(d);
        if (!strncmp(state.c_str(),"Error",5) ){
            response->set_isok(false);
            response->set_responcedata(state);
        }else{
            response->set_isok(true);
            response->set_responcedata(d);
        }
        break;
    case CommandType::WIFI_DISCONNECT :
        //gwifi.Disconnect();
        std::cout << "WIFI_DISCONNECT" << std::endl;
        response->set_isok(true);
        break;
    case CommandType::WIFI_STATE :
        std::cout << "WIFI_STATE" << std::endl;
        if (request->data() == "on") {
            gwifi.Turn("on");
            response->set_responcedata("on");
        } else {
            gwifi.Turn("off");
            response->set_responcedata("off");
        }
        response->set_isok(true);
        break;
    default:
        std::cout << "WIFI_ERROR" << std::endl;
        break;
    }
    return Status::OK;
}
