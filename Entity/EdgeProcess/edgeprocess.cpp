//
// Created by behrang on 12/18/21.
//

#include "edgeprocess.h"
#include "../TagValue/getTagValue.h"

edgeprocess::edgeprocess() {}
edgeprocess::~edgeprocess() {}

edgesProcessEntity::edgesProcessEntity(const edgesEntity &edgesEntity) : edgesEntity_(edgesEntity) {}

void edgesProcessEntity::extract(nlohmann::json j)
{
    (void)j;//TODO
}

void edgesProcessEntity::print()
{

}

json edgesProcessEntity::toJson()
{
    json j, Edges;
    Edges = edgesEntity_.toJson();
    json tags, j3, j4;
    /*for (auto t : tagsEntity_) {
        try {
          tags.push_back(t.toJson());
        } catch (std::exception &e) {
            std::cerr << e.what();
        } catch (...) {
            std::cerr << "other/n";
        }

    }*/

    j3["tagId"] = 10;
    j3["tagName"]= "s7Tag01";
    j3["tagType"] = 14;
    j3["tagSize"] = 8;
    j3["settingRef"] = 880;
    j3["read"] = true;
    j3["write"] = false;
    j3["tagValue"] = nullptr;

    j4["tagId"] = 11;
    j4["tagName"]= "s7Tag02";
    j4["tagType"] = 17;
    j4["tagSize"] = 7;
    j4["settingRef"] = 9898;
    j4["read"] = true;
    j4["write"] = true;
    j4["tagValue"] = nullptr;

    j["messageEdge"] = {{"Edges", Edges}, {"Tags", {j3, j4, j3}}};
    j.push_back({"messageId", "messageEdge"});

    tagsEntity t1(11, "s7tag1", 888, 77, 8888, true, false, nullptr);
    gettagValueEntity tg(11, 1144, "1400", "null");

    json y;
    //y["messageTag"] = t1.toJson();
    //y.push_back({"messageId","messageTags"});

    y["messageGetTagValue"] = tg.toJson();
    y.push_back({"messageId", "getTagValue"});


    return y;
}
