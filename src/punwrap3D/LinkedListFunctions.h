#ifndef __LINKEDLISTFUNCTIONS
#define __LINKEDLISTFUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Voxel_Struct.h"

Edge * CreateNewNode(Voxel *pointer1, Voxel *pointer2, float Reliability, int EdgeIndex);
void Add2End(Edge **head, Edge **tail, Edge *newedge);
void DeleteList(Edge **head, Edge **tail);

#endif
