#include <sstream>
#include <vector>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"

namespace
{
	std::vector<std::string> splitIntoLines(const std::string &string)
	{
		std::stringstream stream(string);
		std::vector<std::string> res;
		while (1)
		{
			std::string line;
			std::getline(stream, line);
			if (!stream.good())
				break;
			res.push_back(line);
		}
		return res;
	}
}

ENUM_STRING_PAIR_START(Animal::Type)
	ENUM_STRING_PAIR_ENTRY(Animal::Type::Dog),
	ENUM_STRING_PAIR_ENTRY(Animal::Type::Cat),
	ENUM_STRING_PAIR_ENTRY(Animal::Type::Pig)
ENUM_STRING_PAIR_END()

Animal::Animal(Type t)
	: m_type(t)
{}

std::string Animal::Serialize()
{
	std::stringstream ss;
	ss << EnumConverter::toStr(m_type) << "\n";
	ss << SerializeDerived() << "\n";

	return ss.str();
}

Animal * Animal::Deserialize(const std::string& s)
{
	auto strs = splitIntoLines(s);

	Type t = EnumConverter::fromStr<Type>(strs[0].c_str());

	Animal *newAnimal = nullptr;
	switch (t)
	{
	case Type::Dog:
		newAnimal = new Dog();
		break;

	case Type::Cat:
		newAnimal = new Cat();
		break;

	default:
		return nullptr;
	}

	newAnimal->DeserializeDerived(strs[1].c_str());
	newAnimal->m_type = t;

	return newAnimal;
}
