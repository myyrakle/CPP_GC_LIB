#pragma once

#include "gcable_object.h"
#include "gc.h"

namespace gc
{
    class Char; // single character type
    class String; // string type

    class Int8; // 1 byte signed integer
    class Int16; // 2 byte signed integer
    class Int32; // 4 byte signed integer
    class Int64; // 8 byte signed integer

    class Uint8; // 1 byte unsigned integer
    class Uint16; // 2 byte unsigned integer
    class Uint32; // 4 byte unsigned integer
    class Uint64; // 8 byte unsigned integer

    class Float32; // single floating point type
    class Float64; // double floating point type

    class Bool; // boolean type

    class Char: public GCableObject // single character type
    {
    private:
        char value;
    public:
        virtual void clear()
        {}
    };
    class String; // string type

    class Int8; // 1 byte signed integer
    class Int16; // 2 byte signed integer
    class Int32; // 4 byte signed integer
    class Int64; // 8 byte signed integer

    class Uint8; // 1 byte unsigned integer
    class Uint16; // 2 byte unsigned integer
    class Uint32; // 4 byte unsigned integer
    class Uint64; // 8 byte unsigned integer

    class Float32; // single floating point type
    class Float64; // double floating point type

    class Bool; // boolean type
}

