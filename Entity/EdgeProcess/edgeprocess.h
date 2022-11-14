//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_EDGEPROCESS_H
#define EVENT_MANAGER_EDGEPROCESS_H

#include "../Tag/tags.h"
#include "edges.h"
#include <vector>

struct edgesProcessEntity: public JsonMessage {
    edgesEntity edgesEntity_{};
    std::vector<tagsEntity> tagsEntity_{};

    edgesProcessEntity(const edgesEntity &edgesEntity);

    json toJson() override;

    void extract(nlohmann::json j) override;
    void print() override;
};

class edgeprocess
{
public:
    edgeprocess();
    virtual ~edgeprocess();
private:

};


#endif //EVENT_MANAGER_EDGEPROCESS_H
