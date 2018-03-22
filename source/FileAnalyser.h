#ifndef FILE_ANALYSER_H
#define FILE_ANALYSER_H

class FileAnalyser
{

private:
	std::ifstream filestream;

public:

	FileAnalyser(const std::string fileName);


	size_t getSize();
	size_t getWordNo();

	textmap stemm();
	void save(const std::string, const std::string, const textmap);
	~FileAnalyser();
};

#endif //FILE_ANALYSER_H