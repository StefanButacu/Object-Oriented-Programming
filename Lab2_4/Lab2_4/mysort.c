
#include "mysort.h"

void sort(Vector* v, CmpFunction cmpF)
{/// Sortes in place the vector pointed by param Vector* v, using the compareFunction cmpF

	int i, j;
	for (i = 0; i < dim(v); i++) {
		for (j = i + 1; j < dim(v); j++)
		{
			Car c1 = elem(v, i);
			Car c2 = elem(v, j);
			if (cmpF(&c1, &c2) > 0 ){
				set(v, i, c2);
				set(v, j, c1);
			}
			
		}
	}
}

