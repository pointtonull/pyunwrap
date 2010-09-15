#include "SecondDiff_QM.h"
#include "pi.h"

extern int x_connectivity;
extern int y_connectivity;
extern int z_connectivity;

void SndDiff26(float *inData,float *outData,int x, int y, int z)
{
/* 	printf("Calculating the Reliabilities of the Voxels ..............>"); */
	int volume, frame, row;
	int i,j,k,index;
	float me,Horizantal, Vertical, Normal, Diag1, Diag2, Diag3, Diag4, Diag5, Diag6, Diag7, Diag8, Diag9, Diag10;
	frame = x*y;
	volume = x*y*z;
	row = x;
	for ( k=0; k<z; k++)
	{
		for(j=0; j<y; j++)
		{
			for(i=0; i<x; i++)
			{
				index = k*frame + j*row + i;
				
				if (k==0)
					outData[index]=999999+rand();
				if (k==(z-1))
					outData[index]=999999+rand();
				
				if (j==0)
					outData[index]=999999+rand();
				if (j==(y-1))
					outData[index]=999999+rand();
				
				if (i==0)
				{
					outData[index]=999999+rand();
				}
				if (i==(x-1))
				{
					outData[index]=999999+rand();
				}

				if( (i>0 && i<(x-1)) && (j>0 && j<(y-1)) && (k>0 && k<(z-1)) ) 
				{
					me = inData[index];
					Horizantal = reliability(me,inData[index-1],inData[index+1]);
					Vertical = reliability(me,inData[index-row], inData[index+row]);
					Normal = reliability(me,inData[index-frame], inData[index+frame]);
					Diag1 = reliability(me,inData[index-row-1], inData[index+row+1]);
					Diag2 = reliability(me,inData[index-row+1], inData[index+row-1]);
					Diag3 = reliability(me,inData[index-frame-row-1], inData[index+frame+row+1]);
					Diag4 = reliability(me,inData[index-frame-row], inData[index+frame+row]);
					Diag5 = reliability(me,inData[index-frame-row+1], inData[index+frame+row-1]);
					Diag6 = reliability(me,inData[index-frame-1], inData[index+frame+1]);//x
					Diag7 = reliability(me,inData[index-frame+1], inData[index+frame-1]);//x
					Diag8 = reliability(me,inData[index-frame+row-1], inData[index+frame-row+1]);
					Diag9 = reliability(me,inData[index-frame+row], inData[index+frame-row]);
					Diag10= reliability(me,inData[index-frame+row+1], inData[index+frame-row-1]);
					outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
									+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
									+pow((Diag9),2)+pow((Diag10),2),0.5);
				}
 
				if (x_connectivity == 1)
				{
					if (i==0 && (j>0 && j<(y-1)) && (k>0 && k<(z-1)))
					{
						me = inData[index];
						Horizantal = reliability(me,inData[index+row-1],inData[index+1]);
						Vertical = reliability(me,inData[index-row], inData[index+row]);
						Normal = reliability(me,inData[index-frame], inData[index+frame]);
						Diag1 = reliability(me,inData[index-1], inData[index+row+1]);
						Diag2 = reliability(me,inData[index-row+1], inData[index+2*row-1]);
						Diag3 = reliability(me,inData[index-frame-1], inData[index+frame+row+1]);
						Diag4 = reliability(me,inData[index-frame-row], inData[index+frame+row]);
						Diag5 = reliability(me,inData[index-frame-row+1], inData[index+frame+2*row-1]);
						Diag6 = reliability(me,inData[index-frame+row-1], inData[index+frame+1]);
						Diag7 = reliability(me,inData[index-frame+1], inData[index+frame+row-1]);
						Diag8 = reliability(me,inData[index-frame+2*row-1], inData[index+frame-row+1]);
						Diag9 = reliability(me,inData[index-frame+row], inData[index+frame-row]);
						Diag10= reliability(me,inData[index-frame+row+1], inData[index+frame-1]);
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}

					if (i==(x-1) && (j>0 && j<(y-1)) && (k>0 && k<(z-1)))
					{	//subtract row
						me = inData[index];
						Horizantal = reliability(me,inData[index-row+1],inData[index-1]);//13,15
						Vertical = reliability(me,inData[index-row], inData[index+row]);//11,17
						Normal = reliability(me,inData[index-frame], inData[index+frame]);//5,23
						Diag1 = reliability(me,inData[index-row-1], inData[index+1]);//10,18
						Diag2 = reliability(me,inData[index+row-1], inData[index-2*row+1]);//16,12
						Diag3 = reliability(me,inData[index-frame-row-1], inData[index+frame+1]);//1,27
						Diag4 = reliability(me,inData[index-frame-2*row+1], inData[index+frame+row-1]);//25,3
						Diag5 = reliability(me,inData[index-frame-1], inData[index+frame-row+1]);//4,24
						Diag6 = reliability(me,inData[index-frame-row+1], inData[index+frame-1]);//6,22
						Diag7 = reliability(me,inData[index-frame-row], inData[index+frame+row]);//2,26
						Diag8 = reliability(me,inData[index-frame+row-1], inData[index+frame-2*row+1]);//7,21
						Diag9 = reliability(me,inData[index-frame+row], inData[index+frame-row]);//8,20
						Diag10= reliability(me,inData[index-frame+1], inData[index+frame-row-1]);//9,19
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}
				}	
				
				if (y_connectivity== 1)
				{
					if (j==0 && (i>0 && i<(x-1)) && (k>0 && k<(z-1)))
					{
						//add frame
						me = inData[index];
						Horizantal = reliability(me,inData[index-1],inData[index+1]);//13,15
						Vertical = reliability(me,inData[index+frame-row], inData[index+row]);//11,17
						Normal = reliability(me,inData[index-frame], inData[index+frame]);//5,23
						Diag1 = reliability(me,inData[index+frame-row-1], inData[index+row+1]);//18,10
						Diag2 = reliability(me,inData[index+frame-row+1], inData[index+row-1]);//16,12
						Diag3 = reliability(me,inData[index-row-1], inData[index+frame+row+1]);//27,1
						Diag4 = reliability(me,inData[index-row], inData[index+frame+row]);//2,26
						Diag5 = reliability(me,inData[index-row+1], inData[index+frame+row-1]);//25,3
						Diag6 = reliability(me,inData[index-frame-1], inData[index+frame+1]);//4,24
						Diag7 = reliability(me,inData[index-frame+1], inData[index+frame-1]);//22,6
						Diag8 = reliability(me,inData[index-frame+row-1], inData[index+2*frame-row+1]);//7,21
						Diag9 = reliability(me,inData[index-frame+row], inData[index+2*frame-row]);//8,20
						Diag10= reliability(me,inData[index-frame+row+1], inData[index+2*frame-row-1]);//19,9
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}
					
					if (j==(y-1) && (i>0 && i<(x-1)) && (k>0 && k<(z-1)))
					{
						//subtract frame
						me = inData[index];
						Horizantal = reliability(me,inData[index+1],inData[index-1]);//13,15
						Vertical = reliability(me,inData[index-row], inData[index-frame+row]);//11,17
						Normal = reliability(me,inData[index-frame], inData[index+frame]);//5,23
						Diag1 = reliability(me,inData[index-row-1], inData[index-frame+row+1]);//10,18
						Diag2 = reliability(me,inData[index-row+1], inData[index-frame+row-1]);//12,16
						Diag3 = reliability(me,inData[index-frame-row-1], inData[index+row+1]);//1,27
						Diag4 = reliability(me,inData[index-frame-row+1], inData[index+row-1]);//3,25
						Diag5 = reliability(me,inData[index-frame-row], inData[index+row]);//2,26
						Diag6 = reliability(me,inData[index-frame-1], inData[index+frame+1]);//4,24
						Diag7 = reliability(me,inData[index-frame+1], inData[index+frame-1]);//22,6
						Diag8 = reliability(me,inData[index-2*frame+row-1], inData[index+frame-row+1]);//7,21
						Diag9 = reliability(me,inData[index-2*frame+row], inData[index+frame-row]);//8,20
						Diag10= reliability(me,inData[index-2*frame+row+1], inData[index+frame-row-1]);//9,19
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}
				}
				
				if (z_connectivity == 1)
				{
					if (k==0 && (j>0 && j<(y-1)) && (i>0 && i<(x-1)))
					{
						//add volume
						me = inData[index];
						Horizantal = reliability(me,inData[index-1],inData[index+1]);//13,15
						Vertical = reliability(me,inData[index-row], inData[index+row]);//11,17
						Normal = reliability(me,inData[index+frame], inData[index+volume-frame]);//5,23
						Diag1 = reliability(me,inData[index-row-1], inData[index+row+1]);//10,18
						Diag2 = reliability(me,inData[index-row+1], inData[index+row-1]);//12,16
						Diag3 = reliability(me,inData[index+volume-frame-row-1], inData[index+frame+row+1]);//1,27
						Diag4 = reliability(me,inData[index+volume-frame-row], inData[index+frame+row]);//2, 26
						Diag5 = reliability(me,inData[index+volume-frame-row+1], inData[index+frame+row-1]);//3,25
						Diag6 = reliability(me,inData[index+volume-frame-1], inData[index+frame+1]);//4,24
						Diag7 = reliability(me,inData[index+volume-frame+1], inData[index+frame-1]);//22,6
						Diag8 = reliability(me,inData[index+volume-frame+row-1], inData[index+frame-row+1]);//7,21
						Diag9 = reliability(me,inData[index+volume-frame+row], inData[index+frame-row]);//8,20
						Diag10= reliability(me,inData[index+volume-frame+row+1], inData[index+frame-row-1]);//9,19
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}
					if (k==(z-1) && (j>0 && j<(y-1)) && (i>0 && i<(x-1)))
					{	//subtract volume
						me = inData[index];
						Horizantal = reliability(me,inData[index+1],inData[index-1]);//13,15
						Vertical = reliability(me,inData[index-row], inData[index+row]);//11,17
						Normal = reliability(me,inData[index-frame], inData[index-volume+frame]);//5,23
						Diag1 = reliability(me,inData[index-row-1], inData[index+row+1]);//10,18
						Diag2 = reliability(me,inData[index-row+1], inData[index+row-1]);//12,16
						Diag3 = reliability(me,inData[index-frame-row-1], inData[index-volume+frame+row+1]);//1,27
						Diag4 = reliability(me,inData[index-frame-row+1], inData[index-volume+frame+row-1]);//3,25
						Diag5 = reliability(me,inData[index-frame-row], inData[index-volume+frame+row]);//2,26
						Diag6 = reliability(me,inData[index-frame-1], inData[index-volume+frame+1]);//4,24
						Diag7 = reliability(me,inData[index-frame+1], inData[index-volume+frame-1]);//6,22
						Diag8 = reliability(me,inData[index-frame+row-1], inData[index-volume+frame-row+1]);//7,21
						Diag9 = reliability(me,inData[index-frame+row], inData[index-volume+frame-row]);//8,20
						Diag10= reliability(me,inData[index-frame+row+1], inData[index-volume+frame-row-1]);//9,19
						outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2)+pow((Diag1),2)+pow((Diag2),2)
								+pow((Diag3),2)+pow((Diag4),2)+pow((Diag5),2)+pow((Diag6),2)+pow((Diag7),2)+pow((Diag8),2)
								+pow((Diag9),2)+pow((Diag10),2),0.5);
					}
				}	
			}
		}
	}
	


/* 	printf(" Done.\n"); */
}


void SndDiff6(float *inData,float *outData,int x, int y, int z)
{
/* 	printf("Calculating the Reliabilities of the Voxels ..............>"); */
	int frame, row;
	int i,j,k,index;
	float me,Horizantal, Vertical, Normal;
	frame = x*y;
	row = x;
	for ( k=1; k<z-1; k++)
	{
		for(j=1; j<y-1; j++)
		{
			for(i=1; i<x-1; i++)
			{
					index = k*frame + j*row + i;
				
					me = inData[index];
					Horizantal = reliability(me,inData[index-1],inData[index+1]);
					Vertical = reliability(me,inData[index-row], inData[index+row]);
					Normal = reliability(me,inData[index-frame], inData[index+frame]);
					outData[index] = pow(pow((Horizantal),2)+pow((Vertical),2)+pow((Normal),2),0.5);
			}
		}
	}
/* 	printf(" Done.\n"); */
}


float reliability(float me, float a, float b)
{
	float first_term, second_term, result;
	first_term = a - me;
	if (first_term > PI )
	{
		first_term = first_term - TWOPI;
	}
	else if (first_term < -PI )
	{
		first_term = first_term + TWOPI;
	}
	second_term = me - b;
	if (second_term > PI )
	{
		second_term = second_term - TWOPI;
	}
	else if (second_term < -PI )
	{
		second_term += TWOPI;
	}
	result = first_term - second_term;
	return result;
}
