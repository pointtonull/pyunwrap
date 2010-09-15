#include "OnScreenDisplay.h"

void Display_3Dfloats(float *Array,int x, int y, int z)
{
	int i,j,k, index,frame;
	frame = x*y;
	for(k=0; k<z; k++)
	{
		for(j=0; j<y; j++)
		{
			for(i=0; i<x; i++)
			{
				index = k*frame + j*x + i;
				printf("Value[%d][%d][%d]:\t%f\n",k,j,i,Array[index]);
			}
		}
	}
	printf("*****************************************************\n");
}
