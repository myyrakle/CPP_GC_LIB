#pragma once

#include "gcable_object.h"
#include "gc.h"

namespace gc
{
    template <class T>
    class Box;

    template <class T>
    class Box: gc::GCableObject
    {
    private:
        T* value;
    public:
        virtual ~Box();
        virtual void clear();
    };

    template <class T>
    Box<T>::~Box()
    {
        
    }
}

