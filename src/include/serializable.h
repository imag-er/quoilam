#pragma once
#include <cstddef>
#include <cstdint>
namespace quoilam
{
    using Byte = uint8_t;

    class Serializable
    {
    public:
        Byte* serialize()
        {
            return (Byte*)this;
        }
        size_t size()
        {
            return sizeof(*this);
        }
    };
};