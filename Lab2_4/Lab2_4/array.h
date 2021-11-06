#pragma once

#include "domain.h"
typedef Car ElemType;
typedef struct {
	int cp; // capacity 
	int n; // nr of actual elements 
	ElemType* elems;
}Vector; 

Vector createEmpty(int cp);
int dim(Vector* v);
ElemType elem(Vector* v, int i);
int update(Vector* v, ElemType c);
void append(Vector* v, ElemType c);
int del(Vector* v, ElemType c);
void destroy(Vector* v);
int findPos(Vector* v, ElemType c);
Vector copyList(Vector* v);
ElemType set(Vector* v, int pos, ElemType c);


