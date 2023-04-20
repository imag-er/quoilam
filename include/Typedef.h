#pragma once


#define QUOILAM_ALL_NAMESPACE \
using namespace quoilam;\
using namespace quoilam::io;\
using namespace quoilam::network;\
using namespace quoilam::text;\
using namespace quoilam::ultility;



#include <cstdint>
namespace quoilam
{
    using Byte = char;
    using Uint = uint32_t;

    namespace ultility
    {

    };
    namespace io
    {
        enum class iomode
        {
            read = 0x1,      // 0001
            write = 0x2,     // 0010
            readwrite = 0x3, // 0011
            app = 0x4,       // 0100
            ate = 0x8,       // 1000
        };

    };
    namespace text
    {

    };
    namespace network
    {

    };
} // namespace quoilam
