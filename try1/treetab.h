#pragma once
#include "treenode.h"
#include "ttable.h"
#include <stack>

class TTreeTable : public TTable
{
protected:
	PTTreeNode pRoot;// указатель на корень дерева
	PTTreeNode* ppRef;// адрес указателя на вершину-результата в FindRecord
	PTTreeNode pCurrent;// указатель на текущую вершину
	int CurrPos;// номер текущей вершины
	std::stack<PTTreeNode> Stack;// стек для итератора
	void PrintTreeTab(std::ostream& os, PTTreeNode pNode);
	void DrawTreeTab(PTTreeNode pNode, int Level);
	void DeleteTreeTab(PTTreeNode pNode);// удаление
public:
	TTreeTable() : TTable()
	{
		CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL;
	}
	~TTreeTable() { DeleteTreeTab(pRoot); }
	virtual int IsFull() const;//заполнена?
	virtual int* FindRecord(TKey k);// найти запись
	virtual void InsRecord(TKey k, int* pVal);// добавить запись
	virtual void DelRecord(TKey k);// удалить запись
	virtual TKey GetKey(void) const;// получить ключ
	virtual int* GetValuePtr(void) const;// получить pValue
	virtual int Reset(void);// установить на первую запись
	virtual int IsTabEnded(void) const;// таблица завершена?
	virtual int GoNext(void);// переход к следующей записи
	virtual void Print(TTable& tab) {}
	virtual PTTabRecord* GetAllpRecs() const { return NULL; }
	friend std::ostream& operator<<(std::ostream &os, TTreeTable& tab);
	// в доработке
	void Draw(void);
	void Show(void);
protected:
	std::string tk[20];
	int t1[20], pos;
	void PutValues(PTTreeNode pNode, int Level);
};
