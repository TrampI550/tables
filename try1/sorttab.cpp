#include "sorttab.h"
TSortTable::TSortTable(const TScanTable & tab)///////////////
{
	*this = tab;
}

TSortTable& TSortTable::operator= (const TScanTable& tab)
{
	if (pRecs != NULL)
	{
		for (int i = 0; i < DataCount; i++)
			delete pRecs[i];
		delete[] pRecs;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++)
		pRecs[i] = tab.GetpRecs(i);
	SortData();
	CurrPos = 0;
	return *this;
}

int* TSortTable::FindRecord(TKey k)
{
	int midd = 0, left = 0, right = DataCount - 1;
	while (left<=right)
	{
		midd = (left + right) / 2;
		if (k < pRecs[midd]->GetKey())       // ���� ������� ������ �������� � ������
			right = midd - 1;      // ������� ������ ������� ������
		else if (k > pRecs[midd]->GetKey())  // ���� ������� ������ �������� � ������
			left = midd + 1;    // ������� ����� ������� ������
		else                       // ����� (�������� �����)
		{
			CurrPos = midd;
			return pRecs[midd]->GetValuePtr();
		}
	}
	//CurrPos = left;
	DopTab.SetSortID(1);
	DopTab.FindRecord(k);
}

void TSortTable::InsRecord(TKey k, int* pVal)
{
	//if (!IsFull())
	//{
	//	int* temp = FindRecord(k);
	//	for (int i = DataCount; i > CurrPos; i--)
	//		pRecs[i] = pRecs[i - 1];
	//	pRecs[CurrPos] = new TTabRecord(k,pVal);
	//	CurrPos = DataCount;
	//	DataCount++;
	//}
	if (!DopTab.IsFull())
	{
		DopTab.SetSortID(1);
		int* temp = DopTab.FindRecord(k);
		DopTab.InsRecord(k, pVal);
	}
}

void TSortTable::DelRecord(TKey k)
{
	int midd = 0, left = 0, right = DataCount - 1, cheak = 1;
	while (cheak)
	{
		midd = (left + right) / 2;
		if (k < pRecs[midd]->GetKey())       // ���� ������� ������ �������� � ������
			right = midd - 1;      // ������� ������ ������� ������
		else if (k > pRecs[midd]->GetKey())  // ���� ������� ������ �������� � ������
			left = midd + 1;    // ������� ����� ������� ������
		else  // ����� (�������� �����)
		{
			if (midd < DataCount)
			{
				DataCount--;
				for (int j = midd; j < DataCount; j++)
				{
					pRecs[j]->pValue = pRecs[j + 1]->pValue;
					pRecs[j]->Key = pRecs[j + 1]->Key;
				}
				pRecs[DataCount]->pValue = NULL;
				pRecs[DataCount]->Key = "";
				pRecs[DataCount] = NULL;
			}
			cheak = 0;
		}
		if (left > right) // ���� ������� ���������� 
		{
			std::cout << "Record is not found" << std::endl;
			cheak = 0;
		}
	}
	CurrPos = midd - 1;
}

void TSortTable::SortData(void)
{
	Efficiency = 0;
	switch (SortMethod)
	{
	case INSERT_SORT: {InsertSort(pRecs, DataCount); }break;
	case MERGE_SORT: {MergeSort(pRecs, DataCount); } break;
	case QUICK_SORT: {QuickSort(pRecs, DataCount); } break;
	}
}

void TSortTable::InsertSort(PTTabRecord* pRecs, int DataCount)
{
	PTTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1, j; i < DataCount; i++)
	{
		pR = pRecs[i];
		for (j = i - 1; j > -1; j--)
			if (pRecs[j]->GetKey() > pR->GetKey())
			{
				pRecs[j + 1] = pRecs[j];
				Efficiency++;
			}
			else break;
		pRecs[j + 1] = pR;
	}
}

void TSortTable::MergeSort(PTTabRecord* pRecs, int DataCount)
{
	PTTabRecord* pData = pRecs;
	PTTabRecord* pBuff = new PTTabRecord[DataCount];
	PTTabRecord* pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp)
		for (int i = 0; i < DataCount; i++) pBuff[i] = pData[i];
	delete pTemp;
}

void TSortTable::MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size)	
{
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2)
	{
		PTTabRecord* pDat2 = pData + n1, * pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1);
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);
}

void TSortTable::MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1,int n2)
{
	int i = 0, i1 = 0, i2 = 0;
	PTTabRecord* pDat1 = pData, * pDat2 = pData + n1;
	while ((i1 < n1) && (i2 < n2))
	{
		if (pDat1[i1]->Key < pDat2[i2]->Key)
			pBuff[i++] = pDat1[i1++];
		else pBuff[i++] = pDat2[i2++];
	}
	while (i1 < n1)
		pBuff[i++] = pDat1[i1++];
	while (i2<n2)
		pBuff[i++] = pDat2[i2++];
	pData = pBuff;
	pBuff = pDat1;
	Efficiency += n1 + n2;
}
void TSortTable::QuickSort(PTTabRecord* pRecs, int DataCount)
{
	int pivot;
	int n1, n2;
	if (DataCount > 1)
	{
		QuickSplit(pRecs, DataCount, pivot);
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);
		QuickSort(pRecs + n1, n2);
	}
}

void TSortTable::QuickSplit(PTTabRecord* pData, int Size, int& Pivot)
{
	PTTabRecord pPivot = pData[0], pTemp;
	int i1 = 1, i2 = Size - 1;
	while (i1 <= i2)
	{
		while ((i1 < Size) && !(pData[i1]->Key > pPivot->Key)) i1++;
		while (pData[i2]->Key > pPivot->Key) i2--;
		if (i1 < i2)
		{
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2;
	Efficiency += Size;
}
void TSortTable::Print(TTable& tab)
{
	std::cout << "Table printing" << std::endl;
	for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
	{
		std::cout << " Key: " << tab.GetKey();
		std::cout << "  Val: ";
		for (int i = 0; i < 5; i++)
			std::cout << tab.GetValuePtr()[i] << " ";
		std::cout << std::endl;
	}
}