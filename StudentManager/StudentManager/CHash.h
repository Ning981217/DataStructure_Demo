#pragma once

#include <iostream>
#include "MyString.h"

using namespace std;

class CHash
{
public:
    static size_t GetHashValue(CMyString val);
};

inline size_t CHash::GetHashValue(CMyString val)
{
    size_t nHashVal = _FNV_offset_basis;
    for (size_t idx = 0; idx < val.GetLen(); ++idx) {
        nHashVal ^= static_cast<size_t>(val[idx]);
        nHashVal *= _FNV_prime;
    }
    return nHashVal;
}
