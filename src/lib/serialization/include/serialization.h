//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_SERIALIZATION_H
#define LIBSERVER_SERIALIZATION_H
#include <vector>
#include "Position.hpp"
#include <string>
#include "premetive.h"

template<>
class ClassDescriptor<Position>{
public:
    typedef  ClassDescriptor<Position> descriptor_t;
    template<typename TCallback>
    void for_each_property(TCallback& callback) const
    {
        callback("username", &Position::username);
        callback("x", &Position::x);
        callback("y", &Position::y);
        callback("z", &Position::z);

    }
};
template<>
class ClassDescriptor<std::string>{
public:
    typedef PrimitiveTypeDescriptor<std::string> descriptor_t;
};
template<typename T>
typename ClassDescriptor<T>::descriptor_t GetTypeDescriptor(const T& t)
{
    return typename ClassDescriptor<T>::descriptor_t {};
}

template<typename T>
class ArrayTypeDescriptor
{
};

template<typename T>
class ArrayTypeDescriptor<std::vector<T>>
{
public:
size_t get_size(std::vector<T>& vec) const
{
    return vec.size();
}
};

template<typename T>
class ClassDescriptor<std::vector<T>>
{
public:
typedef ArrayTypeDescriptor<std::vector<T>> descriptor_t;
};

template<typename T, int N>
class ArrayTypeDescriptor<T[N]>
{
public:
    size_t get_size(T(&t)[N]) const
    {
        return N;
    }
};

template<typename T, int N>
class ClassDescriptor<T[N]>
{
public:
    typedef ArrayTypeDescriptor<T[N]> descriptor_t;
};

#endif //LIBSERVER_SERIALIZATION_H
