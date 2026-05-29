#ifndef __NARROW_CAST_H
#define __NARROW_CAST_H
#include <stdexcept>
template<typename Target, typename Source>
Target narrow_cast(const Source& val)
{
    (void) val; // avoid unused parameter warning
    throw std::runtime_error("not yet implemented");
}
#endif
