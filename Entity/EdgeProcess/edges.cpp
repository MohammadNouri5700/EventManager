//
// Created by behrang on 12/18/21.
//
#include <iostream>
#include "edges.h"

edges::edges()
{

}

edges::~edges() {}

void edgesEntity::extract(nlohmann::json j)
{
    i_edgeId = j.at("edgeId").get<int>();
    str_edgeName = j.at("edgeName").get<std::string>();
    str_edgeFunction = j.at("edgeFunction").get<std::string>();
}

void edgesEntity::print()
{
    std::cout << std::boolalpha << "\nedgeId : " << i_edgeId
              << "\nedgeName : " << str_edgeName
              << "\nedgeFunction : " << str_edgeFunction << std::endl;
}

edgesEntity::edgesEntity(int iEdgeId, const std::string &strEdgeName, const std::string &strEdgeFunction) : i_edgeId(
        iEdgeId), str_edgeName(strEdgeName), str_edgeFunction(strEdgeFunction) {}

edgesEntity::~edgesEntity()
{

}

json edgesEntity::toJson()
{

    json j;
    j["edgeId"] = i_edgeId ;
    j["edgeName"] = str_edgeName;
    j["edgeFunction"] = str_edgeFunction;
    return j;
}
