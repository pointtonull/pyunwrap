#ifndef __VOXEL_STRUCT
#define __VOXEL_STRUCT

struct Voxel
{
	int x;
	int y;
	int z;
	int increment;
	int freq;
	float value;
	float Reliability;
	struct Voxel *next;
	struct Voxel *head;
	struct Voxel *tail;
};

struct Edge
{
	int Edge_Index;
	float Reliability;
	struct Voxel *pointer1;
	struct Voxel *pointer2;
	struct Edge *next;
	struct Edge *previous;
};

#define Edge  struct Edge
#define Voxel struct Voxel

#endif
