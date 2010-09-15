#include "GatheringVoxels.h"
#include "pi.h"

void  Gather_Voxels(Edge *EdgesHead)
{
/* 	printf("Grouping the Voxels ................>"); */

	Voxel *voxel1;   
	Voxel *voxel2;
	Voxel *h1;
	Voxel *h2;
	Edge *Temp_e = EdgesHead;
	int incremento;

	while(Temp_e->next != NULL)
	{
		voxel1 = Temp_e->pointer1;
		voxel2 = Temp_e->pointer2;


		//pixel 1 and pixel 2 belong to different groups
		//initially each pixel is a group by it self and one pixel can construct a group
		//no else or else if to this if
		if (voxel1->head != voxel2->head)
		{
			//pixel 2 is alone in its group
			//merge this pixel with pixel 1 group and find the number of 2 pi to add 
			//to or subtract to unwrap it
			if ((voxel2->next == NULL) && (voxel2->head == voxel2))
			{
				voxel1->head->tail->next = voxel2;
				voxel1->head->tail = voxel2;
				(voxel1->head->freq) +=1;
				voxel2->head = voxel1->head;
				voxel2->increment = voxel1->increment + checkincrement(voxel2->value,voxel1->value);
			}

			//pixel 1 is alone in its group
			//merge this pixel with pixel 2 group and find the number of 2 pi to add 
			//to or subtract to unwrap it
			else if ((voxel1->next == NULL) && (voxel1->head == voxel1))
			{
				voxel2->head->tail->next = voxel1;
				voxel2->head->tail = voxel1;
				(voxel2->head->freq) +=1;
				voxel1->head = voxel2->head;
				voxel1->increment = voxel2->increment+checkincrement(voxel1->value,voxel2->value);
			}


			//pixel 1 and pixel 2 both have groups
			else
            {
				h1 = voxel1->head;
                h2 = voxel2->head;
				//the no. of pixels in pixel 1 group is large than the no. of pixels
				//in pixel 2 group.   Merge pixel 2 group to pixel 1 group
				//and find the number of wraps between pixel 2 group and pixel 1 group
				//to unwrap pixel 2 group with respect to pixel 1 group.
				//the no. of wraps will be added to pixel 2 grop in the future
				if (h1->freq > h2->freq)
				{
					//merge pixel 2 with pixel 1 group
					h1->tail->next = h2;
					h1->tail = h2->tail;
					h1->freq = h1->freq + h2->freq;
					incremento = voxel1->increment+checkincrement(voxel2->value,voxel1->value) - voxel2->increment;
					//merge the other pixels in pixel 2 group to pixel 1 group
					while (h2 != NULL)
					{
						h2->head = h1;
						h2->increment += incremento;
						h2 = h2->next;
					}
				} 

				//the no. of pixels in pixel 2 group is large than the no. of pixels
				//in pixel 1 group.   Merge pixel 1 group to pixel 2 group
				//and find the number of wraps between pixel 2 group and pixel 1 group
				//to unwrap pixel 1 group with respect to pixel 2 group.
				//the no. of wraps will be added to pixel 1 grop in the future
				else
                {
					//merge pixel 1 with pixel 2 group
					h2->tail->next = h1;
					h2->tail = h1->tail;
					h2->freq = h2->freq + h1->freq;
					incremento = voxel2->increment + checkincrement(voxel1->value,voxel2->value) - voxel1->increment;
					//merge the other pixels in pixel 2 group to pixel 1 group
					while (h1 != NULL)
					{
						h1->head = h2;
						h1->increment += incremento;
						h1 = h1->next;
					} // while

                } // else
            } //else
        } ;//if

        Temp_e=Temp_e->next;
	}
/* 	printf(" Done.\n"); */
}

int checkincrement(float destination_value, float reference_value)
{
	if((reference_value-destination_value)> PI)
	{
		return 1;
	}
	else if((reference_value - destination_value) < -PI)
	{
		return -1;
	}
	else
		return 0;
}
