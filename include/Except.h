#include "Typedef.h"
#include <string>

#define raise_exception(msg) \
    static_assert(true,msg);

#define CLASS_NO_IMPLEMENT_EXCEPTION \
    raise_exception("class haven't implement");
    
namespace quoilam::except
{
    
}