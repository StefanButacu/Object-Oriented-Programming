#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdlib.h>
#include "domain.h"

Car createCar( int regNumber,  char* model,  char* category)
{
	/// <summary>
	/// Creates dynamically (allocs memory for the strings) a car with same fileds as params  
	/// </summary>
	/// <param name="regNumber"> integer </param>
	/// <param name="model"> char *</param>
	/// <param name="category">car * </param>
	/// <returns> a Car </returns>
	Car rez; 
	rez.regNumber = regNumber;
	size_t nrC = strlen(model) + 1;
	rez.model = malloc(sizeof(char) * nrC);
	strncpy(rez.model, model, nrC);
	nrC = strlen(category) + 1; 
	rez.category = malloc(sizeof(char) * nrC);
	strncpy(rez.category, category, nrC);
	return rez;
}

 int getRegNumber(Car *c)
{	
	/// <summary>
	/// Getter for regNumber 
	/// </summary>
	/// <param name="c">pointer to a Car </param>
	/// <returns>the regNumber </returns>
	return c->regNumber;
}

 char* getModel(Car *c)
{/// <summary>
	/// Getter for Model
	/// </summary>
	/// <param name="c">pointer to a Car </param>
	/// <returns>the Model </returns>
	return c->model;
}

 char* getCategory(Car *c)
{/// <summary>
	/// Getter for Category 
	/// </summary>
	/// <param name="c">pointer to a Car </param>
	/// <returns>the Category </returns>
	return c->category;
}

void setRegNumber(Car* c, int regNumber)
{/// <summary>
	/// Settter for regNumber 
	/// </summary>
	/// <param name="c">pointer to a Car </param>
	
	c->regNumber = regNumber;
}

void setModel(Car* c,  char* model)
{
	/// <summary>
	/// Setter for a new model. Dealocates the older memory occupied by model
	/// </summary>
	/// <param name="c"></param>
	/// <param name="model"></param>
	if (strcmp(model, "") == 0) return;
	free(c->model);
	size_t nrC = strlen(model) + 1;
	c->model = malloc(sizeof(char) * nrC);
	strncpy(c->model, model, nrC);
	//strcpy_s(c->model, nrC, model);

}

void setCategory(Car* c,  char* category)
{/// <summary>
	/// Setter for a new category. Dealocates the older memory occupied by category
	/// </summary>
	free(c->category);
	size_t nrC = strlen(category) + 1;
	c->category = malloc(sizeof(char) * nrC);
	strcpy(c->category, category);
}

void destroyCar(Car* c)
{   // free the memory allocated for a car
	free(c->model);
	free(c->category);
}




int validate(Car* c)
{/*  c - pointer to a Car structur 
	 c.category has to be suv, sport, mini, sedan
	 c.regNumber > 0  
	 len(c.model) cant be 0
	 Return 0 if the car pointed by c in valid
			1 otherwise
	 */
	if (c->regNumber <= 0)
		return 1;
	if (strlen(c->model) <= 0)
		return 1;
	char categories[5][10] = { {"suv"}, {"sport"}, {"mini"}, {"sedan"} };
	int is = 0;
	for (int i = 0; i < 5; i++) {
		if (strcmp(c->category, categories[i]) == 0)
		{
			is = 1;
			break;
		}
	}
	if (is == 0)
		return 1;

	return 0;
}

Car copyCar(Car* c)
{
	/// <summary>
	/// Creates a new car with same attributes as the car pointed by param Car* c 
	/// </summary>
	/// <param name="c"></param>
	/// <returns>A Car </returns>
	return createCar(c->regNumber, c->model, c->category);
}
