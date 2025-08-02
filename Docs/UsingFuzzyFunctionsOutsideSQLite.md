# Using Fuzzy functions outside of SQLite
Both the FuzzyPlusCSharp library and the SqliteFuzzyPlusExtension library can be used directly without SQLite.
### C#
C# code can use FuzzyPlusCSharp directly without using the SqliteFuzzyPlusExtension. The easiest way to use FuzzyPlusCSharp in C# is to just add the Fuzzy.cs file to the C# project.

#### C++ Example Usage
```` C++
#pragma comment(lib, "SqliteFuzzyPlusExtension.lib")
#include "..\SqliteFuzzyPlusExtension.h"
double example1 = Distance("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
double example2 = Distance("David", "Davix", SqliteFuzzyPlusExtension::DamerauLevenshtein);
double example3 = Distance("David", "Davxx", SqliteFuzzyPlusExtension::JaroWinkler);
double example4 = Distance("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);
double example5 = Distance("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);
double example6 = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);
double example7 = Distance("David", "david", SqliteFuzzyPlusExtension::iLevenshtein);
double example8 = Distance("David", "davdi", SqliteFuzzyPlusExtension::iLevenshtein);

double similar00 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::UseDefaultDistanceMethod);
double similar01 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
double similar02 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::LongestCommonSequence);
double similar03 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::JaccardIndex);
double similar04 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::OverlapCoefficient);
double similar05 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::NeedlemanWunsch);
double similar06 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::SorensenDiceDistance);
double similar07 = HowSimilar("David", "david", SqliteFuzzyPlusExtension::RatcliffObershelpSimilarityDistance);
double similar08 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::HammingDistance);
double similar09 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::LongestCommonSubstringDistance);
double similar10 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::LongestCommonSubsequenceDistance);
double similar11 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::JaroDistance);
double similar12 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::NormalizedLevenshteinDistance);
double similar13 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::Levenshtein2Distance);
double similar14 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::TanimotoCoefficientDistance);
double similar15 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::EdlibDistance);
