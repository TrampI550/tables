#include <math.h>
#include <conio.h>
#include "baltree.h"

void TBalanceTree::InsRecord(TKey k, int* pVal)
{
	if (!IsFull())
		InsBalanceTree((PTBalanceNode)pRoot, k, pVal);
}
int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, int* pVal)
{
	int HeighIndex = HeightOK;
	if (pNode == NULL)
	{
		pNode = new TBalanceNode(k, pVal);
		HeighIndex = HeightInc;
		DataCount++;
	}
	else if (k < pNode->GetKey())
	{
		if (InsBalanceTree(PTBalanceNode(pNode->pLeft), k, pVal) == HeightInc)
			HeighIndex = LeftTreeBalancing(pNode);
	}
	else if (k > pNode->GetKey())
	{
		if (InsBalanceTree(PTBalanceNode(pNode->pRight), k, pVal) == HeightInc)
			HeighIndex = RightTreeBalancing(pNode);
	}
	else HeighIndex = HeightOK;
	return HeighIndex;
}