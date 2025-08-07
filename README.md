# SqliteFuzzyPlusExtension
This SQLite extension is the ultimate library on [fuzzy](https://en.wikipedia.org/wiki/Fuzzy_logic) logic for SQLite.
- [Using SqliteFuzzyPlusExtension](#Using-SqliteFuzzyPlusExtension)
- [Function List](#Function-List)
  - [Fuzzy Distance Functions](#Fuzzy-Distance-Functions)
  - [Phonetic Fuzzy Functions](#Phonetic-Fuzzy-Functions)
  - [Regex Functions](#Regex-Functions)
  - [SqliteFuzzyPlusExtension Fuzzy Wrapper Functions](#SqliteFuzzyPlusExtension-Fuzzy-Wrapper-Functions)
  - [Miscellaneous Fuzzy Functions](#Miscellaneous-Fuzzy-Functions)
  - [Miscellaneous Functions](#Miscellaneous-Functions)
- [Examples](#Examples)

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

For more examples, see [Documentation](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs).

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
- [BlockDistance](https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance](https://ieeexplore.ieee.org/document/8491441)
- [ChapmanLengthDeviation](https://github.com/kwunshing123/chapman-length-deviation)
- [ChapmanMeanLength](https://www.numberanalytics.com/blog/mastering-mean-length-utterance-language-sampling)
- [EuclideanDistance](https://pro.arcgis.com/en/pro-app/3.3/tool-reference/spatial-analyst/understanding-euclidean-distance-analysis.htm)
- [MatchingCoefficient]()
- [MongeElkan]()
- [QGramsDistance]()
- [SmithWaterman]()
- [SmithWatermanGotoh]()
- [SmithWatermanGotohWindowedAffine]()
- [DamerauLevenshteinDistance](https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance) - (alias = DamLev)
- [DiceSimilarity](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient)
- [EdlibDistance](https://github.com/Martinsos/edlib) - (alias = Edlib)
- [fuzzy_caver](https://github.com/nalgeon/sqlean) - (alias = caverphone)
- [fuzzy_damlev](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_damlev) - (alias = dlevenshtein)
- [fuzzy_editdist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_editdist) - (alias = edit_distance)
- [fuzzy_hamming](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_hamming) - (alias = hamming)
- [fuzzy_jarowin](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_jarowin) - (alias = jaro_winkler)
- [fuzzy_leven](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_leven) - (alias = levenshtein)
- [fuzzy_osadist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_osadist) - (alias = osa_distance)
- [HammingDistance](https://en.wikipedia.org/wiki/Hamming_distance) - (alias = HammDist)
- [JaccardDistance](https://en.wikipedia.org/wiki/Jaccard_index) - (alias = Jaccard)
- [JaroDistance](https://en.wikipedia.org/wiki/Jaro-Winkler_distance) - (alias = Jaro)
- [JaroWinklerDistance](https://en.wikipedia.org/wiki/Jaro%E2%80%93Winkler_distance) - (alias = JaroWin)
- [Levenshtein](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = Lev)
- [Levenshtein2Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = Lev2)
- [LongestCommonSubsequenceDistance](https://en.wikipedia.org/wiki/Longest_common_subsequence) - (alias = LCSQ)
- [LongestCommonSubstringDistance](https://en.wikipedia.org/wiki/Longest_common_substring) - (alias = LCS)
- [NormalizedLevenshteinDistance](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = NormLev)
- [OverlapCoefficientDistance](https://en.wikipedia.org/wiki/Overlap_coefficient) - (alias = OverlapCoef)
- [PhraseSimplifiedDiff](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#PhraseSimplifiedDiff) - (alias = PhraseDiff)
- [RatcliffObershelpSimilarityDistance](https://distancia.readthedocs.io/en/latest/Ratcliff) - (alias = Ratcliff)
- [SorensenDiceDistance](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient) - (alias = SorensenDice)
- [TanimotoCoefficientDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#TanimotoCoefficientDistance) - (alias = Tanimoto)
- [iEdlibDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#iEdlibDistance) - (alias = iEdlib)

## Phonetic Fuzzy Functions
- [CaverPhone2](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#CaverPhone2)
- [fuzzy_phonetic](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_phonetic) - (alias = phonetic_hash)
- [fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes) - (alias = rsoundex)
- [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes) - (alias = soundex)
- [fuzzy_translit](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration) - (alias = translit)
- [SameSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameSound)

## Regex Functions
- [RegexMatch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexMatch) - (alias = XMatch)
- [RegexReplace](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexReplace) - (alias = Regex)
- [RegexSearch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#RegexSearch) - (alias = XSearch)

## SqliteFuzzyPlusExtension Fuzzy Wrapper Functions
- [Distance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#Distance)
- [HowSimilar](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#HowSimilar) - (alias = Similar)
- [SameSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameSound)
- [SetDefaultDistanceMethod](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SetDefaultDistanceMethod)

## Miscellaneous Fuzzy Functions
- [fuzzy_script](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration) - (alias = script_code)
- [HasCharInSameOrder](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#HasCharInSameOrder) - (alias = HasChr)
- [SameName](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#SameName)

## Miscellaneous Functions
These minimum and maximum functions are included to allow developers to create custom percentage distance in a query.
- [MaxValue](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#MaxValue) - (alias = MaxVal)
- [MaxLength](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#MaxLength) - (alias = MaxLen)
- [MinValue](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#MinValue) - (alias = MinVal)
- [MinLength](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#MinLength) - (alias = MinLen)
- [NormalizeNum](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/README.md#NormalizeNum)

## The Plus in SqliteFuzzyPlusExtension
The plus is in the name because this extension has some extra functions that have little to do with fuzzy logic.
Here's a list of the non-fuzzy functions.
- StringReverse - Returns the string in reverse order. - (alias = StrRev)
- GetDirectoryName - Retrieves the directory information from a given path string. - (alias = GetDirName)
- GetExtension - Retrieves the extension from a given path string.
- GetFileName - Retrieves the file name (including its extension) from a given path string. - (alias = GetFileNameWithExtension)
- GetFileNameWithoutExtension - Retrieves the file name (excluding its extension) from a given path string.
- IsDirExist - Takes the path of the directory as a string argument and returns 1 or 0, where 1 means the directory exists. - (alias = DirExist)
- IsFileExist - Takes a string path to determine if a specified file exists and returns 1 or 0, where 1 means the file exists. - (alias = FileExist)

# Examples
- SQL examples are listed in the following link: [Examples](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs/Examples).
- Other examples will be posted before the non-beta version is posted.

# ToDo
- Add the following additioinal fuzzy logic.
  - BlockDistance
  - ChapmanLengthDeviation
  - ChapmanMeanLength
  - EuclideanDistance
  - MatchingCoefficient
  - MongeElkan
  - QGramsDistance
  - SmithWaterman
  - SmithWatermanGotoh
  - SmithWatermanGotohWindowedAffine
- Add additional documentation for each function with examples.
- Add more phonetic functions to the CSharp code. The C# code should have at least one version of all the SQLean phonetic functions.
- Create C example project that attaches to the extension.
- Try to figureout a way to load the extension to [DB Browser for SQLite]() without having to copy the **FuzzyPlusCSharp.dll** to the same folder as the executable.
- Add an example C# project that uses the C# fuzzy functions with SQLite without having to attach extension.
