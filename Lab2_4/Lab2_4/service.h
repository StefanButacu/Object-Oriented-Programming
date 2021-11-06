
#pragma once
#include "array.h"

typedef struct {
	Vector carList;   // dynamic array that stores all cars 
	Vector rentList;  // dynamic array that stores rented cars 
	// validatorCars v;
}serviceCars;

typedef int(*CmpFunction)(Car* c1, Car* c2);


serviceCars createServiceCars();
int addCar(serviceCars* service,  int regNumber,   char* model,  char* category);
int updateCar(serviceCars* service, int regNumber, char* model, char* category);
Vector getAll(serviceCars* service); 
int getAllLenght(serviceCars* service);
int findCar(serviceCars* service, int regNumber);

// to rent 
int findRentedCar(serviceCars* service, int regNumber);
Vector getAllRented(serviceCars* service);
void addRentedCar(serviceCars* service, int regNumber);
int getRentedLenght(serviceCars* service); 
int delRentedCar(serviceCars* service, int regNumber);

// sort 
int cmpModel(Car* c1, Car* c2);
int cmpCat(Car* c1, Car* c2);
//Vector sortByModel(serviceCars* service);
//Vector sortByCat(serviceCars* service);
Vector sortByFunct(serviceCars* service, CmpFunction cmpF);
/// dealloc memory
void destroyService(serviceCars* service);
