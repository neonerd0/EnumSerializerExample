#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "Dog.h"
#include "Cat.h"

int main()
{
	srand(time(NULL));

	Dog d1;
	d1.MakeNoise();
	std::string dog = d1.Serialize();

	Cat c1;
	c1.MakeNoise();
	std::string cat = c1.Serialize();

	Animal *newCat = Animal::Deserialize(cat);
	newCat->MakeNoise();

	Animal *newDog = Animal::Deserialize(dog);
	newDog->MakeNoise();

	return 0;
}