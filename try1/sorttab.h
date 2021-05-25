#include "scantab.h"
enum TSortMethod {INSERT_SORT, MERGE_SORT, QUICK_SORT};//метод сортировки
class TSortTable : public TScanTable
{
public: 
	TScanTable DopTab;
	PTTabRecord* pBuff = NULL;
protected:
	TSortMethod SortMethod;
	void SortData(void);//сортировка данных
	void InsertSort(PTTabRecord* pMem, int DataCount);//метод вставок
	void MergeSort(PTTabRecord* pMem, int DataCount);//метод слияния
	void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size);
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2);
	void QuickSort(PTTabRecord* pMem, int DataCount);//быстрая сортировка
	void QuickSplit(PTTabRecord* pData, int Size, int& Pivot);

public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {};
	TSortTable(const TScanTable& tab);
	TSortTable& operator= (const TScanTable& tab);
	TSortMethod GetSortMethod(void) { return SortMethod; } //получить использующийся метод сортировки
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; }//установить метод сортировки
	void Merge();//слияние доп. таблицы в основную

	virtual int* FindRecord(TKey k);//найти запись
	virtual void InsRecord(TKey k, int* pval);//добавить запись
	virtual void DelRecord(TKey k);//удалить запись
	virtual void Print();//принт для сорта
};
