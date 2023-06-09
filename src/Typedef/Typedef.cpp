#include "Typedef.h"
#include <cstring>
namespace quoilam
{

} // namespace quoilam

namespace quoilam::text
{

    // ByteSeries::ByteSeries(UInt bytes_count, Byte val)
    // {
    //     data = std::make_unique<Byte>(new Byte[bytes_count]{val});
    // }
    // ByteSeries::ByteSeries(CRPByte buffer)
    // {
    //     UInt len = strlen(buffer);
    //     data = std::make_unique<Byte>(new Byte[len]);

    //     memcpy(data.get(),buffer,len);
    // }

    // ByteSeries::ByteSeries(const ByteSeries &obj) 
    // {
    //     memcpy(data.get(),obj,obj.length());
    // }
    // ByteSeries::~ByteSeries()
    // {
    // }
    // const Byte& ByteSeries::operator[](int index)
    // {
    //     if (index < 0)
    //     {
    //         return operator[](length() - index);
    //     }
    //     if (index < length())
    //     {
    //         return *(data.get() + index);
    //     }
        
    //     throw std::runtime_error("index out of range");
    // }
    // ByteSeries::operator PByte () const
    // {
    //     return data.get();
    // }
    // const UInt ByteSeries::length() const
    // {
    //     return strlen(data.get());
    // }

    // const ByteSeries serialize(const PVoid obj,UInt size)
    // {
    //     strlen((const char*)obj);
    // }
    // const PVoid deserialize(const ByteSeries &)
    // {

    // }
}
