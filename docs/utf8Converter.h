/**
 * \file
 * \brief Header file with class for string conversion (Unicode <-> UTF8)
 */
#ifndef UTF_CONVERTER_H
#define UTF_CONVERTER_H
#pragma once

#include <string>
#include "Windows.h"

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
}

#endif //UTF_CONVERTER_H