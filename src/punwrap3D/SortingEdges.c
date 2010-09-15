#include "SortingEdges.h"

void Quick_Sort_Edges(Edge * begin, Edge * end, Edge *temp)
{
	float testvalue;
	Edge *temp_head, *temp_tail;
	if((end->Edge_Index ) > (begin->Edge_Index))
	{
		testvalue= begin->Reliability;
		temp_head = begin->next;
		temp_tail = end->previous;
		if(begin->Reliability > end->Reliability)
		{
			Swap_Edges(begin,end,temp);
		}
		
		while(temp_head->Edge_Index <= temp_tail->Edge_Index)
		{
			if(temp_head->Reliability <= testvalue)
			{
				temp_head = temp_head->next;
			}
			else
			{
				Swap_Edges(temp_head,temp_tail,temp);
				temp_tail = temp_tail->previous;
			}
		}
		temp_head = temp_head->previous;
		temp_tail = temp_tail->next;
		Swap_Edges(begin,temp_head,temp);
		Quick_Sort_Edges(begin,temp_head,temp);
		Quick_Sort_Edges(temp_tail,end,temp);
	}
}

void Swap_Edges(Edge *edge1, Edge *edge2, Edge *temp)
{
	temp->Reliability = edge2->Reliability;
	temp->pointer1 =  edge2->pointer1;
	temp->pointer2 = edge2->pointer2;

	edge2->Reliability = edge1->Reliability;
	edge2->pointer1= edge1->pointer1;
	edge2->pointer2 = edge1->pointer2;

	edge1->Reliability = temp->Reliability;
	edge1->pointer1 = temp->pointer1;
	edge1->pointer2 = temp->pointer2;

}

