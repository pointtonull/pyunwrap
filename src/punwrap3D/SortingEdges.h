#ifndef __SORTINGEDGES
#define __SORTINGEDGES

#include <stdio.h>
#include <stdlib.h>
#include "Voxel_Struct.h"

void Quick_Sort_Edges(Edge * begin, Edge * end, Edge *temp);
void Quick_Sort_Edges1(Edge * begin, Edge * end, Edge *temp,Edge * temp_head, Edge * temp_tail, float testvalue);
void Swap_Edges(Edge *edge1, Edge *edge2, Edge *temp);

float cmp(Edge *a, Edge *b);
Edge * MergeSort_EdgesS2B(Edge *list, int is_circular, int is_double);
Edge * MergeSort_EdgesB2S(Edge *list, int is_circular, int is_double);


#endif
