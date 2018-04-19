#ifndef FILE_ANALYSER_H
#define FILE_ANALYSER_H

class FileAnalyser
{
public:

	static textmap stemm(std::ifstream &);
	static void save(const std::string &, const std::string &, const textmap);
	~FileAnalyser();
};

#endif //FILE_ANALYSER_H