#include <QTest>
#include "Test_RStemmer.h"
#include <iostream>
#include <cstdio>
TestRStemmer::TestRStemmer(QObject *parent) :
	QObject(parent)
{
}

/*Deleted test
void TestRStemmer::FileAnalyserWordCountTest_data()
{
	QTest::addColumn<wstring>("FileName");
	QTest::addColumn<int>("WordCount");
	QTest::newRow("words") << wstring (L"Test_data/words.txt") << 11;
	QTest::newRow("words_and_empty_lines") << wstring(L"Test_data/words_and_empty_lines.txt") << 11;
	QTest::newRow("empty") << wstring (L"Test_data/empty.txt") << 0;
	QTest::newRow("whitespace_chars") << (wstring) (L"Test_data/whitespace_chars.txt") << 0;
}*/

/*void TestRStemmer::FileAnalyserWordCountTest()
{
	QFETCH(string, FileName);
	QFETCH(int, WordCount);
	try {
		//FileAnalyser fa;
		//QCOMPARE((int)fa.getWordNo(FileName), WordCount);
	}
	catch (std::exception &ex) {
		std::cout << "Exception occured: " << ex.what() << std::endl;
		QVERIFY(false);
	}
}*/


void TestRStemmer::StemmerPorterFunctionalityTest1_data()
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Stem");
	std::wstring str1;
	std::wstring str2;
	int i = 1;
	char testName[] = "word_00";//name for test

	QFile file("../../Test_data/words.txt");
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		QString qstr1, qstr2;
		while (!stream.atEnd())
		{
			qstr1 = stream.readLine();
			str1 = qstr1.toStdWString();
			qstr2 = stream.readLine();
			str2 = qstr2.toStdWString();

			testName[6] = i + '0';
			QTest::newRow(testName) << wstring(str1) << wstring(str2);
			
			if (i == 9) {
				testName[5]++;
				i = 0;
				continue;
			}
			i++;

		}
		if (stream.status() != QTextStream::Ok)
		{
			qDebug() << "Exception occured";
		}
		file.close();
	}

}

void TestRStemmer::StemmerPorterFunctionalityTest1()
{
	static_cast<void>(std::locale::global(std::locale("Russian_Russia")));
	QFETCH(wstring, Word);
	QFETCH(wstring, Stem);
	StemmerPorter sp;
	QCOMPARE(sp.get(Word), Stem);
}


QTEST_MAIN(TestRStemmer)
