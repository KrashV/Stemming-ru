#ifndef STEMMER_PORTER_H
#define STEMMER_PORTER_H

#include <regex>

using namespace std;

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
	StemmerPorter();
	wstring get(wstring s);
};

#endif // STEMMER_PORTER_H