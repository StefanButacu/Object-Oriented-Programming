#pragma once
#include "array.h"

typedef int(*CmpFunction)(Car* c1, Car* c2);

void sort(Vector* v, CmpFunction cmpF);

