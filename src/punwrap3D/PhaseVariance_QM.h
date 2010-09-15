#ifndef __PHASEVARIANCE_QM
#define __PHASEVARIANCE_QM

#include<stdio.h>
#include<stdlib.h>

void GradVariance(float *grad_array, float *dvar_output, int xsize, int ysize, int zsize,
				  int window_size,int add_code);
void PhaseVariance(float *phase, float *result, int window_size, int x, int y,int z);

#endif
