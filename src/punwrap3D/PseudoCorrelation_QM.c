#include <stdlib.h>
#include <math.h>
#include "pi.h"
#include "PseudoCorrelation_QM.h"


void PseudoCorrelation(float *phase, float *result, int window_size, int x, int y,int z)
{
	int tov,i;
	float * temp1;
	tov = x*y*z;
	temp1 = (float *)malloc(tov*sizeof(float));
	for(i=0; i<tov; i++)
	{
		temp1[i] = cos(TWOPI*phase[i]);
	}

  
  SquareAvgFilter(temp1, result, x, y, z,window_size,0);

  
  {
	  temp1[i] = sin(TWOPI*phase[i]);
  }

  SquareAvgFilter(temp1, result, x, y, z,window_size,0);


  for(i=0; i<tov; i++) 
    result[i] = sqrt(result[i]);
}



void SquareAvgFilter(float *in, float *out, int xsize, int ysize, int zsize,
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
							if (aa>=0 && aa<xsize-1 && bb>=0 && bb<ysize-1 && cc>=0 && cc<zsize-1)
							{
								r = in[dd];
								avg += r;
								n++;
							}

						}
					}
				}/*end of window fors*/
				r = (n>0) ? 1.0/n : 0.0;
				avg *= r;
				if (add_code)
				out[index] +=  avg*avg;   /* variance */ 
				else
				out[index]  =  avg*avg;   /* variance  */
			}
		}
	}/*end of global fors*/
}
