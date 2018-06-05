/**
* \file
* \brief Header file with class for string conversion (Unicode <-> UTF8)
*/
#pragma once
#include "Windows.h"
#include <string>

/**
* \brief Class for string conversion (Unicode <-> UTF8)
*/
class utf8Converter
{
public:
	/**
	* \brief Convert a wide Unicode string to an UTF8 string
	*
	* \param[in] wstr Input string Unicode
	*
	* \return Output string UTF8
	*/
	static std::string utf8_encode(const std::wstring &wstr);

	/**
	* \brief Convert an UTF8 string to a wide Unicode string
	*
	* \param[in] str Input string UTF8
	*
	* \return Output string Unicode
	*/
	static std::wstring utf8_decode(const std::string &str);
};