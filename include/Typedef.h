#pragma once
#include <cstdint>
namespace quoilam
{
    using Byte = char;
    using Uint = uint32_t;
    namespace io{
        extern Uint read,write,readwrite,app,ate;
    };
} // namespace quoilam
