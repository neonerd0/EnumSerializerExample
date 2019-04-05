#ifndef ENUM_SERIALIZER_H
#define ENUM_SERIALIZER_H

#include <tuple>
#include <array>
#include <stdexcept>

#define ENUM_SIZE_LAST\
	enum_type_value_last

#define ENUM_STRING_PAIR_START(EnumType)\
	template<>\
	struct EnumConverter::StrEnumContainer<EnumType>\
	{\
		using ENUM_T = EnumType;\
		static constexpr EnumConverter::ARRAY_T<ENUM_T, (int)EnumType::ENUM_SIZE_LAST> StrEnumPairs\
		{\
			{

#define ENUM_STRING_PAIR_ENTRY(EnumValue)\
	{ getTuple( #EnumValue, EnumValue) }

#define ENUM_STRING_PAIR_END()\
	}};};

#define ENUM_STRING_PAIR_ENABLED\
	friend EnumConverter



static constexpr size_t constexprStringHash(char const* const str) noexcept
{
	///http://www.cse.yorku.ca/~oz/hash.html
	///djb2 hashing
	return (
		(*str != 0) ?
		(static_cast<size_t>(*str) + 33 * constexprStringHash(str + 1)) :
		5381
		);
}

class EnumConverter final
{
public:

	EnumConverter() = delete;
	EnumConverter(const EnumConverter&) = delete;
	EnumConverter(EnumConverter&&) = delete;
	EnumConverter& operator =(const EnumConverter&) = delete;
	EnumConverter& operator =(EnumConverter&&) = delete;

	template< typename ENUM_T >
	static constexpr const char* toStr(const ENUM_T value)
	{
		const auto& strEnumArray{ StrEnumContainer< ENUM_T >::StrEnumPairs };
		const char* result{ nullptr };
		for (size_t index{ 0 }; index < strEnumArray.size(); ++index)
		{
			if (std::get< 1 >(strEnumArray[index]) == value)
			{
				result = std::get< 0 >(strEnumArray[index]);
				break;
			}
		}
		return ((result == nullptr) ? throw std::logic_error{ "Enum toStrBase conversion failed" } : result);
	}

	template< typename ENUM_T >
	static constexpr ENUM_T fromStr(const char* const str)
	{
		const auto& strEnumArray{ StrEnumContainer< ENUM_T >::StrEnumPairs };
		const size_t hash{ constexprStringHash(str) };
		const ENUM_T* result{ nullptr };
		for (size_t index{ 0 }; index < strEnumArray.size(); ++index)
		{
			if (std::get< 2 >(strEnumArray[index]) == hash)
			{
				result = &(std::get< 1 >(strEnumArray[index]));
			}
		}
		return ((result == nullptr) ? throw std::logic_error{ "Enum toStrBase conversion failed" } : *result);
	}

private:
	template< typename ENUM_T, size_t LEN >
	using ARRAY_T = std::array< std::tuple< const char* const, const ENUM_T, const size_t >, LEN >;

	template< typename ENUM_T >
	static constexpr std::tuple< const char* const, ENUM_T, size_t > getTuple(const char* const str, const ENUM_T type) noexcept
	{
		return std::tuple< const char* const, ENUM_T, size_t >{ str, type, constexprStringHash(str) };
	}

	template< typename ENUM_T >
	struct StrEnumContainer
	{};

	template< typename ENUM_T >
	friend struct StrEnumContainer;
};

#endif//ENUM_SERIALIZER_H