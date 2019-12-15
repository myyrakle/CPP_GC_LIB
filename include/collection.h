#pragma once

#include <vector>
#include "gcable_object.h"

namespace gc
{
    template <class T, size_t Len>
    class Array;

    template <class T>
    class Vector;

    template <class T, size_t Len>
    class Array: public GCableObject
    {
    private: 
        T[Len] value;
    public:
        
    };

    template <class T>
    class Vector: public GCableObject
    {
    private: 
        std::vector<T> value;
    public:
        
    };
}
