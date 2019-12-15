#pragma once

namespace gc
{
    class GCableObject;

    class GCableObject
    {
    public:
        virtual void clear() = 0;
    };
}