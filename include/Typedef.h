#pragma once
#include <memory>
#define QUOILAM_ALL_NAMESPACE         \
    using namespace quoilam;          \
    using namespace quoilam::io;      \
    using namespace quoilam::network; \
    using namespace quoilam::text;    \
    using namespace quoilam::util;

#include <cstdint>
namespace quoilam
{

    using Byte = char;
    using PByte = Byte *;
    using CByte = const Byte;
    using CRByte = const Byte &;
    using CRPByte = const PByte &;

    using UInt = uint32_t;
    using CUInt = const UInt;
    using CRUInt = const UInt &;

    using Void = void;
    using PVoid = void *;

    namespace io
    {
    };
    namespace util
    {
    };
    namespace text
    {
    };
    namespace network
    {
    };
} // namespace quoilam

namespace quoilam::io
{
    enum class iomode
    {
        read = 0x1,      // 0001
        write = 0x2,     // 0010
        readwrite = 0x3, // 0011
        app = 0x4,       // 0100
        ate = 0x8,       // 1000
    };

}
namespace quoilam::text
{
    // class ByteSeries
    // {
    // public:
    //     ByteSeries(UInt bytes_count, Byte val = '\0');
    //     ByteSeries(CRPByte buffer);

    //     ByteSeries(const ByteSeries &obj);
    //     ~ByteSeries();

    //     operator PByte() const;
    //     const Byte &operator[](int index);
    //     const UInt length() const;

    // private:
    //     std::unique_ptr<Byte> data;
    // };

    // const ByteSeries serialize(const PVoid );
    // const PVoid deserialize(const ByteSeries &);

}
