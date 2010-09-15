#ifndef __PROCESSBORDERS
#define __PROCESSBORDERS

#include <stdio.h>
#include <stdlib.h>
#include "Voxel_Struct.h"

void processZzero(Voxel *voxels_pointer, int x, int y);
void processZfinal(Voxel *voxels_pointer, int x, int y, int z);
void ProcessFirstRows(Voxel *voxels_pointer, int x, int y, int z);
void ProcessFinalRows(Voxel *voxels_pointer, int x, int y, int z);
void ProcessFirstColoums(Voxel *voxels_pointer, int x, int y, int z);
void ProcessFinalColoums(Voxel *voxels_pointer, int x, int y, int z);

#endif
