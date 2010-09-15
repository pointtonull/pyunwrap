#include "PhaseVariance_QM.h"
#include "PhaseGradient.h"

void PhaseVariance(float *phase, float *result, int window_size, int x, int y,int z)
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
 	GradVariance(temp1,result,x,y,z,window_size,1);
	
	DyPhaseGradient(phase,temp1,x,y,z);
	GradVariance(temp1,result,x,y,z,window_size,1);
	
	DzPhaseGradient(phase,temp1,x,y,z);
	GradVariance(temp1,result,x,y,z,window_size,1);

	free(temp1);
}



void GradVariance(float *grad_array, float *dvar_output, int xsize, int ysize, int zsize,
				  int window_size,int add_code)
{
	int i,j,k,a,b,c,aa,bb,cc,dd,index, n, hs,frame,row;
	float avg, avgsqr,r;

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
				avg = avgsqr = 0.0;
				/*begin of window fors*/
				for(n=0, c=k-hs; c<=k+hs; c++)
				{
					cc = c;
					if(cc < 0) cc = -cc;
					else if(cc >= zsize) cc = 2*zsize - 2 - cc;
					for(b=j-hs;b<=j+hs;b++)
					{
						bb = b;
						if(bb < 0) bb = -bb;
						else if(bb >= ysize) bb = 2*ysize - 2 - bb;
						for(a=i-hs;a<=i+hs;a++)
						{
							aa = a;
							if(aa < 0) aa = -aa;
							else if(aa >= xsize) aa = 2*xsize - 2 - aa;
							
							dd = cc*frame + bb*row + aa;
							r = grad_array[dd];
							avg += r;
							avgsqr += r*r;
							n++;

						}
					}
				}/*end of window fors*/
				r = (n>0) ? 1.0/n : 0.0;
				avg *= r;
				avgsqr *= r;
				if (add_code)
				dvar_output[index] += avgsqr - avg*avg;   /* variance */ 
				else
				dvar_output[index] = avgsqr - avg*avg;   /* variance  */
			}
		}
	}/*end of global fors*/
}


