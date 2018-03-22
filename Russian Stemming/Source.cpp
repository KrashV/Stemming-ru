#include "StemmerPorter.h"
#include "FileAnalyser.h"

#include <cstdio>
#include <windows.h>

#define HELP_USAGE "Usage: <stemmer.exe> <path to source file> <destination .csv file>"

void main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << HELP_USAGE;
		return;
	}

	FileAnalyser fa(argv[1]);
	textmap textmap = fa.stemm();
	fa.save(argv[1], argv[2], textmap);

	std::cout << "Finished sucessfully" << std::endl;
}