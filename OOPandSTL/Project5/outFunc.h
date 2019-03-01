#ifndef OUTFUNC_H
#define OUTFUNC_H

#include <sstream>
#include <string.h>
//#include <string>

template <class T>
T sum(T a, T b)
{
    return a + b;
}

template <>
const char * sum(const char * a, const char * b)
{
    std::stringstream ss;
    ss << a << b;
    return ss.str().c_str();
}

#endif // OUTFUNC_H
