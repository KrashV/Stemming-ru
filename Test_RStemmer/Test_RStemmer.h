#ifndef TEST_RSTEMMER_H
#define TEST_RSTEMMER_H
#include "StemmerPorter.h"
//#include "FileAnalyser.h"
#include <QObject>
#include <sstream>

using namespace std;
Q_DECLARE_METATYPE(std::string);
Q_DECLARE_METATYPE(std::wstring);

class TestRStemmer : public QObject
{
	Q_OBJECT
public:
	explicit TestRStemmer(QObject *parent = 0);

	private slots: // must be private
	//void FileAnalyserWordCountTest();
	//void FileAnalyserWordCountTest_data();
	void StemmerPorterFunctionalityTest_data();
	void StemmerPorterFunctionalityTest();

};

#endif // RSTEMMERTEST_H

