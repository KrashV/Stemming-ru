/**
* \file
* \brief Methods of stemming algorithm class
*
* This file contains the methods and functions of the stemming algorithm class for keyword search
*/

#include "StemmerPorter.h"
#include <algorithm>
#include <iterator>
#include <functional>
#include <clocale>

const wstring StemmerPorter::const1 = L"АЕИОУЫЭИЮЯ";
const wstring StemmerPorter::EMPTY = L"";
const wstring StemmerPorter::S1 = L"$1";
const wstring StemmerPorter::S13 = L"$1$3";
const wstring StemmerPorter::SN = L"Н";

const wregex StemmerPorter::PERFECTIVEGROUND = wregex(L"(ИВ|ИВШИ|ИВШИСЬ|ЫВ|ЫВШИ|ЫВШИСЬ|ВШИ|ВШИСЬ)$");
const wregex StemmerPorter::REFLEXIVE = wregex(L"(СЯ|СЬ)$");
const wregex StemmerPorter::ADJECTIVE = wregex(L"(ЕЕ|ИЕ|ЫЕ|ОЕ|ИМИ|ЫМИ|ЕЙ|ИЙ|ЫЙ|ОЙ|ЕМ|ИМ|ЫМ|ОМ|ЕГО|ОГО|ЕМУ|ОМУ|ИХ|ЫХ|УЮ|ЮЮ|АЯ|ЯЯ|ОЮ|ЕЮ)$");
const wregex StemmerPorter::PARTICIPLE = wregex(L"(.*)(ИВШ|ЫВШ|УЮЩ)$|([АЯ])(ЕМ|НН|ВШ|ЮЩ|Щ)$");
const wregex StemmerPorter::VERB = wregex(L"(.*)(ИЛА|ЫЛА|ЕНА|ЕЙТЕ|УЙТЕ|ИТЕ|ИЛИ|ЫЛИ|ЕЙ|УЙ|ИЛ|ЫЛ|ИМ|ЫМ|ЕН|ИЛО|ЫЛО|ЕНО|ЯТ|УЕТ|УЮТ|ИТ|ЫТ|ЕНЫ|ИТЬ|ЫТЬ|ИШЬ|УЮ|Ю)$|([АЯ])(ЛА|НА|ЕТЕ|ЙТЕ|ЛИ|Й|Л|ЕМ|Н|ЛО|НО|ЕТ|ЮТ|НЫ|ТЬ|ЕШЬ|ННО)$");
const wregex StemmerPorter::NOUN = wregex(L"(А|ЕВ|ОВ|ИЕ|ЬЕ|Е|ИЯМИ|ЯМИ|АМИ|ЕИ|ИИ|И|ИЕЙ|ЕЙ|ОЙ|ИЙ|Й|ИЯМ|ЯМ|ИЕМ|ЕМ|АМ|ОМ|О|У|АХ|ИЯХ|ЯХ|Ы|Ь|ИЮ|ЬЮ|Ю|ИЯ|ЬЯ|Я)$");
const wregex StemmerPorter::I = wregex(L"И$");
const wregex StemmerPorter::P = wregex(L"Ь$");
const wregex StemmerPorter::NN = wregex(L"НН$");
const wregex StemmerPorter::DERIVATIONAL = wregex(L".*[^АЕИОУЫЭЮЯ]+[АЕИОУЫЭЮЯ].*ОСТЬ?$");
const wregex StemmerPorter::DER = wregex(L"ОСТЬ?$");
const wregex StemmerPorter::SUPERLATIVE = wregex(L"(ЕЙШЕ|ЕЙШ)$");

const wregex StemmerPorter::PUNCTUATION = wregex(L"[^\\w\\s]$");

StemmerPorter::StemmerPorter() {

}

wstring StemmerPorter::get(wstring s) {
	transform(s.begin(), s.end(), s.begin(), towupper);
	replace(s.begin(), s.end(), L'Ё', L'Е');

	size_t pos = s.find_first_of(const1, 0);

	if (pos != wstring::npos) {

		// Step 1: Search for a PERFECTIVE GERUND ending.
		// If one is found remove it, and that is then the end of step 1.

		wstring pre = s.substr(0, pos + 1);
		wstring rv = s.substr(pos + 1);
		wstring temp = regex_replace(rv, PERFECTIVEGROUND, EMPTY);

		if (rv.size() != temp.size()) {
			rv = temp;
		}

		// Otherwise try and remove a REFLEXIVE ending, and then search in turn for 
		// (1) an ADJECTIVAL, (2) a VERB or (3) a NOUN ending. 
		// As soon as one of the endings (1) to (3) is found remove it, and terminate step 1.
		else {
			rv = regex_replace(rv, REFLEXIVE, EMPTY);
			temp = regex_replace(rv, ADJECTIVE, EMPTY);

			if (rv.size() != temp.size()) {
				rv = temp;
				rv = regex_replace(rv, PARTICIPLE, S13);
			}

			else {
				temp = regex_replace(rv, VERB, S13);
				if (rv.size() != temp.size()) {
					rv = temp;
				}
				else {
					rv = regex_replace(temp, NOUN, EMPTY);
				}
			}
		}

		// Step 2: If the word ends with и (i), remove it. 
		rv = regex_replace(rv, I, EMPTY);

		// Step 3: Search for a DERIVATIONAL ending in R2 
		// (i.e. the entire ending must lie in R2), and if one is found, remove it. 

		if (regex_match(rv, DERIVATIONAL)) {
			rv = regex_replace(rv, DER, EMPTY);
		}

		// Step 4: (1) Undouble н (n), or, (2) if the word ends with a SUPERLATIVE ending, 
		// remove it and undouble н (n), or (3) if the word ends ь (') (soft sign) remove it. 
		temp = regex_replace(rv, P, EMPTY);

		if (temp.length() != rv.length()) {
			rv = temp;
		}

		else {
			rv = regex_replace(rv, SUPERLATIVE, EMPTY);
			rv = regex_replace(rv, NN, SN);
		}
		s = pre + rv;
	}

	transform(s.begin(), s.end(), s.begin(), towlower);
	return s;
}
