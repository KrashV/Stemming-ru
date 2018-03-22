#include "FileAnalyser.h"
#include "StemmerPorter.h"
#include <algorithm>
#include <iterator>
#include <cstdlib>

FileAnalyser::FileAnalyser(const std::string fileName)
{
	setlocale(0, "");
	filestream.open(fileName, ios::binary);

	if (!filestream.is_open()) {
		throw std::runtime_error("Could not found the file");
	}
}

size_t FileAnalyser::getSize() {
	return (size_t)filestream.tellg();
}

size_t FileAnalyser::getWordNo() {

	size_t size;
	std::istream_iterator<std::string> in { filestream }, end;
	size = std::distance(in, end);

	filestream.clear();
	filestream.seekg(0);
	return size;
}

textmap FileAnalyser::stemm() {
	StemmerPorter sp;
	string word;
	textmap textmap;

	while (filestream >> word)
	{
		// get rid of the punctuation marks
		word.erase(std::remove_if(word.begin(), word.end(), [](const unsigned char c) { return ispunct((int)c); }), word.end());

		string stemmed = sp.get(word);

		// if map doesn't contain the stemmed word
		if (textmap.find(stemmed) == textmap.end()) {
			vector<stringNo> v;
			stringNo sn;

			// create new one
			sn.str = word;
			sn.n = 1;


			v.push_back(sn);

			// place in the table
			textmap.emplace(stemmed, v);
		}

		else // if map already contains the stemmed word
		{
			textmap::iterator it = textmap.find(stemmed);

			vector<stringNo> v = it->second;
			bool isNew = true;

			// if the actual word is already on the list,
			// increase the number of occurrences
			for (auto & value : v) {
				if (value.str == word) {
					value.n++;
					isNew = false;
					break;
				}
			}

			// else create a new one
			if (isNew) {
				stringNo sn;
				sn.str = word;
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
	ofstream file;
	file.open(outputFileName);

	file << "The stem table for " << inputFileName << endl;

	for (auto const& stem : textmap)
	{
		file << stem.first << ";";

		for (auto const& list : stem.second) {
			file << list.str << ":" << list.n << ";";
		}

		file << endl;
	}

	file.close();
}

FileAnalyser::~FileAnalyser()
{
	filestream.close();
}
