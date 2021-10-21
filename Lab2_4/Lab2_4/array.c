#include <malloc.h>
#include "array.h"

#include "domain.h"

Vector createEmpty(int cp)
{
	/// <summary>
	/// Creates a Vector data type
	/// </summary>
	/// <param name="cp"></param>
	/// <returns>Dynamic Vector </returns>
	Vector v;
	v.cp = cp;
	v.n = 0;
	v.elems = (ElemType*)malloc(cp * sizeof(ElemType));
	return v;

}

int dim(Vector* v)
{ // Getter for the actual dimension(nr of elements) insider the vecotr pointed by V param
	return v->n;
}

ElemType elem(Vector* v, int i)
{   // returns the elem from position i 
	return v->elems[i];
}

int update(Vector* v,  ElemType c)
{  // modify the elem that has the same identify with param ElemType c
   // return 0 if update succed ( the car existed)
	// return 1 otherwhise 
	for (int i = 0; i < v->n; i++) {
		ElemType car = elem(v, i);
		if (getRegNumber(&car) == getRegNumber(&c)) {

			setModel(&v->elems[i], getModel(&c));
			setCategory(&v->elems[i], getCategory(&c));
			return 0;
		}
	}
	return 1;
}

void redim(Vector* v) {
	/// <summary>
	/// Realocates memory for the elemes of the vector
	/// </summary>
	/// <param name="v"></param>
	ElemType* elemCopy = (ElemType*)(malloc(2 * v->cp * sizeof(ElemType)));
	for (int i = 0; i < v->n; i++)
		elemCopy[i] = v->elems[i];
	v->cp = 2 * v->cp;
	free(v->elems);
	v->elems = elemCopy;
}

void append(Vector* v, ElemType c)
{/// Adds a new Element of type ElemType inside the dynamic array 

	v->elems[v->n] = c;
	v->n++;
	if (v->cp == v->n) { 
		redim(v);
	}
		
}

int findPos(Vector* v, ElemType c) {
	// returns the position of a element if it exists in the vector 
	// -1 otherwise 
	for (int i = 0; i < v->n; i++) {
		ElemType rez = elem(v, i);
		if (getRegNumber(&rez) == getRegNumber(&c))
			return i;
	}
	return -1;
}

Vector copyList(Vector* v)
{   // Make a copy of the list v 
	// return Vector containing the same elements as l)
	Vector list = createEmpty(5);
	for (int i = 0; i < dim(v); i++) {
		ElemType c = elem(v, i);
		append(&list, copyCar(&c));
	}
	return list;
}

ElemType set(Vector* v, int pos, ElemType c)
{   // Modifity the element on the given position
	// Return the overwrited element
	ElemType rez = elem(v, pos);
	v->elems[pos] = c;
	return rez;
}

int del(Vector* v, ElemType c){
	// deletes the element C from the array
	// returns 0 if the delete succed 
	// retrun 1 otherwise
	int i = findPos(v, c);
	if (i == -1)
		return 1;
	for (int j = i; j < v->n - 1; j++) {
		setRegNumber(&v->elems[j], getRegNumber(&v->elems[j + 1]));
		setModel(&v->elems[j], getModel(&v->elems[j + 1]));
		setCategory(&v->elems[j], getCategory(&v->elems[j+1]));
	}
	destroyCar(&v->elems[v->n-1]); // destory the last car 
	v->n--;
	return 0;
}

void destroy(Vector* v)
{ // free the memory space for vector v
	for (int i = 0; i < v->n; i++)
		destroyCar(&v->elems[i]);		
	free(v->elems);
}

