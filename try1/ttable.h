#pragma once
#include "trecord.h"
class TTable
{
protected:
	int DataCount; //кол-во записей
	int Efficiency;
public:

	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};
	int GetDataCount() const { return DataCount; }
	int GetEfficiency() const { return Efficiency; }
	int IsEmpty() const { return DataCount; }
	virtual int IsFull() const = 0;

	virtual int* FindRecord(TKey k) = 0;
	virtual void InsRecord(TKey k, int* pVal) = 0;
	virtual void DelRecord(TKey k) = 0;

	virtual int Reset(void) = 0;
	virtual int IsTabEnded(void) const = 0;
	virtual int GoNext(void) = 0;
	virtual TKey GetKey(void) const = 0;
	virtual int* GetValuePtr(void) const = 0;
	virtual void Print(TTable& tab) = 0;
	virtual PTTabRecord* GetAllpRecs() const = 0;
	friend std::ostream& operator<<(std::ostream& os, TTable& tab)
	{
		std::cout << "Table printing" << std::endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << " Key: " << tab.GetKey();
			os << "  Val: ";
			for(int i=0;i<5;i++)
			os << tab.GetValuePtr()[i]<<" ";
			os << std::endl;
		}
		return os;
	}
};