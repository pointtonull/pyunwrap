#include "ProcessBorders.h"
#include "GatheringVoxels.h"
#include "pi.h"

void processZzero(Voxel *voxels_pointer, int x, int y)
{
	int i,j,Row,Frame;
	Frame = x*y;
	Row = x;
/* 	printf("Processing the Unprocessed Surfaces.............>"); */
	Voxel *temp_voxel=voxels_pointer+Row+1;
	
	for(j=1; j<y-1; j++)
	{
		for(i=1; i<x-1; i++)
		{
			temp_voxel->increment= (temp_voxel+Frame)->increment+checkincrement(temp_voxel->value,(temp_voxel+Frame)->value);
			temp_voxel++;
		}
		temp_voxel +=2;
	}
}


void processZfinal(Voxel *voxels_pointer, int x, int y, int z)
{
	int i,j,Row,Frame;
	Frame = x*y;
	Row = x;
	Voxel *temp_voxel=voxels_pointer+(z-1)*Frame+Row+1;
	
	for(j=1; j<y-1; j++)
	{
		for(i=1; i<x-1; i++)
		{
			temp_voxel->increment= (temp_voxel-Frame)->increment+checkincrement(temp_voxel->value,(temp_voxel-Frame)->value);
			temp_voxel++;
		}
		temp_voxel +=2;
	}
}

void ProcessFirstRows(Voxel *voxels_pointer, int x, int y, int z)
{
	int i,k,Row,Frame;
	Row = x;
	Frame = x*y;
	Voxel *temp_voxel;
	for(k=0; k<z; k++)
	{
		temp_voxel=voxels_pointer+(k*Frame)+1;
		for(i=1; i<x-1; i++)
		{
			temp_voxel->increment=(temp_voxel+Row)->increment+checkincrement(temp_voxel->value,(temp_voxel+Row)->value);
			temp_voxel++;
		}
	}
}

void ProcessFinalRows(Voxel *voxels_pointer, int x, int y, int z)
{
	int i,k,Row,Frame;
	Row = x;
	Frame = x*y;
	Voxel *temp_voxel;
	for(k=0; k<z; k++)
	{
		temp_voxel=voxels_pointer+(k*Frame)+((y-1)*Row)+1;
		for(i=1; i<x-1; i++)
		{
			temp_voxel->increment=(temp_voxel-Row)->increment+checkincrement(temp_voxel->value,(temp_voxel-Row)->value);
			temp_voxel++;
		}
	}
}

void ProcessFirstColoums(Voxel *voxels_pointer, int x, int y, int z)
{
	int j,k,Row,Frame;
	Row = x;
	Frame = x*y;
	Voxel *temp_voxel;
	for(k=0; k<z; k++)
	{
		temp_voxel=voxels_pointer+(k*Frame);
		for(j=0; j<y; j++)
		{
			temp_voxel->increment=(temp_voxel+1)->increment+checkincrement(temp_voxel->value,(temp_voxel+1)->value);
			temp_voxel += Row;
		}
	}
}

void ProcessFinalColoums(Voxel *voxels_pointer, int x, int y, int z)
{
	int j,k,Row,Frame;
	Row = x;
	Frame = x*y;
	Voxel *temp_voxel;
	for(k=0; k<z; k++)
	{
		temp_voxel = voxels_pointer+(k*Frame)+(Row-1);
		for(j=0; j<y; j++)
		{
			temp_voxel->increment=(temp_voxel-1)->increment+checkincrement(temp_voxel->value,(temp_voxel-1)->value);
			temp_voxel += Row;
		}
	}
/* 	printf(" Done.\n"); */
}
