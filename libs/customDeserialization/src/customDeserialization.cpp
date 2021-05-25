//
// Created by dark0ghost on 25.05.2021.
//
#include <customDeserialization.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::vector<Position> CustomDeserialization::jsonToPosition(const char *json) {
    std::vector<Position> response;
    rapidjson::Document genericDocument;
    genericDocument.Parse(json);
    
    for (rapidjson::Value::ConstValueIterator itr = genericDocument.Begin(); itr != genericDocument.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            Position pos = Position{itr2->username.GetString(),itr2->x.GetString(),itr2->y.GetString(),itr2->z.GetString()};
            response.push_back(pos);
        }
    }
    return response;
}
