#ifndef __PHASEGRADIENT
#define __PHASEGRADIENT

#include <stdio.h>
#include <stdlib.h>

void DxPhaseGradient(float *phase, float *dx, int xsize, int ysize,int zsize);
void DyPhaseGradient(float *phase, float *dy, int xsize, int ysize,int zsize);
void DzPhaseGradient(float *phase, float *dz, int xsize, int ysize,int zsize);
float WrappedDiff(float p1, float p2);

#endif
