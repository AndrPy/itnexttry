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
		{U'à', U"a"}, {U'á', U"b"}, {U'â', U"v"}, {U'ã', U"g"}, {U'ä', U"d"}, {U'å', U"e"}, {U'¸', U"e"}, {U'æ', U"zh"},
		{U'ç', U"z"}, {U'è', U"i"}, {U'é', U"i"}, {U'ê', U"k"}, {U'ë', U"l"}, {U'ì', U"m"}, {U'í', U"n"}, {U'î', U"o"},
		{U'ï', U"p"}, {U'ð', U"r"}, {U'ñ', U"s"}, {U'ò', U"t"}, {U'ó', U"u"}, {U'ô', U"f"}, {U'õ', U"kh"}, {U'ö', U"ts"},
		{U'÷', U"ch"}, {U'ø', U"sh"}, {U'ù', U"shch"}, {U'ú', U"ie"}, {U'û', U"y"}, {U'ü', U"\'"}, {U'ý', U"e"}, {U'þ', U"iu"}, {U'ÿ', U"ia"},
		{U'À', U"A"}, {U'Á', U"B"}, {U'Â', U"V"}, {U'Ã', U"G"}, {U'Ä', U"D"}, {U'Å', U"E"}, {U'¨', U"E"}, {U'Æ', U"Zh"},
		{U'Ç', U"Z"}, {U'È', U"I"}, {U'É', U"I"}, {U'Ê', U"K"}, {U'Ë', U"L"}, {U'Ì', U"M"}, {U'Í', U"N"}, {U'Î', U"O"},
		{U'Ï', U"P"}, {U'Ð', U"R"}, {U'Ñ', U"S"}, {U'Ò', U"T"}, {U'Ó', U"U"}, {U'Ô', U"F"}, {U'Õ', U"Kh"}, {U'Ö', U"Ts"},
		{U'×', U"Ch"}, {U'Ø', U"Sh"}, {U'Ù', U"Shch"}, {U'Ú',U"Ie"}, {U'Û', U"Y"}, {U'Ü', U"\'"}, {U'Ý', U"E"}, {U'Þ', U"Iu"}, {U'ß', U"Ia"}
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