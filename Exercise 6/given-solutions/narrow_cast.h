#ifndef __NARROW_CAST_H
#define __NARROW_CAST_H
#include <stdexcept>
template<typename Target, typename Source>
Target narrow_cast(const Source& val)
{
    auto res = static_cast<Target>(val);
    if( (res != val) || (val != static_cast<Source>(res))){
        throw std::runtime_error("loss if information");
    }
    return res;
}
#endif
