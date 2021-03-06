﻿/**
* \file
* \brief Methods of class for file analysis
*
* This file contains the methods and functions of the class for analyze the input file
*/
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cctype>
#include <string>
#include "FileAnalyser.h"
#include "StemmerPorter.h"
#include "utf8Converter.h"

textmap FileAnalyser::stemm(ifstream &filestream) {
	StemmerPorter sp;
	string word;
	wstring w_word;
	textmap textmap;

	while (filestream >> word)
	{
		w_word = utf8Converter::utf8_decode(word);

		// get rid of the punctuation marks
		w_word.erase(std::remove_if(w_word.begin(), w_word.end(),
			[](wchar_t ch) { return !::iswalnum(ch); }), w_word.end());

		if (!w_word.empty())
		{
			wstring stemmed = sp.get(w_word);

			// if map doesn't contain the stemmed word
			if (textmap.find(stemmed) == textmap.end()) {
				vector<wstringNo> v;
				wstringNo sn;

				// create new one
				sn.wstr = w_word;
				sn.n = 1;


				v.push_back(sn);

				// place in the table
				textmap.emplace(stemmed, v);
			}

			else // if map already contains the stemmed word
			{
				textmap::iterator it = textmap.find(stemmed);

				vector<wstringNo> v = it->second;
				bool isNew = true;

				// if the actual word is already on the list,
				// increase the number of occurrences
				for (auto & value : v) {
					if (value.wstr == w_word) {
						value.n++;
						isNew = false;
						break;
					}
				}

				// else create a new one
				if (isNew) {
					wstringNo sn;
					sn.wstr = w_word;
					sn.n = 1;

					v.push_back(sn);
				}

				it->second = v;
			}
		}
	}

	return textmap;
}

void FileAnalyser::save(const string &inputFileName, const string &outputFileName, const textmap textmap)
{
	wofstream file;
	setlocale(LC_ALL, "Russian");

	file.open(outputFileName);

	file << L"The stem table for " << utf8Converter::utf8_decode(inputFileName) << endl;

	for (auto const& stem : textmap)
	{
		file << stem.first << L";";

		for (auto const& list : stem.second) {
			file << list.wstr << L":" << list.n << L";";
		}

		file << endl;
	}

	file.close();
}

FileAnalyser::~FileAnalyser() {}