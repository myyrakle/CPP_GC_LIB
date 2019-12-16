#pragma once

namespace gc
{
    class GCableObject;

    class GCableObject
    {
    public:
        bool _marked = false; //dont modify this
        virtual void clear() = 0;
    };
}