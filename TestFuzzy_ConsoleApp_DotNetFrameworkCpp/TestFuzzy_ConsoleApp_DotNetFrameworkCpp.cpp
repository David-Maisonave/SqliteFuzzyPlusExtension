#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include <atlstr.h>
using namespace std;
using namespace System;

static void CreateScript(string rootDir, string fieldName, string table, string FunctionName, string text, bool byName) 
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    ofstream f(rootDir + FunctionName + fileName + table + ".sql");
    f << "select " << fieldName << endl;
    for (int i = 0; i < (int)FuzzyPlusCSharp::Fuzzy::DistanceMethod::iEdlibDistance; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetDistanceMethodName(i);
        string distanceName = CW2A(d);
        if (std::isdigit(distanceName[0]))
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", '" << text << "', ";
        if (byName)
            f << "'" << distanceName << "'";
        else
            f << i;
        f << ") as a" << i << " -- " << distanceName << " (ID# " << i << ")" << endl;
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: Case insensitive functions have an ID number greater than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE << endl;
    f << "--       C++ functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY << " and less than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE << endl;
    f << "--       Tokenize functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::TOKEN_METHODS << " and less than " << FuzzyPlusCSharp::Fuzzy::PHRASE_METHODS << endl;
    f << "--       Phrase functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::PHRASE_METHODS << " and less than " << FuzzyPlusCSharp::Fuzzy::METHODS_UP_FOR_DELETION << endl;
    f << "--       Functions that are being considered for deletion have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::METHODS_UP_FOR_DELETION << " and less than " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY << endl;
    f.close();
}
static void CreateScript(string rootDir, string fieldName, string table, string FunctionName, string text) 
{
    CreateScript(rootDir, fieldName, table, FunctionName, text, false);
    CreateScript(rootDir, fieldName, table, FunctionName, text, true);
}

static void CreateUnitTestSqlFile()
{
    string rootDir = "..\\TestData\\AutoCreatedSqlScript\\";
    CreateScript(rootDir, "Name", "SimilarNames", "Distance", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "Distance", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "Distance", "David");
    CreateScript(rootDir, "Name", "SimilarNames", "HowSimilar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "HowSimilar", "David");
    CreateScript(rootDir, "Name", "SimilarNames", "Similar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "Similar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "Similar", "David");

    CreateScript(rootDir, "Name", "SimilarNames", "IsVerySimilar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsVerySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "IsVerySimilar", "David");

    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSomeWhatSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSlightlySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsHardlySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsNotSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "This is a similar phrase test");

}

int main() //array<System::String ^> ^args)
{
    CreateUnitTestSqlFile();
    return 0;
}
