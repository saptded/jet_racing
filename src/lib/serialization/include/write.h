//
// Created by dark0ghost on 12.05.2021.
//

#ifndef LIBSERVER_WRITE_H
#define LIBSERVER_WRITE_H

#include <string>
#include "serialization.h"
#include "get_type_descriptor.h"
#include "premetive.h"


template<typename TStream, typename TClass>
class WriteJSONFunctor;

template<typename TStream, typename T>
void DispatchWriteJSON(const PrimitiveTypeDescriptor<T>& descriptor,
                       TStream &stream, T& t)
{
    stream << t;
}

template<typename TStream, typename T>
void DispatchWriteJSON(const PrimitiveTypeDescriptor<T>& descriptor,
                       TStream &stream, std::string& t)
{
    //todo: escape strings here
    stream << "\"" << t << "\"";
}

template<typename TStream, typename T>
void DispatchWriteJSON(const ArrayTypeDescriptor<T>& descriptor,
                       TStream &stream, T& t)
{
    stream << "[";
    auto size = descriptor.get_size(t);
    for(int n = 0; n < size; n++)
    {
        if(n != 0)
        {
            stream << ",";
        }
        WriteJSON(stream, t[n]);
    }
    stream << "]";
}

template<typename TStream, typename T>
void DispatchWriteJSON(const ClassDescriptor<T>& descriptor,
                       TStream &stream, T &t){
    WriteJSONFunctor<TStream, T> functor(stream, t);
    stream << "{";
    descriptor.for_each_property(functor);
    stream << "}";
}


template<typename TStream, typename T>
void WriteJSON(TStream &stream, T& t){
    DispatchWriteJSON(GetTypeDescriptor(t), stream, t);
}

template<typename TStream>
void writeJSONPosition(TStream &stream, Position& t){
    DispatchWriteJSON(typename ClassDescriptor<Position>::descriptor_t {} , stream, t);
}

template<typename TStream, typename TClass>
class WriteJSONFunctor{
    TStream& m_stream;
    TClass& m_t;
    bool m_first;
public:
    WriteJSONFunctor(TStream& stream, TClass& t):m_stream(stream), m_t(t){
        m_first = true;
    }

    template<typename TPropertyType>
    void operator()(const char* szProperty, TPropertyType TClass::*pPropertyOffset){
        if(m_first){
            m_first = false;
        }
        else{
            m_stream << ",";
        }
        m_stream << "\"" << szProperty << "\": ";
        WriteJSON(m_stream, m_t.*pPropertyOffset);
    }
};

#endif //LIBSERVER_WRITE_H
