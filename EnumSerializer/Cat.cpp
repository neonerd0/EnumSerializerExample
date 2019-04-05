#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Cat.h"

ENUM_STRING_PAIR_START(Cat::Breed)
	ENUM_STRING_PAIR_ENTRY(Cat::Breed::Persian),
	ENUM_STRING_PAIR_ENTRY(Cat::Breed::Wild)
ENUM_STRING_PAIR_END()

Cat::Cat()
	:Animal(Type::Cat),
	m_breed(static_cast<Breed>(rand() % (int)Breed::enum_type_value_last))
{}

void Cat::MakeNoise()
{
	std::cout << EnumConverter::toStr(m_breed) << ": Meow!" << std::endl;
}

std::string Cat::SerializeDerived()
{
	std::stringstream ss;
	ss << EnumConverter::toStr(m_breed);
	return ss.str();
}

void Cat::DeserializeDerived(const std::string & s)
{
	m_breed = EnumConverter::fromStr<Breed>(s.c_str());
}
