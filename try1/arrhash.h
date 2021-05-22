#pragma once

#include "hashtab.h"

#define TabMaxSize 25
#define TabHashStep 5

class TArrayHash : public THashTable 
{
protected:
	PTTabRecord* pRecs;
	int TabSize;
	int HashStep;
	int FreePos;
	int CurrPos;
	PTTabRecord pMark;

	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	TArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
	~TArrayHash();

	virtual int IsFull() const { return DataCount >= TabSize; }

	virtual int* FindRecord(TKey k);
	virtual void InsRecord(TKey k, int* pVal);
	virtual void DelRecord(TKey k);

	virtual int Reset(void) { CurrPos = 0; return IsTabEnded(); }
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);

	virtual TKey GetKey(void) const;
	virtual int* GetValuePtr(void) const;
};