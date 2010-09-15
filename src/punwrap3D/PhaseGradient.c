#include "PhaseGradient.h"
#include "pi.h"

void DxPhaseGradient(float *phase, float *dx, int xsize, int ysize,int zsize)
{
  int  i, j, k,index,frame,row;
  float  grad;
  frame = xsize*ysize;
  row = xsize;
  for (k=0; k<zsize; k++)
  {
	  for (j=0; j<ysize; j++)
	  {
		for (i=0; i<xsize; i++)
		{
		  index = k*frame + j*row + i;
		  if (i < xsize - 1) 
			//grad = Gradient(phase[index+1], phase[k]);
			grad = WrappedDiff(phase[index+1], phase[index]);
		  else 
			grad = WrappedDiff(phase[index-1], phase[index]);
		  dx[index] = grad;
		}
	  }
  }
}


void DyPhaseGradient(float *phase, float *dy, int xsize, int ysize,int zsize)
{
  int  i, j, k,index, frame,row;
  float  grad;
  frame = xsize*ysize;
  row = xsize;
  for (k=0; k<zsize; k++)
  {
	  for (j=0; j<ysize; j++)
	  {
		for (i=0; i<xsize; i++)
		{
		  index = k+frame+ j*row + i;
		  if (j < ysize - 1) 
			grad = WrappedDiff(phase[index+row], phase[index]);
		  else 
			grad = WrappedDiff(phase[index-row], phase[index]);
		  dy[index] = grad;
		}
	  }
  }
}

void DzPhaseGradient(float *phase, float *dz, int xsize, int ysize,int zsize)
{
  int  i, j, k,index, frame,row;
  float  grad;
  frame = xsize*ysize;
  row = xsize;
  for (k=0; k<zsize; k++)
  {
	  for (j=0; j<ysize; j++)
	  {
		for (i=0; i<xsize; i++)
		{
		  index = k+frame+ j*row + i;
		  if (k < zsize - 1) 
			grad = WrappedDiff(phase[index+frame], phase[index]);
		  else 
			grad = WrappedDiff(phase[index-frame], phase[index]);
		  dz[index] = grad;
		}
	  }
  }
}

float WrappedDiff(float p1, float p2)
{
	float r;
	r = p1 - p2;
	if(r >  PI) r -= TWOPI;
	if(r < -PI) r += TWOPI;
	return r;
}
