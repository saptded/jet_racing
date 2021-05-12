//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_PARSER_H
#define LIBSERVER_PARSER_H

#include <string>
#include <map>
#include <vector>
#include <stack>
#include <variant>
#include "json_val.h"


class JSONParser {

public:
    JSONParser();

    ~JSONParser();

    void parseFile(std::string);

private:
    json_value root;
    std::stack<std::string> s;
    std::stack<json_value> s_value;

    // Lexer
    static bool checkDeliminator(char);

    static std::vector<std::string> lexer(std::ifstream &);

    // FSM varaibles
    enum state {
        int_value,
        float_value,
        bool_value,
        string_value,
        default_value,
        bad_state
    };
    state current;

    // FSM
    void fsm(std::string);

    // Parser variables
    enum stack_map {
        list_open, list_close, object_open, object_close, colon, comma, buffer, follow
    };
    std::map<std::string, stack_map> stack_conversion;

    // Parser helper functions
    template<typename T>
    void addElement();

    template<typename T>
    void insert(std::string &, T (*)(const std::string &));

    template<typename T>
    void insert();

    void insert(std::string &);

    void pushBuffer();

    template<typename ... T>
    bool multiComparision(const char scope, T ... args);

    bool isDigit(const char);

    static int st2i(const std::string &value);

    static float st2f(const std::string &value);

    static bool st2b(const std::string &value);

    // Parser
    void parser(const std::string &cursor);
};

#endif //LIBSERVER_PARSER_H
