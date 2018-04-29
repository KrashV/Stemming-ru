/**
 * \file
 * \brief Header file with stemming algorithm class
 *
 * This file contains the definition of the stemming algorithm class for keyword search
 */
#ifndef STEMMER_PORTER_H
#define STEMMER_PORTER_H
#pragma once

#include <regex>
using namespace std;

/**
 * \brief Stemming class
 */
class StemmerPorter {
private:
  static const wstring EMPTY;
  static const wstring S1;
  static const wstring S13;
  static const wstring SN;
  static const wstring const1;
  static const wregex PERFECTIVEGROUND;
  static const wregex REFLEXIVE;
  static const wregex ADJECTIVE;
  static const wregex PARTICIPLE;
  static const wregex VERB;
  static const wregex NOUN;
  static const wregex I;
  static const wregex P;
  static const wregex NN;
  static const wregex DERIVATIONAL;
  static const wregex DER;
  static const wregex SUPERLATIVE;
  static const wregex PUNCTUATION;

public:
  /**
   * \brief Class constructor
   */
  StemmerPorter();

  /**
   * \brief Get the stemm from word
   * 
   * \param[in] s Word
   *
   * \return It's stemm
   */
  static wstring get(wstring s);
};

#endif // STEMMER_PORTER_H