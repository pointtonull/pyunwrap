#include "LinkedListFunctions.h"

Edge * CreateNewNode(Voxel *pointer1, Voxel *pointer2, float Reliability, int EdgeIndex)
{
	Edge *tmp;
	tmp = (Edge*)malloc(sizeof(Edge));
	tmp->pointer1 = pointer1;
	tmp->pointer2 = pointer2;
	tmp->Reliability = Reliability;
	tmp->Edge_Index = EdgeIndex;
	tmp->next = NULL;
	tmp ->previous = NULL;
	return tmp;
}


void Add2End(Edge **head, Edge **tail, Edge *newedge)
{
	if((*head) == NULL)
	{
		(*head) = newedge;
		(*tail) = newedge;
	}
	else
	{
		newedge->previous = (*tail);
		(*tail)->next = newedge;
		newedge->next = NULL;
		(*tail) = newedge;
	}
}
/*
void Add2Front(Residue **head, Residue **tail, Residue *newres)
{
	if((*head)==NULL)
	{
		(*head) = newres;
		(*tail) = newres;
	}
	else
	{
		newres->next = (*head);
		(*head)->previous = newres;
		newres->previous = NULL;
		(*head) = newres;
	}
}

void DeleteNode(Residue **head, Residue **tail, Residue *delres)
{
	Residue *tmp, *pre;
	if( (delres == (*head)) && (delres == (*tail)) )
	{
		free(delres);
	}
	else if(delres == (*head))
	{
		tmp = delres->next;
		tmp->previous = NULL;
		(*head) = tmp;
		free(delres);
	}
	else if(delres != (*tail))
	{
		pre = delres->previous;
		tmp = delres->next;
		tmp->previous = pre;
		pre->next = tmp;
		free(delres);
	}
	else if(delres == (*tail))
	{
		pre = delres->previous;
		pre->next = NULL;
		(*tail) = pre;
		free(delres);
	}
}
*/
void DeleteList(Edge **head, Edge **tail)
{
	Edge *tmphead, *tmp;
	if(head == NULL)
	{
		 return;
	}
	tmphead = (*head);
	(*head) = NULL;
	(*tail) = NULL;
	while(tmphead != NULL)
	{
		tmp = tmphead;
		tmphead = tmphead->next;
		free(tmp);
	}
}
/*

void DisplayList(Residue *head)
{
	Residue *tmp;
	tmp = head;
	while(tmp != NULL)
	{
		printf("***********************\n");
		printf("i is:  %d.\n",tmp->i_index);
		printf("j is:  %d.\n",tmp->j_index);
		printf("k is:  %d.\n",tmp->k_index);
		printf("type is:  %d.\n",tmp->type);
		printf("sign is:  %d.\n",tmp->sign);
		printf("the previous is:  %x.\n",tmp->previous);
		printf("the next is:  %x.\n",tmp->next);
		tmp = tmp->next;
	}
}

////////////////////////////////////////////
ResPtr * CreateHeadPtr(Residue *ptrhead, Residue *ptrtail)
{
	ResPtr *tmp;
	tmp = (ResPtr*)malloc(sizeof(ResPtr));
	tmp->ptrhead = ptrhead;
	tmp->ptrtail = ptrtail;
	tmp->next = NULL;
	tmp->previous = NULL;
	return tmp;
}

void AddHandT2List(ResPtr **head,ResPtr **tail, ResPtr *newptr)
{
	if((*head) == NULL)
	{
		(*head) = newptr;
		(*tail) = newptr;
	}
	else
	{
		(*tail)->next = newptr;
		newptr->previous = (*tail);
		newptr->next = NULL;
		(*tail) = newptr;
	}
}

void DisplayLoopsHead(ResPtr *Head)
{
	ResPtr *tmp;
	tmp = Head;
	while(tmp != NULL)
	{
		printf("**********************************\n");
		printf("the head is:  %x.\n",tmp->ptrhead);
		printf("the tail is:  %x.\n",tmp->ptrtail);
		tmp = tmp->next;
	}
}
*/
