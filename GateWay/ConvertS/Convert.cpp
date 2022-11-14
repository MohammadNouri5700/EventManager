//
// Created by aziz on 15.10.21.
//

#include "Convert.h"
#include <iostream>

void Convert::setSource(const std::string &source)
{
    Source = source;
}

void Convert::setDist(const std::string dist)
{
    DistS.push_back(dist);
}

void Convert::Print()
{
    std::cout << "Source : " << Source <<'\n'
              << "distS : " << '\n';
    for (auto d: DistS) {
        std::cout << d <<'\n';
    }
}