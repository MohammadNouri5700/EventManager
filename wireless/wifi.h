//
// Created by aziz on 02.01.22.
//

#ifndef WIFI_WIFI_H
#define WIFI_WIFI_H
#include <unistd.h>
#include <iwlib.h>
#include <string>
#include <vector>
#include <set>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
#define NETWORK_NAME {"wlx7cc2c62577c4"};
struct access_point {
    std::string essId_{};
    std::string bitrate_{};
    std::string State_{};
    json toJson();
};

struct networks {
    std::string Quality;
    std::string Essid;
    };
class wifi
{
private:
    int sock_{};
    iwrange range_{};

    std::string ifName_{"wlx7cc2c62577c4"};

    std::vector<access_point> accessPoints_{};
    std::vector<std::string> essID_{};

public:
    
    int networkscount = 0;
    std::map<std::string,networks> networkList;
    bool Scan(void);
    std::map<std::string,networks> SystemScan();
    std::vector<std::string> getifconfig(void);
    void print(void);
    std::string findEssidName();
    std::string Connect(std::string data);
    int Turn(std::string data);

    wifi();

    virtual ~wifi();
    json toJson();


};

bool Connect(std::string essID, std::string password, std::string ifName);


#endif //WIFI_WIFI_H
