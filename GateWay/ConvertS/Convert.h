//
// Created by aziz on 15.10.21.
//

#ifndef EVENT_MANAGER_CONVERT_H
#define EVENT_MANAGER_CONVERT_H
#include <string>
#include <vector>


class Convert
{
    std::string Source{};
    std::vector<std::string> DistS{};
public:
    void setSource(const std::string &source);
    void setDist(const std::string dist);
    void Print();

    std::string source() const { return Source; }
    std::vector<std::string> distS() const { return DistS; }

};


#endif //EVENT_MANAGER_CONVERT_H