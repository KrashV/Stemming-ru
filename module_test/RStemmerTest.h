#ifndef RSTEMMERTEST_H
#define RSTEMMERTEST_H

#include "StemmerPorter.h"
#include "FileAnalyser.h"
#include <QObject>
#include <sstream>

using namespace std;
Q_DECLARE_METATYPE(std::string);

class RStemmerTest : public QObject
{
	Q_OBJECT
public:
	explicit RStemmerTest(QObject *parent = 0);

	private slots: // must be private
	void FileAnalyserWordCountTest();
	void FileAnalyserWordCountTest_data();
	void StemmerPorterFunctionalityTest_data();
	void StemmerPorterFunctionalityTest();

};

#endif // RSTEMMERTEST_H