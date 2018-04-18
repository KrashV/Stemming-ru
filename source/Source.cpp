#include "StemmerPorter.h"
#include "FileAnalyser.h"

#include <cstdio>
#include <windows.h>

#define HELP_USAGE "Usage: <stemmer.exe> <path to source file> <destination .csv file>"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << HELP_USAGE;
		return -1;
	}

	try {
		std::locale::global(std::locale("Russian_Russia"));
		FileAnalyser fa(argv[1]);
		textmap textmap = fa.stemm();
		fa.save(argv[1], argv[2], textmap);
	}
	catch (std::exception &ex) {
		std::cout << "Exception occured: " << ex.what() << std::endl;
		return -1;
	}

	std::cout << "Finished sucessfully" << std::endl;

	return 0;
}