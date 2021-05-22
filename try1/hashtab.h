#pragma once

#include "arraytab.h"

class TTabRecord;

class THashTable : public TTable
{
protected:
	virtual unsigned long HashFunc(const TKey key)
    {
        unsigned int hash = 1315423911;

        for (std::size_t i = 0; i < key.length(); i++)
        {
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        }

        return (hash & 0x7FFFFFFF);
    }
public:
	THashTable() : TTable() {}
    virtual void Print(TTable &tab) {}
};
