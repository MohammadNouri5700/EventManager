//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_PANEL_H
#define EVENT_MANAGER_PANEL_H
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"



struct  panel :public JsonMessage {
    bool LED1{false};
    bool LED2{false};
    bool LED3{false};
    bool LED4{false};
    bool PushButton{false};
    float  Temp{0.0};


    void extract(nlohmann::json j) override;
    void print() override;
};


#endif //EVENT_MANAGER_PANEL_H
