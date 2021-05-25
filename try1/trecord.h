#pragma once
#include <iostream>
typedef std::string TKey;// тип ключа записи
class TTabRecord 
{

protected:
	TKey Key;// ключ
	int* pValue;// указатель на значение
public:
	TTabRecord(TKey k = "", int* pVal = NULL)
	{
		Key = k; pValue = pVal;
	}

	void SetKey(TKey k) {Key = k;}// установить значение ключа
	TKey GetKey(void) { return Key; }// получить значение ключа
	void SetValuePtr(int* p) { pValue = p; }// установить указатель на данные
	int* GetValuePtr(void) { return pValue; }// получить указатель на данные

	TTabRecord& operator=(TTabRecord tr)
	{
		Key = tr.Key; pValue = tr.pValue;
		return *this;
	}
	virtual int operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator< (const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator> (const TTabRecord &tr) { return Key < tr.Key; }
protected:
	void PrintRec(std::ostream& os) { os << Key << " " << *pValue; }// вывод записи в консоль

friend class TArrayTable;
friend class TScanTable;
friend class TSortTable;
friend class TTreeNode;
friend class TTreeTable;
friend class TArrayhash;
friend class THashTable;
};
typedef TTabRecord* PTTabRecord;// указатель на запись
