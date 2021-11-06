#define _CRT_SECURE_NO_DEPRECATE
//
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//
#include "tests.h"
#include "domain.h"
#include "service.h"
#include "array.h"

void testAll(){
	testDomain();
	testVector();
	testService();
	testServiceRent();
	testSort();
}

void testDomain() {
	// testing getters and setters 
	Car c1 = createCar(1, "Bla", "Suv");
	assert(getRegNumber(&c1) == 1);
	assert(strcmp(getModel(&c1), "Bla") == 0);
	assert(strcmp(getCategory(&c1), "Suv") == 0);
	setRegNumber(&c1, 55);
	setModel(&c1, "BMW");
	setCategory(&c1, "sport");
	assert(getRegNumber(&c1) == 55);
	assert(strcmp(getModel(&c1), "BMW") == 0);
	assert(strcmp(getCategory(&c1), "sport") == 0);
	// testing validator 
	assert(validate(&c1) == 0);
	destroyCar(&c1);
	Car c2 = createCar(0, "Chevy", "Blasaf");
	c2.regNumber = 0;
	assert(validate(&c2) == 1);
	c2.regNumber = 10;
	strcpy(c2.model, "");
	assert(validate(&c2) == 1);

	strcpy(c2.model, "Chevy");
	strcpy(c2.category, "Blasaf");
	assert(validate(&c2) == 1);
	destroyCar(&c2);
}

void testVector() {
	Vector myVector = createEmpty(5);
	assert(dim(&myVector) == 0);
	Car c = createCar(0, "blsaf", "fas");
	append(&myVector, c);
	assert(dim(&myVector) == 1);
	for (int i = 0; i < 10; i++) {
		Car c2 = createCar(i, "Bla", "Bla");
		append(&myVector, c2);

	}
	assert(dim(&myVector) == 11  );
	// test update the first car  
	Car newCar = createCar(0, "a", "b");
	assert(update(&myVector, newCar) == 0); // it was a succes 
	assert(strcmp(getModel(&myVector.elems[0]), "a") == 0);
	assert(strcmp(getCategory(&myVector.elems[0]), "b") == 0);
	destroyCar(&newCar);
	newCar = createCar(15, "a", "b");
	assert(update(&myVector, newCar) == 1); // returns 1 because this car does not exists 
	destroyCar(&newCar);
	// delete a car 
	newCar = createCar(0, "a", "b");
	assert(del(&myVector, newCar) == 0);
	assert(dim(&myVector) == 10);
	destroyCar(&newCar);

	// inexisting car
	newCar = createCar(15, "a", "b");
	assert(del(&myVector, newCar) == 1);
	assert(dim(&myVector) == 10);
	destroyCar(&newCar);
	
	destroy(&myVector);
}

void testService() {
	serviceCars service = createServiceCars();
	// testing with validation and unicity
	int reg = 1;
	char model[] = "BMW";
	char cat[] = "sport";
	assert(dim(&service.carList) == 0);
	assert(addCar(&service, reg, model, cat) == 0);
	assert(getAllLenght(&service) == 1);
	assert(findCar(&service, 1) == 0);  // the car with regNr = 1 is on pos 0 
	assert(findCar(&service, 5) == -1);  // the car with regNr = 5 doesn't exist 



	// invalid car
	reg = -1;
	strcpy(model, "");
	strcpy(cat, "basf");
	// duplicated car
	assert(addCar(&service, reg, model, cat) == 1);
	assert(dim(&service.carList) == 1);
	// updating
	int newReg = 1;
	char newModel[] = "LAMBO";
	char newCategory[] = "mini";
	assert(updateCar(&service, newReg, newModel, newCategory) == 0);
	// check updates 
	// ///
	Vector getCars = getAll(&service);
	assert(strcmp(getCars.elems[0].model, "LAMBO") == 0);
	assert(strcmp(getCars.elems[0].category, "mini") == 0);
	// try to update an inexistent car 
	assert(updateCar(&service, 78, newModel, newCategory) == 1);
	// try to update to an invalid car 
	assert(updateCar(&service, newReg, "", "") == 1);
	
	destroyService(&service);
		
}

void testServiceRent() {
	serviceCars service = createServiceCars();
	addCar(&service, 1, "a", "suv");
	addCar(&service, 2, "b", "suv");
	addCar(&service, 3, "aa", "mini");
	assert(getRentedLenght(&service) == 0);
	addRentedCar(&service, 1);
	assert(getRentedLenght(&service) == 1);
	assert(findRentedCar(&service, 1) == 0);
	assert(delRentedCar(&service, 1) == 0);
	assert(delRentedCar(&service, 2) == -1); // unrentedCar
	assert(getRentedLenght(&service) == 0);

	assert(findRentedCar(&service, 3) == -1) ; // unrentedCar 
	Vector rentList = getAllRented(&service);
	assert(rentList.n == 0);
	destroyService(&service);
}

void testSort() {
	serviceCars service = createServiceCars();
	addCar(&service, 1, "a", "suv");
	addCar(&service, 2, "b", "suv");
	addCar(&service, 3, "aa", "mini");
	addCar(&service, 4, "c", "sport");
	//Vector sortModel1 = sortByModel(&service);
	Vector sortModel1 = sortByFunct(&service, cmpModel);
	
	assert(getRegNumber(&sortModel1.elems[0]) == 1);    // a 
 	assert(getRegNumber(&sortModel1.elems[1]) == 3); // aa
	assert(getRegNumber(&sortModel1.elems[2]) == 2); // b 
	assert(getRegNumber(&sortModel1.elems[3]) == 4); // c 
	
	destroy(&sortModel1);
	
//	Vector sortCat1 = sortByCat(&service);
	Vector sortCat1 = sortByFunct(&service, cmpCat);
	assert(getRegNumber(&sortCat1.elems[0]) == 3);
	assert(getRegNumber(&sortCat1.elems[1]) == 4);
	assert(getRegNumber(&sortCat1.elems[2]) == 1);
	assert(getRegNumber(&sortCat1.elems[3]) == 2);
	destroy(&sortCat1);

	
	destroyService(&service);
}