//
// Created by aziz on 17.10.21.
//

#include "CoapNode.h"

void CoAP::CoapNode::Run()
{
    auto it = NodeS.begin();
    while (it != NodeS.end()) {
        (*it)->Run();
        it++;
        if (it==NodeS.end())
            it = NodeS.begin();
    }

    for (auto n:NodeS) {
        n->End();
    }
}

