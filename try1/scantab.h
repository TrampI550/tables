#pragma once
#include "arraytab.h"
class TScanTable : public TArrayTable
{
protected:
	int SortID = 0;// идентификатор для упорядоченной таблицы с перепаковкой( Если 0, то обычная таблица, если 1, то сорт)
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pVal);
	virtual void DelRecord(TKey k);
	void SetSortID(int ID) { SortID = ID; }
};
