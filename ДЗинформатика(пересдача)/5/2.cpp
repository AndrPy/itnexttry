#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

#include <boost/locale.hpp>

#include <Windows.h>

std::string convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

int main()
{
	system("chcp 1251");

	std::string text;
	std::getline(std::cin, text); 

	std::unordered_map < char32_t, std::u32string > equivalents =
	{
		{U'�', U"a"}, {U'�', U"b"}, {U'�', U"v"}, {U'�', U"g"}, {U'�', U"d"}, {U'�', U"e"}, {U'�', U"e"}, {U'�', U"zh"},
		{U'�', U"z"}, {U'�', U"i"}, {U'�', U"i"}, {U'�', U"k"}, {U'�', U"l"}, {U'�', U"m"}, {U'�', U"n"}, {U'�', U"o"},
		{U'�', U"p"}, {U'�', U"r"}, {U'�', U"s"}, {U'�', U"t"}, {U'�', U"u"}, {U'�', U"f"}, {U'�', U"kh"}, {U'�', U"ts"},
		{U'�', U"ch"}, {U'�', U"sh"}, {U'�', U"shch"}, {U'�', U"ie"}, {U'�', U"y"}, {U'�', U"\'"}, {U'�', U"e"}, {U'�', U"iu"}, {U'�', U"ia"},
		{U'�', U"A"}, {U'�', U"B"}, {U'�', U"V"}, {U'�', U"G"}, {U'�', U"D"}, {U'�', U"E"}, {U'�', U"E"}, {U'�', U"Zh"},
		{U'�', U"Z"}, {U'�', U"I"}, {U'�', U"I"}, {U'�', U"K"}, {U'�', U"L"}, {U'�', U"M"}, {U'�', U"N"}, {U'�', U"O"},
		{U'�', U"P"}, {U'�', U"R"}, {U'�', U"S"}, {U'�', U"T"}, {U'�', U"U"}, {U'�', U"F"}, {U'�', U"Kh"}, {U'�', U"Ts"},
		{U'�', U"Ch"}, {U'�', U"Sh"}, {U'�', U"Shch"}, {U'�',U"Ie"}, {U'�', U"Y"}, {U'�', U"\'"}, {U'�', U"E"}, {U'�', U"Iu"}, {U'�', U"Ia"}
	};

	std::string u8text = convert_locale_to_utf(text);

	std::u32string u32text = boost::locale::conv::utf_to_utf < char32_t, char >(u8text);

	std::u32string u32output;

	std::for_each(std::begin(u32text), std::end(u32text), [&equivalents, &u32output](auto x) {if (equivalents.contains(x)) { u32output += equivalents.at(x); } else { u32output += x; } return 0; });


	u8text = boost::locale::conv::utf_to_utf < char, char32_t >(u32output);

	text = convert_utf_to_locale(u8text);

	std::cout << text << std::endl;

	return 0;
}