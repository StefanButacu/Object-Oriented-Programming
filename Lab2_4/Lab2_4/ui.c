#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include "domain.h"
#include "service.h"

void printMenu() {
	printf("(DONE) 1. Print all cars\n");
	printf("(DONE) 2. Add a car\n");
	printf("(DONE) 3. Update car\n");
	printf("(DONE) 4. Rent a car\n");
	printf("(DONE) 5. Return a car\n");
	printf("(DONE) 6. See cars by option\n");
	printf("(DONE) 7. Sort cars by option\n");
	printf("(----) 8. Undo\n");
	printf("0. Exit\n");
}

void SeeCarsByOption(serviceCars* service) {
	// Lets user to see cars by category or model
	int cmd;
	printf("Select one of the following options\n1->Category\n2->Model\n");
	scanf("%d", &cmd);
	Vector cars = getAll(service);
	int lenght = getAllLenght(service);
	int found = 0;
	if (cmd == 1) {
		char searchCategory[10];
		printf("Enter the category\n");
		scanf("%s", searchCategory);
		for (int i = 0; i < lenght; i++) {
			Car c = elem(&cars, i);
			if (strcmp(getCategory(&c), searchCategory) == 0) {
				found++;
				printf("Car-> RegNr: %3d, Model: %s, Category: %s\n", getRegNumber(&c), getModel(&c), getCategory(&c));
			}
		}
		if (!found) {
			printf("%s","There are no cars from this category!\n");
		}
	}
	else {
		if (cmd == 2) {
			char searchModel[10];
			printf("Enter the model\n");
			scanf("%s", searchModel);
			for (int i = 0; i < lenght; i++) {
				Car c = elem(&cars, i);
				if (strcmp(getModel(&c), searchModel) == 0) {
					found++;
					printf("Car-> RegNr: %3d, Model: %s, Category: %s\n", getRegNumber(&c), getModel(&c), getCategory(&c));
				}
			}
			if (!found)
				printf("%s", "There are no cars for this model!\n");
		}
		else
			printf("Invalid option!\n");
	}

}

void updateMenu(serviceCars* service) {
	// Update menu which asks user to input the regNr of the car the he wanna update, and the new values 
	// which will be updated (model and cateogy)
	// Prints a message if the car is not Valid
	// Prints a message if there is not car with the same regNr
	int regNr;
	char model[15];
	char category[15];
	printf("Give the registrationNumber of the car that you wanna update: ");
	scanf("%d", &regNr);
	printf("Give the new model: ");
	scanf("%s", model);
	printf("Give the category( Has to be one of these: {suv}, {sport}, {mini}, {sedan}) : ");
	scanf("%s", category);
	if (updateCar(service, regNr, model, category))  // should warn the user that he updates a rented car ? 
		printf("Something went wrong!\n");
	else
		printf("Succesful operation\n");
}

void addMenu(serviceCars* service) {
	// Add car menu which asks for user input for regNr, model and category
	// Prints a message in the car is not valid 
	// Prints a message if a car with same regNr is stored already
	int regNumber;
	char model[10];
	char category[10];
	printf("Give the registration number: ");
	scanf("%d", &regNumber);
	printf("Give the model: ");
	scanf("%s", &model);
	printf("Give the category( Has to be one of these: {suv}, {sport}, {mini}, {sedan}) : ");
	scanf("%s", &category);

	int errorCode = addCar(service, regNumber, model, category);
	if (errorCode == 0)
		printf("Succesful proces!\n");
	else
		printf("Error at saving the car!\n");
}

void getAllMenu(serviceCars* service) {
	// Prints all the  cars if they exits, or a message if none cares are stored 

	Vector cars = getAll(service);
	int lenght = getAllLenght(service);
	if (lenght > 0){
		printf("----------------------------------------- \n");

		printf("Cars: \n");
		for (int i = 0; i < lenght; i++) {
			// getters not working  -> done 
			Car c = elem(&cars, i);
			printf("Car %d:  NR- %d , Model-%s, Cat-%s \n", i, getRegNumber(&c), getModel(&c), getCategory(&c));

		}
		printf("----------------------------------------- \n");

	}
	else
		printf("There are no cars in here\n"); 
}


void printRentedCars(serviceCars* service) {
	// Prints all the rented cars if they exits, or a message if none cares are rented 
	Vector cars = getAllRented(service);
	int lenght = getRentedLenght(service);
	if (lenght > 0) {
		printf("----------------------------------------- \n");

		printf("Rented cars: \n");
		for (int i = 0; i < lenght; i++) {

			Car c = elem(&cars, i);
			printf("Car %d:  regNr- %d , Model-%s, Cat-%s \n", i, getRegNumber(&c), getModel(&c), getCategory(&c));

		}
		printf("----------------------------------------- \n");

	}
	else
		printf("There are no rented cars in here\n");
}

void returnCarsMenu(serviceCars* service) {
	// Return the care menu which let user to enter a regNumber for the car that we wanna return
	// Prints a message if the car hasnt been rented or the car does not exit
	printRentedCars(service);
	printf("Give the regNumber of the car that you wanna return: ");
	int regNr;
	scanf("%d", &regNr);
	int posAllCars = findCar(service, regNr);
	if (posAllCars == -1) {
		printf("The car does not exits!\n");
		return;
	}
	else {
		int posRentedCar = findRentedCar(service, regNr);
		if (posRentedCar == -1) {
			printf("This car is NOT rented! \n");
			return;
		}
		else {
			delRentedCar(service, regNr);
		}
	}
	

}
void rentCarsMenu(serviceCars* service) {
	// Rent a car menu which let user to enter a registration Number for a car that he want to rent
	// Prints a message if the car is already rented or it does not exits
	printf("Give the regNumber of the car that you wanna rent: ");
	int regNr;
	scanf("%d", &regNr);
	// from carList search for the car then append it in rentList 
	// show a message if the car does not exists 
	int posRentedCar = findRentedCar(service, regNr); 
	if (posRentedCar != -1) {
		printf("This car is already rented!\n");
		printRentedCars(service);

		return;
	}
	int posAllCars = findCar(service, regNr);
	if (posAllCars == -1) {
		printf("The car does not exits!\n");
		printRentedCars(service);

		return;
	}
	// add car to rented list 
	printf("Now, this car is rented! \n");
	addRentedCar(service, regNr);
	printf("All rented cars are: \n");
	printRentedCars(service);
}

void sortCarsMenu(serviceCars* service) {
	// Sort Cars menu that let user to enter the field and the order that he wanna sort
	printf("Enter the number of field that you want to sort:\n1.Model\n2.Category\n-> ");
	int field;
	scanf("%d", &field);
	printf("Enter\n1.Ascending order\n2.Descending order\n-> ");
	int order;
	scanf("%d", &order);
	if (field == 1) {
		Vector v = sortByFunct(service, cmpModel);
		if (order == 1) {
			for (int i = 0; i < dim(&v); i++) {
				Car c = elem(&v, i);
				printf("Car:  regNr- %d , Model-%s, Cat-%s \n",  getRegNumber(&c), getModel(&c), getCategory(&c));
			}
			printf("\n");
		}
		else {
			for (int i = dim(&v) - 1; i >=0 ; i--) {
				Car c = elem(&v, i);
				printf("Car:  regNr- %d , Model-%s, Cat-%s \n", getRegNumber(&c), getModel(&c), getCategory(&c));
			}
			printf("\n");
		}
		destroy(&v);
		return;
	}
	if (field == 2) {
		Vector v = sortByFunct(service,cmpCat);
		if (order == 1) {
			for (int i = 0; i < dim(&v); i++) {
				Car c = elem(&v, i);
				printf("Car:  regNr- %d , Model-%s, Cat-%s \n", getRegNumber(&c), getModel(&c), getCategory(&c));
			}
			printf("\n");
		}
		else {
			for (int i = dim(&v) - 1; i >= 0; i--) {
				Car c = elem(&v, i);
				printf("Car:  regNr- %d , Model-%s, Cat-%s \n", getRegNumber(&c), getModel(&c), getCategory(&c));
			}
			printf("\n");
		}
		destroy(&v);
	}

}
void run(serviceCars *service) {
	// The console for user inter-action
	int running = 1;
	int cmd; 

	while (running) {
		printMenu();
		printf("Give the command ---> ");
		scanf("%d", &cmd);
		switch (cmd) {
		case 0:
			running = 0;
			break; 
		case 1:
			getAllMenu(service);
			break;
		case 2:
			addMenu(service);
			break;
		case 3: 
			updateMenu(service);
			break;
		case 4:
			rentCarsMenu(service);
			break;
		case 5:
			returnCarsMenu(service);
			break;
		case 6:
			SeeCarsByOption(service);
			break;
		case 7:
			sortCarsMenu(service);
			break;
		default:
			printf("Invalid command");
		}

	}
}
