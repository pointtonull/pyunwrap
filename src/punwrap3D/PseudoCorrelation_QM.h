#ifndef __PSEUDOCORRELATION_QM
#define __PSEUDOCORRELATION_QM

void PseudoCorrelation(float *phase, float *result, int window_size, int x, int y,int z);
void SquareAvgFilter(float *in, float *out, int xsize, int ysize, int zsize,
				  int window_size,int add_code);

#endif
