#include "UnwrapPhase.h"
#include "pi.h"

void  UnwrapImage(Voxel *Voxels_Pointer,float *Data, int x, int y, int z)
{
/* 	printf("Unwrapping the Image ..............>"); */
	int i,Frame,Row,total_no_voxels;
	total_no_voxels = x*y*z;
	Frame = x*y;
	Row = x;
	Voxel *Temp= Voxels_Pointer;

	for (i = 0; i < total_no_voxels; i++)
	{
		Temp->value += TWOPI * (float)(Temp->increment);
        Temp++;
    }
	UpdatePhaseArray(Voxels_Pointer,Data,x,y,z);
/* 	printf(" Done.\n"); */
}

void UpdatePhaseArray(Voxel *Voxels_Pointer,float *Data, int x, int y, int z)
{
	int index,Row,Frame,k,j,i;
	Row = x;
	Frame = x*y;

	Voxel *Temp = Voxels_Pointer;
	for(k=0;k<z;k++)
	{
		for(j=0;j<y;j++)
		{
			for(i=0;i<x;i++)
			{
				index = k*Frame + j*Row + i;
				Data[index]=Temp->value;
				Temp++;
			}
		}
	}
}
