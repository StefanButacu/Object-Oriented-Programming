#pragma once
#ifndef DOMAIN_H_
#define DOMAIN_H_

typedef struct  {
	int regNumber; 
	char* model;
	char* category;
} Car;


Car createCar( int regNumber,  char* model,  char* category);
 int getRegNumber(Car *c);
 char* getModel(Car *c);
 char* getCategory(Car *c );
void setRegNumber(Car* c, int regNumber);
void setModel(Car* c,  char* model);
void setCategory(Car* c,  char* category);
void destroyCar(Car* c);
int validate(Car* c); 
Car copyCar(Car* c);

#endif // !DOMAIN_H_

