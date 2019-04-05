#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Dog.h"

ENUM_STRING_PAIR_START(Dog::Breed)
	ENUM_STRING_PAIR_ENTRY(Dog::Breed::Dalmatian),
	ENUM_STRING_PAIR_ENTRY(Dog::Breed::Poodle),
	ENUM_STRING_PAIR_ENTRY(Dog::Breed::Pug)
ENUM_STRING_PAIR_END()

Dog::Dog()
	: Animal(Animal::Type::Dog), 
	m_breed(static_cast<Breed>(rand() % (int)Breed::enum_type_value_last))
{}

void Dog::MakeNoise()
{
	std::cout << EnumConverter::toStr(m_breed) << ": Woof!" <<std::endl;
}

std::string Dog::SerializeDerived()
{
	std::stringstream ss;
	ss << EnumConverter::toStr(m_breed);
	return ss.str();
}

void Dog::DeserializeDerived(const std::string & s)
{
	m_breed = EnumConverter::fromStr<Breed>(s.c_str());
}
