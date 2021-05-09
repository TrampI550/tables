#include "scantab.h"

int* TScanTable::FindRecord(TKey k)
{
    int i;
    for (i = 0; i < DataCount; i++)
        if (pRecs[i]->Key == k) break;
    Efficiency = i + 1;
    if (i < DataCount) { CurrPos = i; return pRecs[i]->pValue; }
    return NULL;
}
void TScanTable::InsRecord(TKey k, int* pVal)
{
    if (!IsFull())
    {
        //pRecs[DataCount] = new TTabRecord;
        //pRecs[DataCount]->Key = k;
        //pRecs[DataCount]->pValue = pVal;
        pRecs[DataCount] = new TTabRecord(k, pVal);
        CurrPos = DataCount;
        DataCount++;
    }
}
void TScanTable::DelRecord(TKey k)
{
    int i;
    for (i = 0; i < DataCount; i++)
        if (pRecs[i]->Key == k) break;
    Efficiency = i + 1;
    if (i < DataCount)
    { 
        DataCount--;
        for (int j = i; j < DataCount; j++)
        {
            pRecs[j]->pValue = pRecs[j + 1]->pValue;
            pRecs[j]->Key = pRecs[j + 1]->Key;
        }
        pRecs[DataCount]->pValue = NULL;
        pRecs[DataCount]->Key = "";
        pRecs[DataCount] = NULL;
        CurrPos = i - 1;
    }
}