#pragma once
#include "trecord.h"
class TTable
{
protected:
	int DataCount;// количество записей в таблице
	int Efficiency;// показатель эффективности выполнения операции
public:

	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};
	int GetDataCount() const { return DataCount; }// к-во записей
	int GetEfficiency() const { return Efficiency; }// к-во записей
	int IsEmpty() const { return DataCount; }// к-во записей
	virtual int IsFull() const = 0;// к-во записей

	virtual int* FindRecord(TKey k) = 0;// найти запись
	virtual void InsRecord(TKey k, int* pVal) = 0;// добавить запись
	virtual void DelRecord(TKey k) = 0;// удалить запись

	virtual int Reset(void) = 0;// установить на первую запись
	virtual int IsTabEnded(void) const = 0;// таблица завершена?
	virtual int GoNext(void) = 0;// переход к следующей записи
	virtual TKey GetKey(void) const = 0;// получить ключ
	virtual int* GetValuePtr(void) const = 0;// получить pValue
	virtual PTTabRecord* GetAllpRecs() const = 0;// получить массив записей
	virtual void Print() {}
	// ВЫВОД
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
