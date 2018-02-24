#include "StemmerPorter.h"
#include <cctype>
#include <algorithm>
#include <iterator>
#include <functional>

const string StemmerPorter::const1 = "¿≈»Œ”€›»ﬁﬂ";
const string StemmerPorter::EMPTY = "";
const string StemmerPorter::S1 = "$1";
const string StemmerPorter::S13 = "$1$3";
const string StemmerPorter::SN = "Õ";

const regex StemmerPorter::PERFECTIVEGROUND = regex("(»¬|»¬ÿ»|»¬ÿ»—‹|€¬|€¬ÿ»|€¬ÿ»—‹|¬ÿ»|¬ÿ»—‹)$");
const regex StemmerPorter::REFLEXIVE = regex("(—ﬂ|—‹)$");
const regex StemmerPorter::ADJECTIVE = regex("(≈≈|»≈|€≈|Œ≈|»Ã»|€Ã»|≈…|»…|€…|Œ…|≈Ã|»Ã|€Ã|ŒÃ|≈√Œ|Œ√Œ|≈Ã”|ŒÃ”|»’|€’|”ﬁ|ﬁﬁ|¿ﬂ|ﬂﬂ|Œﬁ|≈ﬁ)$");
const regex StemmerPorter::PARTICIPLE = regex("(.*)(»¬ÿ|€¬ÿ|”ﬁŸ)$|([¿ﬂ])(≈Ã|ÕÕ|¬ÿ|ﬁŸ|Ÿ)$");
const regex StemmerPorter::VERB = regex("(.*)(»À¿|€À¿|≈Õ¿|≈…“≈|”…“≈|»“≈|»À»|€À»|≈…|”…|»À|€À|»Ã|€Ã|≈Õ|»ÀŒ|€ÀŒ|≈ÕŒ|ﬂ“|”≈“|”ﬁ“|»“|€“|≈Õ€|»“‹|€“‹|»ÿ‹|”ﬁ|ﬁ)$|([¿ﬂ])(À¿|Õ¿|≈“≈|…“≈|À»|…|À|≈Ã|Õ|ÀŒ|ÕŒ|≈“|ﬁ“|Õ€|“‹|≈ÿ‹|ÕÕŒ)$");
const regex StemmerPorter::NOUN = regex("(¿|≈¬|Œ¬|»≈|‹≈|≈|»ﬂÃ»|ﬂÃ»|¿Ã»|≈»|»»|»|»≈…|≈…|Œ…|»…|…|»ﬂÃ|ﬂÃ|»≈Ã|≈Ã|¿Ã|ŒÃ|Œ|”|¿’|»ﬂ’|ﬂ’|€|‹|»ﬁ|‹ﬁ|ﬁ|»ﬂ|‹ﬂ|ﬂ)$");
const regex StemmerPorter::I = regex("»$");
const regex StemmerPorter::P = regex("‹$");
const regex StemmerPorter::NN = regex("ÕÕ$");
const regex StemmerPorter::DERIVATIONAL = regex(".*[^¿≈»Œ”€›ﬁﬂ]+[¿≈»Œ”€›ﬁﬂ].*Œ—“‹?$");
const regex StemmerPorter::DER = regex("Œ—“‹?$");
const regex StemmerPorter::SUPERLATIVE = regex("(≈…ÿ≈|≈…ÿ)$");

const regex StemmerPorter::PUNCTUATION = regex("[^\\w\\s]$");

StemmerPorter::StemmerPorter() {
	setlocale(0, "");
}

string StemmerPorter::get(string s) {

	transform(s.begin(), s.end(), s.begin(), ::toupper);
	replace(s.begin(), s.end(), '®', '≈');

	size_t pos = s.find_first_of(const1, 0);

	if (pos != string::npos) {

		// Step 1: Search for a PERFECTIVE GERUND ending.
		// If one is found remove it, and that is then the end of step 1.

		string pre = s.substr(0, pos + 1);
		string rv = s.substr(pos + 1);
		string temp = regex_replace(rv, PERFECTIVEGROUND, EMPTY);

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

	transform(s.begin(), s.end(), s.begin(), tolower);
	return s;
}
