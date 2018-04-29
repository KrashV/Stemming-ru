/**
 * \file
 * \brief Methods of stemming algorithm class
 *
 * This file contains the methods and functions of the stemming algorithm class for keyword search
 */
#include <algorithm>
#include <iterator>
#include <functional>
#include <clocale>
#include "StemmerPorter.h"

const wstring StemmerPorter::const1 = L"¿≈»Œ”€›»ﬁﬂ";
const wstring StemmerPorter::EMPTY = L"";
const wstring StemmerPorter::S1 = L"$1";
const wstring StemmerPorter::S13 = L"$1$3";
const wstring StemmerPorter::SN = L"Õ";

const wregex StemmerPorter::PERFECTIVEGROUND = wregex(L"(»¬|»¬ÿ»|»¬ÿ»—‹|€¬|€¬ÿ»|€¬ÿ»—‹|¬ÿ»|¬ÿ»—‹)$");
const wregex StemmerPorter::REFLEXIVE = wregex(L"(—ﬂ|—‹)$");
const wregex StemmerPorter::ADJECTIVE = wregex(L"(≈≈|»≈|€≈|Œ≈|»Ã»|€Ã»|≈…|»…|€…|Œ…|≈Ã|»Ã|€Ã|ŒÃ|≈√Œ|Œ√Œ|≈Ã”|ŒÃ”|»’|€’|”ﬁ|ﬁﬁ|¿ﬂ|ﬂﬂ|Œﬁ|≈ﬁ)$");
const wregex StemmerPorter::PARTICIPLE = wregex(L"(.*)(»¬ÿ|€¬ÿ|”ﬁŸ)$|([¿ﬂ])(≈Ã|ÕÕ|¬ÿ|ﬁŸ|Ÿ)$");
const wregex StemmerPorter::VERB = wregex(L"(.*)(»À¿|€À¿|≈Õ¿|≈…“≈|”…“≈|»“≈|»À»|€À»|≈…|”…|»À|€À|»Ã|€Ã|≈Õ|»ÀŒ|€ÀŒ|≈ÕŒ|ﬂ“|”≈“|”ﬁ“|»“|€“|≈Õ€|»“‹|€“‹|»ÿ‹|”ﬁ|ﬁ)$|([¿ﬂ])(À¿|Õ¿|≈“≈|…“≈|À»|…|À|≈Ã|Õ|ÀŒ|ÕŒ|≈“|ﬁ“|Õ€|“‹|≈ÿ‹|ÕÕŒ)$");
const wregex StemmerPorter::NOUN = wregex(L"(¿|≈¬|Œ¬|»≈|‹≈|≈|»ﬂÃ»|ﬂÃ»|¿Ã»|≈»|»»|»|»≈…|≈…|Œ…|»…|…|»ﬂÃ|ﬂÃ|»≈Ã|≈Ã|¿Ã|ŒÃ|Œ|”|¿’|»ﬂ’|ﬂ’|€|‹|»ﬁ|‹ﬁ|ﬁ|»ﬂ|‹ﬂ|ﬂ)$");
const wregex StemmerPorter::I = wregex(L"»$");
const wregex StemmerPorter::P = wregex(L"‹$");
const wregex StemmerPorter::NN = wregex(L"ÕÕ$");
const wregex StemmerPorter::DERIVATIONAL = wregex(L".*[^¿≈»Œ”€›ﬁﬂ]+[¿≈»Œ”€›ﬁﬂ].*Œ—“‹?$");
const wregex StemmerPorter::DER = wregex(L"Œ—“‹?$");
const wregex StemmerPorter::SUPERLATIVE = wregex(L"(≈…ÿ≈|≈…ÿ)$");

const wregex StemmerPorter::PUNCTUATION = wregex(L"[^\\w\\s]$");

StemmerPorter::StemmerPorter() {}

wstring StemmerPorter::get(wstring s) {
  transform(s.begin(), s.end(), s.begin(), towupper);
  replace(s.begin(), s.end(), '®', '≈');

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

    // Step 2: If the word ends with Ë (i), remove it. 
    rv = regex_replace(rv, I, EMPTY);

    // Step 3: Search for a DERIVATIONAL ending in R2 
    // (i.e. the entire ending must lie in R2), and if one is found, remove it. 

    if (regex_match(rv, DERIVATIONAL)) {
      rv = regex_replace(rv, DER, EMPTY);
    }

    // Step 4: (1) Undouble Ì (n), or, (2) if the word ends with a SUPERLATIVE ending, 
    // remove it and undouble Ì (n), or (3) if the word ends ¸ (') (soft sign) remove it. 
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