#ifndef DOG_H
#define DOG_H

#include "Animal.h"
#include "EnumSerializer.h"

class Dog : public Animal
{
public:
	Dog();
	virtual void MakeNoise() override;

protected:
	virtual std::string SerializeDerived() override;
	virtual void DeserializeDerived(const std::string& s) override;

private:
	enum class Breed
	{
		Poodle,
		Dalmatian,
		Pug,
		ENUM_SIZE_LAST
	};

	ENUM_STRING_PAIR_ENABLED;

	Breed m_breed;
};

#endif