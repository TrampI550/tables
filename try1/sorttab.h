#include "scantab.h"
enum TSortMethod {INSERT_SORT, MERGE_SORT, QUICK_SORT};
class TSortTable : public TScanTable
{
public: 
	TScanTable DopTab;
	PTTabRecord* pBuff = NULL;
protected:
	TSortMethod SortMethod;
	void SortData(void);
	void InsertSort(PTTabRecord* pMem, int DataCount);
	void MergeSort(PTTabRecord* pMem, int DataCount);
	void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size);
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2);
	void QuickSort(PTTabRecord* pMem, int DataCount);
	void QuickSplit(PTTabRecord* pData, int Size, int& Pivot);

public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {};
	TSortTable(const TScanTable& tab);
	TSortTable& operator= (const TScanTable& tab);
	TSortMethod GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; }
	void Merge();

	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pval);
	virtual void DelRecord(TKey k);
	virtual void Print();
};