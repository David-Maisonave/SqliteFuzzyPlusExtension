# SqliteFuzzyPlusExtension
This SQLite extension is the ultimate library on [fuzzy](https://en.wikipedia.org/wiki/Fuzzy_logic) logic for SQLite.
## Content
- [Using SqliteFuzzyPlusExtension](#Using-SqliteFuzzyPlusExtension)
  - [Using SqliteFuzzyPlusExtension With SQLite](#Using-SqliteFuzzyPlusExtension-With-SQLite)
  - [Using SqliteFuzzyPlusExtension Without SQLite](#Using-SqliteFuzzyPlusExtension-Without-SQLite)
- [Function List](#Function-List)
  - [Fuzzy String Matching Algorithms](#Fuzzy-String-Matching-Algorithms)
  - [Phonetic Fuzzy Functions](#Phonetic-Fuzzy-Functions)
  - [Regex Functions](#Regex-Functions)
  - [SqliteFuzzyPlusExtension Fuzzy Wrapper Functions](#SqliteFuzzyPlusExtension-Fuzzy-Wrapper-Functions)
  - [Miscellaneous Fuzzy Functions](#Miscellaneous-Fuzzy-Functions)
  - [Miscellaneous Functions](#Miscellaneous-Functions)
- [Examples](#Examples)
- [ToDo](#ToDo)

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
95% of the source is taken from other fuzzy libraries like [SimMetricsCore](https://github.com/HamedFathi/SimMetricsCore), [SQLean](https://github.com/nalgeon/sqlean), [Edlib](https://github.com/Martinsos/edlib), [SimMetrics.Net](https://github.com/StefH/SimMetrics.Net), [jaccardsimilarity](https://github.com/soenneker/soenneker.utils.string.jaccardsimilarity), [Phonix](https://github.com/eldersantos/phonix), and [Microsoft PhoneticMatching](https://github.com/microsoft/PhoneticMatching).

## Using SqliteFuzzyPlusExtension
### Using SqliteFuzzyPlusExtension With SQLite
- As a SQLite extension, the two DLL's are both required (SqliteFuzzyPlusExtension.dll and FuzzyPlusCSharp.dll). 
- When calling the libraries from source code, add SqliteFuzzyPlusExtension.lib to the build and for c++ code, add include **SqliteFuzzyPlusExtension.h**.
- If building in C, add ``#define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION``, before including **SqliteFuzzyPlusExtension.h**.

#### Important Note!!!
When using SqliteFuzzyPlusExtension.dll with an executable like **DB Browser for SQLite**, the FuzzyPlusCSharp.dll file MUST be in the same directory as the executable (**DB Browser for SQLite.exe**). While the SqliteFuzzyPlusExtension.dll can be located anywhere.

### Using SqliteFuzzyPlusExtension Without SQLite
- Using Fuzzy functions outside of SQLite
  - Both the FuzzyPlusCSharp library and the SqliteFuzzyPlusExtension library can be used directly without SQLite.
  - See [UsingFuzzyFunctionsOutsideSQLite.md](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/Docs/UsingFuzzyFunctionsOutsideSQLite.md) for more details.

# Function List
## Fuzzy String Matching Algorithms
- Edit Distance Based Methods
  - [Levenshtein](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = Lev)
  - [Levenshtein2Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = Lev2)
  - [DamerauLevenshteinDistance](https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance) - (alias = DamLev)
  - [NormalizedLevenshteinDistance](https://en.wikipedia.org/wiki/Levenshtein_distance) - (alias = NormLev)
  - [HammingDistance](https://en.wikipedia.org/wiki/Hamming_distance) - (alias = HammDist)
  - [JaroWinklerDistance](https://en.wikipedia.org/wiki/Jaro%E2%80%93Winkler_distance) - [more](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Jaro-Winkler) - (alias = JaroWin)
  - [JaroDistance](https://en.wikipedia.org/wiki/Jaro-Winkler_distance) - [more](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Jaro) - (alias = Jaro)
  - [ChapmanLengthDeviation](https://github.com/kwunshing123/chapman-length-deviation)
  - [EuclideanDistance](https://en.wikipedia.org/wiki/Euclidean_distance) - [more](https://pro.arcgis.com/en/pro-app/3.3/tool-reference/spatial-analyst/understanding-euclidean-distance-analysis.htm)
  - [ChapmanMeanLength](https://www.numberanalytics.com/blog/mastering-mean-length-utterance-language-sampling) - This method does not give expected results, and is only here for testing and comparisons purposes.
  - [EdlibDistance](https://github.com/Martinsos/edlib) - (alias = Edlib)
  - [fuzzy_damlev](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_damlev) - (alias = dlevenshtein)
  - [fuzzy_editdist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_editdist) - (alias = edit_distance)
  - [fuzzy_hamming](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_hamming) - (alias = hamming)
  - [fuzzy_jarowin](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_jarowin) - (alias = jaro_winkler)
  - [fuzzy_leven](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_leven) - (alias = levenshtein)
  - [fuzzy_osadist](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_osadist) - (alias = osa_distance)
- Sequence Alignment Based Methods
  - [LongestCommonSequence](https://reference.wolfram.com/language/ref/LongestCommonSequence.html)
  - [LongestCommonSubsequenceDistance](https://en.wikipedia.org/wiki/Longest_common_subsequence) - (alias = LCSQ)
  - [LongestCommonSubstringDistance](https://en.wikipedia.org/wiki/Longest_common_substring) - (alias = LCS)
  - [NeedlemanWunsch](https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm) - [more](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Needleman-Wunsch)
  - [RatcliffObershelpSimilarityDistance](https://distancia.readthedocs.io/en/latest/Ratcliff) - (alias = Ratcliff)
  - [SmithWaterman](https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm)
  - [SmithWatermanGotoh](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Smith-Waterman-Gotoh)
  - [SmithWatermanGotohWindowedAffine](https://github.com/amuller/libsim/commit/19e5c21919dee595696890d0d6e324377e93e734)
- Token Based Methods
  - [CosineSimilarity](https://en.wikipedia.org/wiki/Cosine_similarity)
  - [JaccardIndex](https://en.wikipedia.org/wiki/Jaccard_index)
  - [JaccardSimilarity](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Jaccard_Similarity_Coefficient)
  - [TanimotoCoefficientDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#TanimotoCoefficientDistance) - (alias = Tanimoto)
  - [OverlapCoefficientDistance](https://en.wikipedia.org/wiki/Overlap_coefficient) - [more](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Overlap_Coefficient) - (alias = OverlapCoef)
  - [SorensenDiceDistance](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient) - (alias = SorensenDice)
  - [DiceSimilarity](https://en.wikipedia.org/wiki/Dice-S%C3%B8rensen_coefficient) - [more](https://wiki.melissadata.com/index.php?title=Matchcode_Optimization:Dice%27s_Coefficient)
  - [BlockDistance](https://ieeexplore.ieee.org/document/8491441)
  - [MatchingCoefficient](https://en.wikipedia.org/wiki/Simple_matching_coefficient)
  - [QGramsDistance](https://tilores.io/q-gram-algorithm-online-tool)
  - [NGramsDistance](https://github.com/Dandraka/FuzzySubstringSearch) - [more](https://en.wikipedia.org/wiki/N-gram)
- Hybrid Algorithms 
  - [MongeElkan](https://anhaidgroup.github.io/py_stringmatching/v0.4.x/MongeElkan.html) - [more](https://www.gelbukh.com/CV/Publications/2009/Generalized%20Mongue-Elkan%20Method%20for%20Approximate%20Text%20String.pdf)
  - [Sift4](https://siderite.dev/blog/super-fast-and-accurate-string-distance.html) Not in build, but in source code. Will be included in next build (0.1.5)
- Phrase token methods
  - [PhraseTokenize](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#PhraseSimplifiedDiff) - (alias = PhraseDiff)
  - [SimplePhraseTokenize](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#PhraseSimplifiedDiff)

## Phonetic Fuzzy Functions
- [Caverphone2](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#Caverphone2)
- [fuzzy_phonetic](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#fuzzy_phonetic) - (alias = phonetic_hash)
- [fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes) - (alias = rsoundex)
- [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes) - (alias = soundex)
- [fuzzy_translit](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration) - (alias = translit)
- [fuzzy_caver](https://github.com/nalgeon/sqlean) - (alias = caverphone)
- [EnPhoneticDistance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#EnPhoneticDistance)
- [Soundex2](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#Soundex2)
- [SameSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#SameSound)

## Regex Functions
- [RegexMatch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#RegexMatch) - (alias = XMatch)
- [RegexReplace](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#RegexReplace) - (alias = Regex)
- [RegexSearch](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#RegexSearch) - (alias = XSearch)

## SqliteFuzzyPlusExtension Fuzzy Wrapper Functions
- [Distance](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#Distance)
- [HowSimilar](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#HowSimilar) - (alias = Similar)
- [SameSound](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#SameSound)
- [SetDefaultDistanceMethod](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#SetDefaultDistanceMethod)

## Miscellaneous Fuzzy Functions
- [fuzzy_script](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#transliteration) - (alias = script_code)
- [HasCharInSameOrder](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#HasCharInSameOrder) - (alias = HasChr)
- [SameName](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#SameName)

## Miscellaneous Functions
These minimum and maximum functions are included to allow developers to create custom percentage distance in a query.
- [MaxValue](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#MaxValue) - (alias = MaxVal)
- [MaxLength](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#MaxLength) - (alias = MaxLen)
- [MinValue](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#MinValue) - (alias = MinVal)
- [MinLength](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#MinLength) - (alias = MinLen)
- [NormalizeNum](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/Docs#NormalizeNum)

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
- Add additional documentation for each function with examples.
- Try to figureout a way to load the extension to [DB Browser for SQLite]() without having to copy the **FuzzyPlusCSharp.dll** to the same folder as the executable.
- Add an example C# project that uses the C# fuzzy functions with SQLite without having to attach extension.
- Finish implementing API's SameFirstLastName,  SamePhone, SameSocial, SameZip, SameAddress, SameDate, and SameNumber. And add associated documentation.
