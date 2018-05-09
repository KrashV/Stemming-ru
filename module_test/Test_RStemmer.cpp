#include <QTest>
#include "Test_RStemmer.h"
#include <iostream>
#include <cstdio>
TestRStemmer::TestRStemmer(QObject *parent) :
	QObject(parent)
{
}

//void TestRStemmer::FileAnalyserWordCountTest_data()
//{
//	QTest::addColumn<wstring>("FileName");
//	QTest::addColumn<int>("WordCount");
//	QTest::newRow("words") << wstring (L"Test_data/words.txt") << 11;
//	QTest::newRow("words_and_empty_lines") << wstring(L"Test_data/words_and_empty_lines.txt") << 11;
//	QTest::newRow("empty") << wstring (L"Test_data/empty.txt") << 0;
//	QTest::newRow("whitespace_chars") << (wstring) (L"Test_data/whitespace_chars.txt") << 0;
//}
//
//void TestRStemmer::FileAnalyserWordCountTest()
//{
//	//QFETCH(string, FileName);
//	//QFETCH(int, WordCount);
//	//try {
//	//	//FileAnalyser fa;
//	//	//QCOMPARE((int)fa.getWordNo(FileName), WordCount);
//	//}
//	//catch (std::exception &ex) {
//	//	std::cout << "Exception occured: " << ex.what() << std::endl;
//	//	QVERIFY(false);
//	//}
//}

void TestRStemmer::StemmerPorterFunctionalityTest_data()
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Stem");
	
	QTest::newRow("word_1") << wstring (L"агрохимия") << wstring(L"агрохим");
	QTest::newRow("word_2") << wstring(L"адаптировавшийся") << wstring(L"адаптирова");
	QTest::newRow("word_3") << wstring(L"акции") << wstring(L"акц");
	QTest::newRow("word_4") << wstring(L"влюбившись") << wstring(L"влюб");
	QTest::newRow("word_5") << wstring(L"домов") << wstring(L"дом");
	QTest::newRow("word_6") << wstring(L"давешний") << wstring(L"давешн");
	QTest::newRow("word_7") << wstring(L"красивейше") << wstring(L"красив");
	QTest::newRow("word_8") << wstring(L"красить") << wstring(L"крас");
	QTest::newRow("word_9") << wstring(L"малолетней") << wstring(L"малолетн");
	QTest::newRow("word_10") << wstring(L"маленьким") << wstring(L"маленьк");
	QTest::newRow("word_11") << wstring(L"сериями") << wstring(L"сер");
	QTest::newRow("word_12") << wstring(L"улья") << wstring(L"ул");
}


void TestRStemmer::StemmerPorterFunctionalityTest()
{
	static_cast<void>(std::locale::global(std::locale("Russian_Russia")));
	QFETCH(wstring, Word);
	QFETCH(wstring, Stem);
	StemmerPorter sp;
	QCOMPARE(sp.get(Word), Stem);

}

QTEST_MAIN(TestRStemmer)
//#include "RStemmerTest.moc"
//#include "moc_RStemmerTest.cpp"