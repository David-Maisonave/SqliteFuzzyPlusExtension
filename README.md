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
See [UsingFuzzyFunctionsOutsideSQLite.md](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/UsingFuzzyFunctionsOutsideSQLite.md) for more details.

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
- [PhraseSimplifiedDiff](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#PhraseSimplifiedDiff)
- [RatcliffObershelpSimilarityDistance](https://distancia.readthedocs.io/en/latest/Ratcliff)
- [SorensenDiceDistance](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient)
- [TanimotoCoefficientDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#TanimotoCoefficientDistance)
- [iEdlibDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#iEdlibDistance)

## Othe Fuzzy Functions
- [CaverPhone](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_caver)
- [Distance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#Distance)
- [fuzzy_phonetic](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_phonetic)
- [fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)
- [fuzzy_script](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration)
- [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)
- [fuzzy_translit](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration)
- [HasCharInSameOrder](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#HasCharInSameOrder)
- [HowSimilar](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#HowSimilar)
- [NormalizeNum](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#NormalizeNum)
- [RegexMatch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexMatch)
- [RegexReplace](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexReplace)
- [RegexSearch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexSearch)
- [SameName](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameName)
- [SameRSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameRSound)
- [SameSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameSound)
- [SetDefaultDistanceMethod](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SetDefaultDistanceMethod)

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



