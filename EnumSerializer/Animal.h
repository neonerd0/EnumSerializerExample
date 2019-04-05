#ifndef ANIMAL_H
#define ANIMAL_H

#include "EnumSerializer.h"

class Animal
{
public:
	virtual void MakeNoise() = 0;

	std::string Serialize();
	static Animal* Deserialize(const std::string& type);

protected:
	enum class Type
	{
		Dog,
		Cat,
		Pig,
		ENUM_SIZE_LAST
	};
	ENUM_STRING_PAIR_ENABLED;

protected:
	Animal(Type t);
	virtual std::string SerializeDerived() = 0;
	virtual void DeserializeDerived(const std::string& s) = 0;

private:
	Type m_type;
};

#endif