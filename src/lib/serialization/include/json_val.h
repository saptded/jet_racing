//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_JSON_VAL_H
#define LIBSERVER_JSON_VAL_H
struct Jobject;
struct Tlist;

using json_value = std::variant<int, float, bool, std::string, Tlist, Jobject>;

enum Tag {
    int_value,
    float_value,
    string_value,
    list,
    object
};
struct Tlist {
    Tag type;
    std::vector<json_value *> vector_value;
};
struct Jobject {
    Tag type;
    std::map<std::string, json_value *> map_value;
};

#endif //LIBSERVER_JSON_VAL_H
