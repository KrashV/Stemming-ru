#include "FileAnalyser.h"
#include "StemmerPorter.h"
#include "utf8Converter.h"
#include <algorithm>
#include <iterator>
#include <cstdlib>

FileAnalyser::FileAnalyser(const std::string fileName)
{
	filestream.open(fileName, ios::binary);

	if (!filestream.is_open()) {
		throw std::runtime_error("Could not found the file");
	}
}

size_t FileAnalyser::getSize() {
	return (size_t)filestream.tellg();
}

textmap FileAnalyser::stemm() {
	StemmerPorter sp;
	string word;
	wstring w_word;
	textmap textmap;
	utf8Converter converter;

	while (filestream >> word)
	{
		w_word = converter.utf8_decode(word);
		// get rid of the punctuation marks
		w_word.erase(std::remove(w_word.begin(), w_word.end(), L'.'), w_word.end());

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

	return textmap;
}

void FileAnalyser::save(const string inputFileName, const string outputFileName, const textmap textmap)
{
	wofstream file;
	file.open(outputFileName);
	utf8Converter converter;

	file << L"The stem table for " << converter.utf8_decode(inputFileName) << endl;

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

FileAnalyser::~FileAnalyser()
{
	filestream.close();
}
