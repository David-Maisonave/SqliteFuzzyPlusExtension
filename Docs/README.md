# SqliteFuzzyPlusExtension Documentation

### SqliteFuzzyPlusExtension Main Functions
- [SetDefaultDistanceMethod](#SetDefaultDistanceMethod)
- [HowSimilar](#HowSimilar)
- [Distance](#Distance)

### Fuzzy functions unique to SqliteFuzzyPlusExtension:
- [PhraseSimplifiedDiff](#PhraseSimplifiedDiff)
- [HasCharInSameOrder](#HasCharInSameOrder)
- [SameRSound](#SameRSound)
- [SameSound](#SameSound)
- [iEdlibDistance](#iEdlibDistance)

### Fuzzy functions which don't have an associated Wiki link:
- [TanimotoCoefficientDistance](#TanimotoCoefficientDistance)
- [NormalizeNum](#NormalizeNum)
- [SameName](#SameName)

### Regex functions
- [RegexMatch](#RegexMatch)
- [RegexReplace](#RegexReplace)
- [RegexSearch](#RegexSearch)


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

Functions like SameSound and SameRSound will also use the default distance method if a 3rd argument is passed with a zero value.
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

## SameRSound
``` SQL
SameRSound(str)
```
SameRSound (aka rsoundex) Uses SQLean fuzzy rsoundex to compare to strings, and returns 1 if rsoundex values are equal.
If a 3rd argument is given, the 3rd argument is used to determine what distance method is used to compare the 2 rsoundex values.

For more information see:[fuzzy_rsoundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)

## SameSound
``` SQL
SameSound(str)
```
SameSound (aka soundex) uses SQLean fuzzy soundex to compare to strings, and returns 1 if soundex values are equal.
If a 3rd argument is given, the 3rd argument is used to determine what distance method is used to compare the 2 soundex values.

For more information see: [fuzzy_soundex](https://github.com/nalgeon/sqlean/blob/main/docs/fuzzy.md#phonetic-codes)

## iEdlibDistance
``` SQL
SELECT Phrases, iEdlibDistance(FieldName,'David') t FROM SimilarPhrase WHERE t < 2;
```
iEdlibDistance (aka iEdlib) is a distance case-insensitive function which uses the Edlib library.

For details on edlib, see:
https://github.com/Martinsos/edlib

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
