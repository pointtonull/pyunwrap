/* This code is a function created from the main program of Abdul-Rhaman and Gdeisat's 3D unwrapping algorithm.*/



#include "UnwrapMain.h"

int x_connectivity = 1;		//periodicity on the right and left borders of the volume
int y_connectivity = 1;		//periodicity on the front and back borders of the volume
int z_connectivity = 0;		//periodicity on the top and bottom borders of the volume


int unwrap_phs(float* wrapped, float* unwrapped, int n_sl, int n_pe, int n_fe)
{
	char outputfile[50];
	int m,x,y,z;
	int Row, Frame;
	int EdgeIndex=1;
	long total_no_voxels;
	//float TestSortValue=0;
	float *Quality_Array;

	Voxel * Voxels_Pointer;
	Edge  *EdgesHead = NULL, *EdgesTail = NULL;
	Edge *TempSortEdge = (Edge *)malloc(sizeof(Edge));
	
	//Edge *TempSortHead, *TempSortTail;
	//TempSortHead = TempSortTail = NULL;

        // Assign dimensions to data.	
	x=n_pe;
	y=n_fe;
	z=n_sl;

	Row=x;
	Frame=x*y;
	total_no_voxels=(x*y*z);
	Quality_Array = (float *)malloc(total_no_voxels*sizeof(float));
	Voxels_Pointer = (Voxel *)calloc(total_no_voxels,sizeof(Voxel));
	
        // Assign file names	
	strcpy(outputfile, "unwrap_field.img");
	
	SndDiff26(wrapped,Quality_Array,x,y,z);

        
	Intialize_Voxels(Voxels_Pointer,wrapped,Quality_Array,x,y,z);
	HorizantalEdges(Voxels_Pointer,&EdgesHead,&EdgesTail,x,y,z,&EdgeIndex);
	VerticalEdges(Voxels_Pointer,&EdgesHead,&EdgesTail,x,y,z,&EdgeIndex);
	NormalEdges(Voxels_Pointer,&EdgesHead,&EdgesTail,x,y,z,&EdgeIndex);
	
        Quick_Sort_Edges(EdgesHead,EdgesTail,TempSortEdge);

	Gather_Voxels(EdgesHead);
	processZzero(Voxels_Pointer,x,y);
	processZfinal(Voxels_Pointer,x,y,z);
	ProcessFirstRows(Voxels_Pointer, x,y,z);
	ProcessFinalRows(Voxels_Pointer, x,y,z);
	ProcessFirstColoums(Voxels_Pointer,x,y,z);
	ProcessFinalColoums(Voxels_Pointer,x,y,z);
	
	UnwrapImage(Voxels_Pointer,wrapped,x,y,z);

        memcpy(unwrapped, wrapped, total_no_voxels*sizeof(float));

	
	free(Quality_Array);
	free(Voxels_Pointer);
	free(TempSortEdge);
	DeleteList(&EdgesHead,&EdgesTail);
	//printf("\n\a**** The Image was unwrapped successfully.****\n");
	//printf("%d\n",EdgeIndex);

	return 1;
}
