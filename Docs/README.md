# SqliteFuzzyPlusExtension Documentation

### SqliteFuzzyPlusExtension Main Functions
- [DistanceMethod Parameter](#DistanceMethod)
- [SetDefaultDistanceMethod](#SetDefaultDistanceMethod)
- [HowSimilar](#HowSimilar)
- [Distance](#Distance)

### Fuzzy functions unique to SqliteFuzzyPlusExtension:
- [PhraseSimplifiedDiff](#PhraseSimplifiedDiff)
- [HasCharInSameOrder](#HasCharInSameOrder)
- [SameSound](#SameSound)
- [iEdlibDistance](#iEdlibDistance)

### Fuzzy functions which don't have an associated Wiki link:
- [TanimotoCoefficientDistance](#TanimotoCoefficientDistance)
- [NormalizeNum](#NormalizeNum)
- [SameName](#SameName)
- [CaverPhone2](#CaverPhone2)
- [Soundex2](#Soundex2)

### Regex functions
- [RegexMatch](#RegexMatch)
- [RegexReplace](#RegexReplace)
- [RegexSearch](#RegexSearch)

### Miscellaneous functions
- [MaxValue](#MaxValue)
- [MaxLength](#MaxLength)
- [MinValue](#MinValue)
- [MinLength](#MinLength)

## DistanceMethod
Multiple functions have DistanceMethod as an optional or as a required parameter. The argument can be in the form of a string or as a number.
- If performance is a key factor, use a number instead of a string name.
- If readablity is more important, use the string name.
#### The following is the list of names and associated ID number.
- UseDefaultDistanceMethod = 0 
- Levenshtein = 1
- DamerauLevenshtein = 2
- JaroWinkler = 3
- LongestCommonSequence = 4
- JaccardIndex = 5
- OverlapCoefficient = 6
- NeedlemanWunsch = 7
- SorensenDiceDistance = 8
- RatcliffObershelpSimilarityDistance = 9
- HammingDistance = 10
- LongestCommonSubstringDistance = 11
- LongestCommonSubsequenceDistance = 12
- JaroDistance = 13
- NormalizedLevenshteinDistance = 14
- Levenshtein2Distance = 15
- TanimotoCoefficientDistance = 16
- EditDistance = 17
- CosineSimilarity = 18
- JaccardSimilarity = 19
- PhraseTokenize = 20
- SimplePhraseTokenize = 21
- Fuzzy_Damlev = 64 (CPP_ONLY_FUZZY)
- Fuzzy_Hamming = 65
- Fuzzy_Jarowin = 66
- Fuzzy_Leven = 67
- Fuzzy_Osadist = 68
- Fuzzy_Editdist = 69
- Fuzzy_Jaro = 70
- SameSound_StrCmp = 71
- EdlibDistance = 72
- iLevenshtein = 129 (CASE_INSENSITIVE + Levenshtein)
- iDamerauLevenshtein = 130
- iJaroWinkler = 131
- iLongestCommonSequence = 132
- iJaccardIndex = 133
- iOverlapCoefficient = 134
- iNeedlemanWunsch = 135
- iSorensenDiceDistance = 136
- iRatcliffObershelpSimilarityDistance = 137
- iHammingDistance = 138
- iLongestCommonSubstringDistance = 139
- iLongestCommonSubsequenceDistance = 140
- iJaroDistance = 141
- iNormalizedLevenshteinDistance = 142
- iLevenshtein2Distance = 143
- iTanimotoCoefficientDistance = 144
- iEditDistance = 145
- iCosineSimilarity = 146
- iJaccardSimilarity = 147
- iEdlibDistance = 200 (CASE_INSENSITIVE + EdlibDistance)

## SetDefaultDistanceMethod
``` SQL
SetDefaultDistanceMethod('Levenshtein');
```
Call this function to set the default distance method used when calling HowSimilar or Distance without including a 3rd parameter which specifies the distance method.

The parameter can be either a string or a number.
As a string, it's the name of the distance method. The distance name is case-insensitive.
As a number, it's the ID of the distance method.

On startup, the default distance method is DamerauLevenshteinDistance.
When HowSimilar and Distance are called only using 2 argumenets, the default distance method is used.
The default distance method is also used if these functions are called with the 3rd argument equal to zero.

Functions like soundex and rsoundex will also use the default distance method if a 3rd argument is passed with a zero value.
#### Example#1 Set to build-in default method:
``` SQL
SetDefaultDistanceMethod(0);
```

## HowSimilar
``` SQL
select Name, HowSimilar(Name, "David Jorge") as s FROM SimilarNames where s > .9;
```
HowSimilar (aka Similar) tries to return a percentage representing how similar are two variables. The return value is in a range of 1 to 0.
1=(100% match)
0=(Does not match at all)
.9=90% match
.8123=80.23% match
.561=56.1% match
.11=11% match

Most of the distance method return above expected results depending on the data, but some return poor results.
Fuzzy_Editdist = Extreemly poor results. Should NOT be used with HowSimilar. Use EditDistance instead, which gives expected results. Fuzzy_Editdist is part of SQLean library, where as EditDistance is part of the CSharp fuzzy function library.

As of the time of this writing, the following functions return 80% (.83) instead of 100% (1) for values that are equal. Moreover both HammingDistance and JaroDistance return 100% (1) for values that do not match at all. This make get fixed in the future.
HammingDistance
JaroDistance
NormalizedLevenshteinDistance

FYI:
The main diffence between Distance API and HowSimilar (aka Similar), is that HowSimilar attempts to return a percentage result for all distance methods.
Where-as the Distance function makes no such attempt.

## Distance
``` SQL
select Name, Distance(Name, "David Jorge") as d FROM SimilarNames WHERE d < 2;
```
Returns the raw results of a distance method.
Gives the same results as calling the distance method directly.
This function has two main purposes.
1. Have a standard alias to use to call a distance function. This allows the code to stay the same, with only making one change where SetDefaultDistanceMethod is called.
2. It can be used for testing purposes to allow developers to see which distance function is best to use for a particular set of data. For a test example, see  HowSimilar_bynumber_SimilarWords.sql

FYI:
The main diffence between Distance API and HowSimilar (aka Similar), is that HowSimilar attempts to return a percentage result for all distance methods.
Where-as the Distance function makes no such attempt.

## PhraseSimplifiedDiff
``` SQL
SELECT Phrase FROM MyTable WHERE PhraseSimplifiedDiff('The Westside story', 'Westside story, the') < 2;
```
PhraseSimplifiedDiff (aka PhraseDiff) gets the phrase difference after the phrases have been simplified.
It returns number of words different of the simplified strings.

The phrase gets simplified by the following:
Removes abbreviated letters
Removes non-alpha characters
Removes "The" and "A"
Replaces double spaces with a single space

``` SQL
select Phrases, PhraseDiff(Phrases, 'Westside story, the') as p
FROM SimilarPhrase WHERE p < 2
```
**Results**:
<img width="215" height="145" alt="PhraseSimplifiedDiff_Example2Results" src="https://github.com/user-attachments/assets/58fa4f7d-e71c-4ecd-87d7-3a47851d5bfd" />

## HasCharInSameOrder
``` SQL
SELECT Words FROM SimilarWords WHERE Words like HasCharInSameOrder("david");
```
HasCharInSameOrder (aka HasChr).
Use this function on a WHERE clause to find a string that contains all the characters of the input string and in the same order.

#### Example#1:
``` SQL
SELECT Words FROM SimilarWords WHERE Words like HasChr("david");
```
**Results**:
```
david
Davide
D av id
D-avi-d
```

Match FAILS:
```
Davdi
Dave
Dovid
Divad
Dadiv
Daves
```

#### Example#2:
``` SQL
SELECT Phrases, HasChr("similar phrase test") h FROM SimilarPhrase 
WHERE Phrases like h
```
**Results**:
```
This is similar as a phrase test
This is similar phrases tests
That similar fuzzy phrase tested
```

Match FAILS:
```
phrase similar test
That is similar phrase
test similar phrase
```

For more information see:[fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)

## SameSound
``` SQL
SELECT Word, SameSound(Word,"there") sn FROM SimilarSoundingWords;
```
SameSound compares 2 strings, and returns 1 if the sound is similar.
- If a 3rd argument is given, the 3rd argument is used to determine what phonetic method is used to compare the 2 strings. By default Soundex is used to compare the 2 input strings.
  - Allowed 3rd parameter values:
    - "Soundex"
    - "Caverphone2"
    - "fuzzy_caver"
    - "fuzzy_phonetic"
    - "fuzzy_soundex"
    - "fuzzy_rsoundex"
    - "fuzzy_translit"
    - 1
    - 2
    - 3
    - 4
    - 5
    - 6
    - 7
  - Note: The number values are ID values of the string listed values. (1="Soundex", 2="Caverphone2", etc...)
- If a 4th argument is given, the 4th argument is used to determine what distance method is used to compare the 2 phonetic values. By default, strcmp is used to determine if the phonetic values are equal.
  - See [DistanceMethod](#DistanceMethod) for allowed values.
- If a 5TH argument is present, the 5th argument is used to determine if the distance method should return IsVerySimilar or IsSimilar.  If the 5TH argument is 1, the function returns IsVerySimilar results. If the 5TH argument is 0, a IsSimilar result is returned. The 5th argument is only applicable if the 4th argument specifies a distance method other than "SameSound_StrCmp".


#### Example#1:
``` SQL
SELECT Word, SameSound(Word,"there") sn FROM SimilarSoundingWords WHERE sn = 1;
```
**Results**:
```
there	1
their	1
they're	1
```

#### Example#2:
``` SQL
SELECT Words, SameSound(Words,"pair") sn, "pair" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"too") sn, "too" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"there") sn, "there" as comp FROM SimilarSoundingWords WHERE sn = 1;```
**Results**:
```
pair	1	pair
pear	1	pair
to	1	too
too	1	too
two	1	too
there	1	there
their	1	there
they're	1	there
```


For more information see: [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)

## iEdlibDistance
``` SQL
SELECT Phrases, iEdlibDistance(FieldName,'David') t FROM SimilarPhrase WHERE t < 2;
```
iEdlibDistance (aka iEdlib) is a distance case-insensitive function which uses the Edlib library.

For details on edlib, see:
https://github.com/Martinsos/edlib

## MaxValue 
``` SQL
SELECT Word, soundex(Word,"to") as sn, MaxValue(length(Word), length("to")) as L FROM SimilarSoundingWords WHERE sn = 1;
```
Returns the value that is the highest of the two input arguments.

## MaxLength 
``` SQL
SELECT Word, soundex(Word,"to") as sn, MaxLength(Word, "to") as L FROM SimilarSoundingWords WHERE sn = 1;
```
Returns the value that is the longest length of the two input arguments.


## MinValue 
``` SQL
SELECT Word, soundex(Word,"to") as sn, MinValue(length(Word), length("to")) as L FROM SimilarSoundingWords WHERE sn = 1;
```
Returns the value that is the minimum of the two input arguments.

## MinLength 
``` SQL
SELECT Word, soundex(Word,"to") as sn, MinLength(Word, "to") as L FROM SimilarSoundingWords WHERE sn = 1;
```
Returns the value that is the shortest length of the two input arguments.

## TanimotoCoefficientDistance
``` SQL

SELECT Phrases, TanimotoCoefficientDistance(FieldName,'David') t FROM SimilarPhrase WHERE t < 2;
```
TanimotoCoefficientDistance (aka Tanimoto) also known as the Jaccard index, is a measure of similarity between two sets or vectors, often used to quantify the overlap between them. It's frequently applied to binary vectors or in cheminformatics to compare molecular fingerprints. The Tanimoto Distance, derived from the Tanimoto Coefficient, quantifies the dissimilarity between these sets or vectors, where a higher distance indicates less similarity.




## NormalizeNum
``` SQL
SELECT StrNum, NormalizeNum('123.4K') as n FROM MyTable where n = '123400';
```
Converts human-friendly compact numbers to full 64-bit integers, e.g., `"100.2K"` into `100200`

This function comes from the library in the following link: [sqlite-functions](https://github.com/brandonrobertz/sqlite-functions)

## SameName
``` SQL
select Name, SameName(Name, "David") as sn FROM SimilarNames;
```
A function that returns true if two names are determined to be the same despite different formats (e.g., "last, first mid" vs. "first mid last").
**Results**:
```
David Jorge	1
DavidJorge	1
david jorge	1
davidjorge	1
David E. Jorge	1
David E. Gorge	1
Bob E. Gorge	0
Bob Egor Gorge	0
David Egor Gorge	1
D. Jorge	0
Jorge	0
David	1
```

This function comes from the library in the following link: [sqlite-functions](https://github.com/brandonrobertz/sqlite-functions)

## CaverPhone2
``` SQL
select CaverPhone2('ate','eight');
```
CaverPhone2 (aka CaverPhone_CS) calculates the Caverphone code. It takes two arguments comnpare to the SQLean CaverPhone, which only take one argument.
Example usage:
``` SQL
SELECT Word, CaverPhone2(Word,"ate") cp FROM SimilarSoundingWords WHERE cp = 1;
```
**Results**:
```
ate	1
eight	1
```

Here's example usage for SQLean CaverPhone.
``` SQL
SELECT Word, CaverPhone(Word) cp FROM SimilarSoundingWords WHERE cp = CaverPhone("ate");;
```

They both give the same results, but IMHO the CaverPhone2 syntax is easier and more efficient to use.

## Soundex2
``` SQL
select Soundex2('too','two');
```
Soundex2 calculates the Soundex code. It takes two arguments.

## RegexMatch
``` SQL
select Words, RegexMatch(Words, 'Dav[a-z][a-z]') FROM SimilarWords;
```
RegexMatch (aka XMatch) searches for the first occurrence of the regular expression pattern within the input string and returns 1 if a match is found, and 0 if no match.

#### Example#1:
``` SQL
select Words, RegexMatch(Words, 'Dav[a-z][a-z]') as r
FROM SimilarWords  WHERE r = TRUE;
```
**Results**:
```
David
Davdi
david
Daves
```

Match FAILS:
```
Dovid
Dave
Divad
```
#### Example#2:
``` SQL
select Words, RegexMatch(Words, 'D[a-z]vid') as r
FROM SimilarWords  WHERE r = 1;
```
**Results**:
```
David
david
Dovid
```

Match FAILS:
```
Daves
Davdi
Divad
```

## RegexReplace
``` SQL
select Words, RegexReplace(Words, '([Dd]av)[ei][d]?', '$1id') as r FROM SimilarWords;
```
Searches for the first occurrence of the regular expression pattern within the input string and replaces the match with replacement string.
If match found, it returns the string with replacement change.
Otherwise it returns original string.

Takes 3 arguments.
source	= original string
pattern = regex pattern to search for
replacement = replacement string which can contain parameter numbers ($1, $2)

#### Example#1:
``` SQL
select Words, RegexReplace(Words, '([Dd]av)[ei][d]?', '$1id') as r
FROM SimilarWords  WHERE r like 'David';
```
**Results**:
```
David	David
Dave	David
david	david
```

## RegexSearch
``` SQL
select Words, RegexSearch(Words, 'D[a-z]vid') FROM SimilarWords;
```
Searches for the first occurrence of the regular expression pattern within the input string and returns the match if found. Otherwise returns empty string.
#### Example#1:
``` SQL
select Words, RegexSearch(Words, 'D[a-z]vid') as r
FROM SimilarWords  WHERE r <> '';
```
**Results**:
```
David	David
david	david
Dovid	Dovid
```
