#ifndef CAT_H
#define CAT_H

#include "Animal.h"
#include "EnumSerializer.h"

class Cat : public Animal
{
public:
	Cat();
	virtual void MakeNoise() override;

protected:
	virtual std::string SerializeDerived() override;
	virtual void DeserializeDerived(const std::string& s) override;

private:
	enum class Breed
	{
		Persian,
		Wild,
		ENUM_SIZE_LAST
	};

	ENUM_STRING_PAIR_ENABLED;

	Breed m_breed;
};

#endif