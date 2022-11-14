//
// Created by behrang on 12/18/21.
//
#include <iostream>
#include "panel.h"
void panel::extract(nlohmann::json j)
{
    LED1 = j.at("led1").get<bool>();
    LED2 = j.at("led2").get<bool>();
    LED3 = j.at("led3").get<bool>();
    LED4 = j.at("led4").get<bool>();
    PushButton = j.at("pushButton").get<bool>();
    Temp = j.at("temperature").get<float>();
}

void panel::print()
{
    std::cout << std::boolalpha << "\nled 1 : " << LED1
              << "\nled 2 : " << LED2
              << "\nled 3 : " << LED3
              << "\nled 4 : " << LED4
              <<"\npushButton : " << PushButton
              <<"\ntemperature : " << Temp << std::endl;
}