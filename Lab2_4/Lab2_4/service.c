#define _CRT_SECURE_NO_DEPRECATE



#include <string.h>
#include <stdlib.h>
#include "service.h"
#include "domain.h"
#include "array.h"
#include "mysort.h"
#define CP 10

serviceCars createServiceCars()
{
	/// <summary>
	/// Creates the service which has 2 Empty Dynamic vectors  
	/// </summary>
	/// <returns></returns>
	serviceCars service;
	service.carList = createEmpty(CP);
	service.rentList = createEmpty(CP);
	return service;
}

int addCar(serviceCars* service,  int regNumber,  char* model,  char* category)
{/* Validate the params, construct a car and adds it.
	Return 1- if the car was added
		   0- otherwhise ( ValidationError or the Car already exists
	*/
	Car c = createCar(regNumber, model, category);
	if (validate(&c) == 0 && findPos(&service->carList, c) == -1) {
		append(&service->carList, c);
		return 0;
	}
	destroyCar(&c);
	return 1;
}

int updateCar(serviceCars* service, int regNumber, char* model, char* category)
{ /*
  Updates the car's model and category to the new values to the car that has the regNumber
  return 1 if the update wasnt possible (nonexistent car or invalid new values)
		 0 if the update succed
  */
	Car c = createCar(regNumber, model, category);
	if (validate(&c) != 0 || update(&service->carList, c) != 0) {
		destroyCar(&c);
		return 1;
	}
	destroyCar(&c);

	return 0;
}

int findCar(serviceCars* service, int regNumber) {
	// Finds the position of car that has the same regNr as 2nd parameter regNumber in the AllCars list. 
	// Return -1 if is not found 
	// Return its position otherwise 
	Car c = createCar(regNumber, "", "");
	if (findPos(&service->carList, c) == -1){
	destroyCar(&c);
	return -1;
	}
	destroyCar(&c);
	return findPos(&service->carList, c);
	
}

int findRentedCar(serviceCars* service, int regNumber)
{
	// Finds the position of car that has the same regNr as 2nd parameter regNumber in the rentedCar list. 
	// Return -1 if is not found 
	// Return its position otherwise
	Car c = createCar(regNumber, "", "");
	if (findPos(&service->rentList, c) == -1) {
		destroyCar(&c);
		return -1;
	}
	destroyCar(&c);
	return findPos(&service->rentList, c);
	
}

int delRentedCar(serviceCars* service, int regNumber) {
	// Removes the car that has the same regNr as 2nd param from rentedList 
	// Return 0 if the delete succed 
	//        -1 if is not found
	Car c = createCar(regNumber, "", "");
	if (findPos(&service->rentList, c) == -1) {
		destroyCar(&c);
		return -1;
	}
	del(&service->rentList, c);
	destroyCar(&c);
	return 0;
	
}
Vector getAll(serviceCars* service) {
	/// 
	/// <param name="service"></param>
	/// <returns>a pointer to a list of Cars </returns>
	return service->carList;
}

int getAllLenght(serviceCars* service) {
	/// <summary>
	/// gets the number of cares stored in carList ( a list which contains all the cares stored by user)
	/// </summary>
	/// <param name="service"></param>
	/// <returns></returns>
	return dim(&service->carList);
}

Vector getAllRented(serviceCars* service) {
	/// <summary>
	/// returns the vector which contains all the rented cars 
	/// </summary>
	/// <param name="service"></param>
	/// <returns></returns>
	return service->rentList;

}

int getRentedLenght(serviceCars* service) {
	/// <summary>
	/// gets the number of elements stored in rented car list 
	/// </summary>
	/// <param name="service"></param>
	/// <returns></returns>
	return dim(&service->rentList);
}


void addRentedCar(serviceCars* service, int regNumber) {
	/// <summary>
	/// Adds the car that has the same regNumber into the rented car list 
	/// </summary>
	/// <param name="service"></param>
	/// <param name="regNumber"></param>
	Car c = elem(&service->carList, findCar(service, regNumber));
	Car c2 = createCar(getRegNumber(&c), getModel(&c), getCategory(&c));
	append(&service->rentList, c2);
	
}


void destroyService(serviceCars* service) {
	/// <summary>
	/// Destroyes the memory alocated for the 2 vectors inside the service
	/// </summary>
	/// <param name="service"></param>
	destroy(&service->carList);
	destroy(&service->rentList);
}

int cmpModel(Car* c1, Car* c2)
{
	/// Function that compares the model of 2 cars 
  /// Returns 1 if model of c1 > c2 
///  Returns  0 if model of c1 = c2 
///  Returns -1 if model of c1 < c2 
	return strcmp(getModel(c1), getModel(c2));
}

int cmpCat(Car* c1, Car* c2)
{ /// Function that compares the categories of 2 cars 
  /// Returns 1 if category of c1 > c2 
///  Returns  0 if category of c1 = c2 
///  Returns -1 if category of c1 < c2 
	return strcmp(getCategory(c1), getCategory(c2));
}
/*
Vector sortByModel(serviceCars* service){
	//Creates a shallow copy of the service carList that will be sort by model ascending  

	Vector myV = copyList(&service->carList);
	sort(&myV, cmpModel);
	return myV;

}

Vector sortByCat(serviceCars* service)
{  // Creates a shallow copy of the service carList, sortes is by Category  ascending and returns the new Vector
	Vector myV = copyList(&service->carList);
	sort(&myV, cmpCat);
	return myV;
}
*/
Vector sortByFunct(serviceCars* service, CmpFunction cmpF)
{
	Vector myV = copyList(&service->carList);
	sort(&myV, cmpF);
	return myV;
}
