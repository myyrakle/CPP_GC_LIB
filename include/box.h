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
        Box();
    public:
        Box();
        virtual ~Box();
        virtual void clear();
    };

    template <class T>
    Box<T>::Box()
    {
        gc::table.add();
    }

    template <class T>
    Box<T>::~Box()
    {
        gc::table.mark_and_sweep();
    }

    template <class T>
    void Box<T>::clear()
    {
        delete this->value;
    }
}