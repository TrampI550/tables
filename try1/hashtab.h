#pragma once

#include "ttable.h"

class TTabRecord;

class THashTable : public TTable
{
protected:
    virtual unsigned long HashFunc(const TKey key, const int choose)// хеш-функция 1
    {
        if (choose == 1)
        {
            unsigned int hash = 1315423911;

            for (std::size_t i = 0; i < key.length(); i++)
            {
                hash ^= ((hash << 5) + key[i] + (hash >> 2));
            }

            return (hash & 0x7FFFFFFF);
        }
        else // хеш-функция 2
        {
            const int p = 31;
            long long hash = 0, p_pow = 1;
            for (int i = 0; i < key.length(); i++)
            {
                hash += (key[i] - 'a' + 1) * p_pow;
                p_pow *= p;
            }
            return (hash & 0x7FFFFFFF);
        }
    }
public:
	THashTable() : TTable() {}
};
