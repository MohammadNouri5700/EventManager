//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_EDGES_H
#define EVENT_MANAGER_EDGES_H
#include <string>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"

struct edgesEntity:public JsonMessage {
    int i_edgeId{0};
    std::string str_edgeName{""};
    std::string str_edgeFunction{""};
    edgesEntity(){}
    virtual ~edgesEntity();

    edgesEntity(int iEdgeId, const std::string &strEdgeName, const std::string &strEdgeFunction);

    void extract(nlohmann::json j) override;
    void print() override;

    json toJson() override;
};

class edges
{
public :
    edges();
    virtual ~edges();
private:


};


#endif //EVENT_MANAGER_EDGES_H
