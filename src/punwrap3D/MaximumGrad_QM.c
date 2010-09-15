#include "MaximumGrad_QM.h"
#include "PhaseGradient.h"

void MaximumGradient(float *phase, float *result, int window_size, int x, int y,int z)
{
	int tov,i;
	float * temp1;
	tov = x*y*z;
	temp1 = (float *)malloc(tov*sizeof(float));
	for(i=0; i<tov; i++)
	{
		temp1[i] = 0.0;
	}
	DxPhaseGradient(phase,temp1,x,y,z);
 	GradMaximum(temp1,result,x,y,z,window_size,0);
	
	DyPhaseGradient(phase,temp1,x,y,z);
	GradMaximum(temp1,result,x,y,z,window_size,1);
	
	DzPhaseGradient(phase,temp1,x,y,z);
	GradMaximum(temp1,result,x,y,z,window_size,1);

	free(temp1);
}



void GradMaximum(float *grad_array, float *dvar_output, int xsize, int ysize, int zsize,
				  int window_size,int add_code)
{
	int i,j,k,a,b,c,dd,index, hs,frame,row;
	float dmax, r;

	frame = ysize*xsize;
	row = xsize;
	hs = (window_size/2);
	for(k = 0; k<zsize; k++)
	{
		for(j=0; j<ysize; j++)
		{
			for(i=0;i<xsize;i++)
			{
				index = k*frame+j*row+i;
				/*begin of window fors*/
				for(dmax=0, c=k-hs; c<=k+hs; c++)
				{
					if (c < 0 || c >= zsize) continue;
					for(b=j-hs;b<=j+hs;b++)
					{
						if (b < 0 || b >= ysize) continue;
						for(a=i-hs;a<=i+hs;a++)
						{
							if (a < 0 || a >= xsize) continue;
							
							dd = c*frame + b*row + a;
							r = grad_array[dd];
							if(r<0) r=-r;
							if(dmax < r) dmax = r;

						}
					}
				}/*end of window fors*/
				if (add_code)
					//dvar_output[index] = (dmax > dvar_output[index])? dmax : dvar_output
					dvar_output[index] += dmax;   
				else
					dvar_output[index] = dmax;   
			}
		}
	}/*end of global fors*/
}
