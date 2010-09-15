#include "EdgesCalculations.h"
#include "LinkedListFunctions.h"

extern int x_connectivity;
extern int y_connectivity;
extern int z_connectivity;

void Intialize_Voxels(Voxel * Voxels_Pointer,float *Phase,float *Quality,int x, int y, int z)
{
/* 	printf("Intialize and Fill the Voxels ...............>"); */
	int i,j,k,frame,row,index;
	Voxel *temp = Voxels_Pointer;
	
	frame = x*y;
	row = x;
	for(k=0; k<z; k++)
	{
		for(j=0; j<y; j++)
		{
			for(i=0; i<x; i++)
			{
				index = k*frame + j*row + i;
				temp->x = i;
				temp->y = j;
				temp->z = k;
				temp->value = Phase[index];
				temp->Reliability = Quality[index];
				temp->freq = 1;
				temp->increment = 0;
				temp->head = temp;
				temp->next = NULL;
				temp->tail = temp;
				temp++;
			}
		}
	}
/* 	printf(" Done.\n"); */
}

void HorizantalEdges(Voxel *voxel_pointer, Edge **EdgeHead,Edge **EdgeTail, int x, int y, int z,int *EdgeIndex)
{
	int i,j,k,Frame,Row;
	float Rel=0;
	Frame = x*y;
	Row = x;
/* 	printf("Calculating the Horizantal Edges................>"); */
	
	Voxel *voxel_temp = voxel_pointer;
	Edge *temp;
	
	for ( k =0; k<z; k++)
	{
		for(j=0; j<y; j++)
		{
			for(i=0; i<x; i++)
			{
				if (i<x-1)
				{
					Rel = voxel_temp->Reliability + (voxel_temp+1)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp+1),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
				//edges for the last voxel in the x direction (for x_connectivity)
				if ( (i==x-1) &&  x_connectivity == 1 )
				{
					Rel = voxel_temp->Reliability + (voxel_temp - Row + 1)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp - Row + 1),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
			}
		}
	}
/* 	printf(" Done.\n"); */
}

void VerticalEdges(Voxel *voxel_pointer, Edge **EdgeHead,Edge **EdgeTail, int x, int y, int z,int *EdgeIndex)
{
	int i,j,k,Frame,Row, Volume;
	float Rel;
	Frame = x*y;
	Row = x;
	Volume = x*y*z;
/* 	printf("Calculating the Vertical Edges ................>"); */
	Voxel *voxel_temp = voxel_pointer;
	Edge *temp;
	
	for (k=0; k<z; k++)
	{
		for(j=0; j<y; j++)
		{
			if (j<y-1)
			{
				for(i=0; i<x; i++)
				{
					Rel = voxel_temp->Reliability + (voxel_temp+Row)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp+Row),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
			}
				//edges for the last voxel in the y direction (for y_connectivity)
			if ( (j==y-1) &&  y_connectivity == 1 )
			{
				for(i=0; i<x; i++)
				{					
					Rel = voxel_temp->Reliability + (voxel_temp-Frame+Row)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp-Frame+Row),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
			}
		}
	}
/* 	printf(" Done.\n"); */

}

void NormalEdges(Voxel *voxel_pointer, Edge **EdgeHead,Edge **EdgeTail, int x, int y, int z,int *EdgeIndex)
{
	int i,j,k,Frame,Row, Volume;
	float Rel;
	Volume = x*y*z;
	Frame = x*y;
	Row = x;
/* 	printf("Calculating the Normal Edges............>"); */
	Voxel *voxel_temp = voxel_pointer;
	Edge *temp;
	
	for ( k =0; k<z; k++)
	{
		if (k<z-1)
		{
			for(j=0; j<y; j++)
			{
				for(i=0; i<x; i++)
				{
					Rel = voxel_temp->Reliability + (voxel_temp+Frame)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp+Frame),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
			}
		}
		if ( (k==z-1) &&  z_connectivity == 1 )
		{
			for(j=0; j<y; j++)
			{
				for(i=0; i<x; i++)
				{
					Rel = voxel_temp->Reliability + (voxel_temp-Volume+Frame)->Reliability;
					temp = CreateNewNode(voxel_temp,(voxel_temp-Volume+Frame),Rel,(*EdgeIndex));
					Add2End(EdgeHead,EdgeTail,temp);
					(*EdgeIndex)++;
					voxel_temp++;
				}
			}
		}

	}
/* 	printf(" Done.\n"); */
}
