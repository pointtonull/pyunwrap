#ifndef __UNWRAPMAIN
#define __UNWRAPMAIN

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "LinkedListFunctions.h"
#include "OnScreenDisplay.h"
#include "SecondDiff_QM.h"
#include "pi.h"
#include "Voxel_Struct.h"
#include "EdgesCalculations.h"
#include "SortingEdges.h"
#include "GatheringVoxels.h"
#include "ProcessBorders.h"
#include "UnwrapPhase.h"
#include "PhaseGradient.h"
#include "PhaseVariance_QM.h"
#include "MaximumGrad_QM.h"
#include "PseudoCorrelation_QM.h"

#endif

int unwrap_phs(float* wrapped, float* unwrapped, int n_sl, int n_pe, int n_fe);
