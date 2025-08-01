# SqliteFuzzyPlusExtension
This SQLite extension adds many different [fuzzy](https://en.wikipedia.org/wiki/Fuzzy_logic) logic functions to SQLite.
### Example SQLite Usage
##### Example#1
The following query finds a 90% match for the name "David Jorge" using the default distance method.
```` SQL
select Name, Similar(Name, "David Jorge") as s FROM SimilarNames where s > .9
````
##### Example#1
Query to list the different results of different distance methods.
```` SQL
select Name
, HowSimilar(Name, "David Jorge", "Levenshtein") as lev, HowSimilar(Name, "David Jorge", "DamerauLevenshtein") as dlev, HowSimilar(Name, "David Jorge", "LongestCommonSequence") as lcs, HowSimilar(Name, "David Jorge", "NeedlemanWunsch") as n
, HowSimilar(Name, "David Jorge", "JaroWinkler") as jw
FROM SimilarNames
````
##### Example#3 (SQLean)
Return a results that has less than 2 edit distance.
```` SQL
select Name, fuzzy_damlev(Name, "David Jorge") as d FROM SimilarNames where d < 2
````

SqliteFuzzyPlusExtension is a SQLite Fuzzy Extension which is build using both C/C++ and CSharp libraries. The Visual Studio solution builds 2 DLL (C++ & C#).
95% of the source is taken from other fuzzy libraries like [SQLean](https://github.com/nalgeon/sqlean), [Edlib](https://github.com/Martinsos/edlib), [SimMetricsCore](https://github.com/HamedFathi/SimMetricsCore), [SimMetrics.Net](https://github.com/StefH/SimMetrics.Net), [soenneker.utils.string.jaccardsimilarity](https://github.com/soenneker/soenneker.utils.string.jaccardsimilarity).

## Using SqliteFuzzyPlusExtension
- As a SQLite extension, the two DLL's are both required (SqliteFuzzyPlusExtension.dll and FuzzyPlusCSharp.dll). 
- When calling the libraries from source code, add SqliteFuzzyPlusExtension.lib to the build and for c++ code, add include **SqliteFuzzyPlusExtension.h**.
- If building in C, add ``#define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION``, before including **SqliteFuzzyPlusExtension.h**.

### Important Note!!!
When using SqliteFuzzyPlusExtension.dll with an executable like **DB Browser for SQLite**, the FuzzyPlusCSharp.dll file MUST be in the same directory as the executable (**DB Browser for SQLite.exe**). While the SqliteFuzzyPlusExtension.dll can be located anywhere.

## Using Fuzzy functions outside of SQLite
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
````
# Function List
## Fuzzy Distance Functions
- [DamerauLevenshteinDistance](https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance)
- [DiceSimilarity](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient)
- [EdlibDistance](https://github.com/Martinsos/edlib)
- [fuzzy_caver](https://github.com/nalgeon/sqlean)
- [fuzzy_damlev](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_damlev)
- [fuzzy_editdist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_editdist)
- [fuzzy_hamming](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_hamming)
- [fuzzy_jarowin](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_jarowin)
- [fuzzy_leven](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_leven)
- [fuzzy_osadist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_osadist)
- [HammingDistance](https://en.wikipedia.org/wiki/Hamming_distance)
- [JaccardDistance](https://en.wikipedia.org/wiki/Jaccard_index)
- [JaroDistance](https://en.wikipedia.org/wiki/Jaro-Winkler_distance)
- [JaroWinklerDistance](https://en.wikipedia.org/wiki/Jaro%E2%80%93Winkler_distance)
- [Levenshtein](https://en.wikipedia.org/wiki/Levenshtein_distance)
- [Levenshtein2Distance](https://en.wikipedia.org/wiki/Levenshtein_distance)
- [LongestCommonSubsequenceDistance](https://en.wikipedia.org/wiki/Longest_common_subsequence)
- [LongestCommonSubstringDistance](https://en.wikipedia.org/wiki/Longest_common_substring)
- [NormalizedLevenshteinDistance](https://en.wikipedia.org/wiki/Levenshtein_distance)
- [OverlapCoefficientDistance](https://en.wikipedia.org/wiki/Overlap_coefficient)
- [PhraseSimplifiedDiff]()
- [RatcliffObershelpSimilarityDistance](https://distancia.readthedocs.io/en/latest/Ratcliff)
- [SorensenDiceDistance](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient)
- [TanimotoCoefficientDistance]()
- [iEdlibDistance](https://github.com/Martinsos/edlib)

## Othe Fuzzy Functions
- [CaverPhone](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_caver)
- Distance
- [fuzzy_phonetic](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_phonetic)
- [fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)
- [fuzzy_script](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration)
- [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)
- [fuzzy_translit](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration)
- HasCharInSameOrder
- HowSimilar
- [NormalizeNum]()
- [RegexMatch]()
- [RegexReplace]()
- [RegexSearch]()
- [SameName]()
- [SameRSound]()
- [SameSound]()
- SetDefaultDistanceMethod

## The Plus in SqliteFuzzyPlusExtension
The plus is in the name because this extension has some extra functions that have little to do with fuzzy logic.
Here's a list of the non-fuzzy functions.
- MaxValue - Returns the value that is the highest of the two input arguments.
- StringReverse - Returns the string in reverse order.
- GetDirectoryName - Retrieves the directory information from a given path string.
- GetExtension - Retrieves the extension from a given path string.
- GetFileName - Retrieves the file name (including its extension) from a given path string.
- GetFileNameWithoutExtension - Retrieves the file name (excluding its extension) from a given path string.
- IsDirExist - Takes the path of the directory as a string argument and returns 1 or 0, where 1 means the directory exists.
- IsFileExist - Takes a string path to determine if a specified file exists and returns 1 or 0, where 1 means the file exists.



