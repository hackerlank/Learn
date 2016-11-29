
#include "ServerDefine.h"
#include "Archive.h"

TVecFloat& operator+=(TVecFloat& vecAttr1, const TVecFloat& vecAttr2)
{
    size_t dstsize = vecAttr1.size();
    size_t srcsize = vecAttr2.size();
    size_t size = std::max(dstsize, srcsize);

    if (dstsize < srcsize)
        vecAttr1.resize(size, 0.f);

    for (size_t i = 0; i < size && i < srcsize; ++i)
        vecAttr1[i] += vecAttr2[i];

    return vecAttr1;
}

TVecFloat& operator-=(TVecFloat& vecAttr1, const TVecFloat& vecAttr2)
{
    size_t dstsize = vecAttr1.size();
    size_t srcsize = vecAttr2.size();
    size_t size = std::max(dstsize, srcsize);

    if (dstsize < srcsize)
        vecAttr1.resize(size, 0.f);

    for (size_t i = 0; i < size && i < srcsize; ++i)
        vecAttr1[i] -= vecAttr2[i];

    return vecAttr1;
}

