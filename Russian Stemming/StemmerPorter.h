#ifndef STEMMER_PORTER_H
#define STEMMER_PORTER_H

#include <regex>

using namespace std;

class StemmerPorter {
private:
	static const string EMPTY;
	static const string S1;
	static const string S13;
	static const string SN;
	static const string const1;
	static const regex PERFECTIVEGROUND;
	static const regex REFLEXIVE;
	static const regex ADJECTIVE;
	static const regex PARTICIPLE;
	static const regex VERB;
	static const regex NOUN;
	static const regex I;
	static const regex P;
	static const regex NN;
	static const regex DERIVATIONAL;
	static const regex DER;
	static const regex SUPERLATIVE;
	static const regex PUNCTUATION;

public:
	StemmerPorter();
	string get(string s);
};

#endif // STEMMER_PORTER_H