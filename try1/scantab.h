#pragma once
#include "arraytab.h"
class TScanTable : public TArrayTable
{
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pVal);
	virtual void DelRecord(TKey k);
};