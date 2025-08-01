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
PhraseSimplifiedDiff('The Westside story', 'Westside story, the');
```
PhraseSimplifiedDiff (aka PhraseDiff) gets the phrase difference after the phrases have been simplified.
It returns percentage difference between the number of words different of the simplified strings divided by the maximum quantity of words in the simplified phrase. If one phrase has more words than the other, the division factor of the phrase with the most words is used.

The phrase gets simplified by the following:
Removes abbreviated letters
Removes non-alpha characters
Removes "The" and "A"
Replaces double spaces with a single space

``` SQL
select Phrases, PhraseSimplifiedDiff(Phrases, 'Westside story, the') as p
FROM SimilarPhrase WHERE p < 2
```
Using this project test database, the above query yields the following results:
<img width="215" height="145" alt="PhraseSimplifiedDiff_Example2Results" src="https://github.com/user-attachments/assets/58fa4f7d-e71c-4ecd-87d7-3a47851d5bfd" />


## HasCharInSameOrder
``` SQL
HasCharInSameOrder(str)
```
HasCharInSameOrder


## SameRSound
``` SQL
SameRSound(str)
```
SameRSound



## SameSound
``` SQL
SameSound(str)
```
SameSound



## iEdlibDistance
``` SQL
iEdlibDistance(str)
```
iEdlibDistance


## TanimotoCoefficientDistance
``` SQL
TanimotoCoefficientDistance(str)
```
TanimotoCoefficientDistance



## NormalizeNum
``` SQL
NormalizeNum(str)
```
NormalizeNum



## SameName
``` SQL
SameName(str)
```
SameName



## RegexMatch
``` SQL
RegexMatch(str)
```
RegexMatch



## RegexReplace
``` SQL
RegexReplace(str)
```
RegexReplace



## RegexSearch
``` SQL
RegexSearch(str)
```
RegexSearch

