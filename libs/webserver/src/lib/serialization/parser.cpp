//
// Created by dark0ghost on 12.05.2021.
//
#include <fstream>
#include <iostream>
#include "parser.h"
#include "json_val.h"

JSONParser::JSONParser() {
    stack_conversion = { { "[", list_open }, { "]", list_close }, { "{", object_open }, { "}", object_close }, { ":", colon }, { ",", comma }, { "buffer", buffer } };
}

JSONParser::~JSONParser() = default;

void JSONParser::parseFile(std::string FILE) {
    std::ifstream configfile(FILE);
    std::vector<std::string> scan = lexer(configfile);

    scan.push_back("terminate");
    for (auto & it : scan) {
        parser(it);
    }
    root = s_value.top();
    s_value.pop();
}

// Lexer
bool JSONParser::checkDeliminator(char piece) {
    switch (piece) {
        case '[':
            return true;
        case ']':
            return true;
        case '{':
            return true;
        case '}':
            return true;
        case ':':
            return true;
        case ',':
            return true;
        default:
            return false;
    }
}

std::vector<std::string> JSONParser::lexer(std::ifstream & configfile) {
    char piece;
    std::string capture = "";
    std::string conversion;
    std::vector<std::string> capture_list;

    while(configfile >> piece) {
        if (checkDeliminator(piece)) {
            conversion = piece;
            if (capture != "") {
                capture_list.push_back(capture);
                capture_list.push_back(conversion);
                capture = "";
            } else {
                capture_list.push_back(conversion);
            }
        } else {
            capture += piece;
        }
    }

    return capture_list;
}

// FSM
void JSONParser::fsm(std::string value) {
    current = default_value;
    char point;
    auto it = value.begin();

    while (it != value.end()) {
        point = *it;
        if (point == '"' && current == default_value) {
            current = string_value;
            return;
        } else if (isdigit(point)) {
            if (current == default_value || current == int_value) {
                current = int_value;
                ++it;
            } else if (current == float_value) {
                ++it;
            } else {
                current = bad_state;
                return;
            }
        } else if (point == '.' && current == int_value) {
            current = float_value;
            ++it;
        } else if (point == 'f' && current == float_value) {
            ++it;
        } else if (current == default_value) {
            if (value == "true" || value == "false") {
                current = bool_value;
                return;
            } else {
                current = bad_state;
                return;
            }
        } else {
            current = bad_state;
            return;
        }
    }
}

// Parser Helper functions
template<>
void JSONParser::addElement<Jobject>() {
    json_value value_read;
    json_value key_read;

    value_read = s_value.top();
    s_value.pop();
    key_read = s_value.top();
    s_value.pop();

   //std::get<Jobject>(s_value.top()).insert(key_read, value_read);
}

template<>
void JSONParser::addElement<Tlist>() {
    json_value value_read;

    value_read = s_value.top();
    s_value.pop();

  //  std::get<Tlist>(s_value.top()).push_back(value_read);
}

template<typename T>
void JSONParser::insert(std::string & value, T (*fptr)(const std::string &)) {
    T T_value(fptr(value));
    s_value.push(T_value);
}

template<typename T>
void JSONParser::insert() {
    T T_value;
    s_value.push(T_value);
}

void JSONParser::insert(std::string & value) {
    value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
    s_value.push(value);
}

void JSONParser::pushBuffer() {
    s.pop();
    s.push("buffer");
}

template<typename ... T>
bool JSONParser::multiComparision(const char scope, T ... args) {
    return (scope == (args || ...));
}

bool JSONParser::isDigit(const char c) {
    return multiComparision<char>(c, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0');
}

int JSONParser::st2i(const std::string & value) {
    return stoi(value);
}

float JSONParser::st2f(const std::string & value) {
    return stof(value);
}

bool JSONParser::st2b(const std::string & value) {
    if (value == "true") {
        return true;
    } else {
        return false;
    }
}

// Parser
void JSONParser::parser(const std::string & cursor) {
    if(s.empty()) {
        s.push(cursor);
    } else {
        stack_map stack_value;
        std::string value = s.top();

        if (stack_conversion.find(value) != stack_conversion.end()) {
            stack_value = stack_conversion[s.top()];
        } else {
            stack_value = follow;
        }

        switch (stack_value) {
            case buffer:
                s.pop();
                break;
            case list_open:
                insert<Tlist>();
                if (cursor == "]") {
                    pushBuffer();
                    return;
                }
                break;
            case list_close:
                addElement<Tlist>();
                s.pop();
                s.pop();
                break;
            case object_open:
                insert<Jobject>();
                if (cursor == "}") {
                    pushBuffer();
                    return;
                }
                break;
            case object_close:
                addElement<Jobject>();
                s.pop();
                s.pop();
                break;
            case colon:
                s.pop();
                break;
            case comma:
                s.pop();
                if (s.top() == "{") {
                    addElement<Jobject>();
                } else {
                    addElement<Tlist>();
                }
                break;
            default:
                s.pop();
                fsm(value);
                switch (current) {
                    case string_value:
                        insert(value);
                        break;
                    case int_value:
                        insert<int>(value, st2i);
                        break;
                    case float_value:
                        insert<float>(value, st2f);
                        break;
                    case bool_value:
                        insert<bool>(value, st2b);
                        break;
                    default:
                        std::cout << "Bad state\n";
                }
        }
        s.push(cursor);
    }
}

