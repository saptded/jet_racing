//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_PREMETIVE_H
#define LIBSERVER_PREMETIVE_H
template<typename T>
class PrimitiveTypeDescriptor{
};


template<typename T>
class ClassDescriptor
{
public:
    typedef PrimitiveTypeDescriptor<T> descriptor_t;
};
#endif //LIBSERVER_PREMETIVE_H
