select Words
-- sqlean fuzzy functions
, HowSimilarByName(Words, "David", "EditDistance") as eed,EditDistance(Words, "David") as ced
, HowSimilarByName(Words, "David", "fuzzy_damlev") as fd, HowSimilarByName(Words, "David", "fuzzy_hamming") as fh
, HowSimilarByName(Words, "David", "fuzzy_jarowin") as fj, HowSimilarByName(Words, "David", "fuzzy_leven") as fl
, HowSimilarByName(Words, "David", "fuzzy_osadist") as fo, HowSimilarByName(Words, "David", "fuzzy_editdist") as fe
,fuzzy_damlev(Words, "David") as ffd, fuzzy_hamming(Words, "David") as ffh, fuzzy_jarowin(Words, "David") as ffj
,fuzzy_leven(Words, "David") as ffl, fuzzy_osadist(Words, "David") as ffo, fuzzy_editdist(Words, "David") as ffe
-- CSharp fuzzy functions
, HowSimilarByName(Words, "David", "Levenshtein") as lev, HowSimilarByName(Words, "David", "DamerauLevenshtein") as dlev
, HowSimilarByName(Words, "David", "JaroWinkler") as jw, HowSimilarByName(Words, "David", "CosineSimilarity") as cosn
, HowSimilarByName(Words, "David", "LongestCommonSequence") as lcs, HowSimilarByName(Words, "David", "JaccardSimilarity") as Jacs
, HowSimilarByName(Words, "David", "JaccardIndex") as jaci, HowSimilarByName(Words, "David", "OverlapCoefficient") as ocoef
, HowSimilarByName(Words, "David", "NeedlemanWunsch") as n, HowSimilarByName(Words, "David", "SorensenDiceDistance") as sd
, HowSimilarByName(Words, "David", "RatcliffObershelpSimilarityDistance") as r, HowSimilarByName(Words, "David", "HammingDistance") as h
, HowSimilarByName(Words, "David", "LongestCommonSubstringDistance") as lcsd, HowSimilarByName(Words, "David", "LongestCommonSubsequenceDistance") as lcsq
, HowSimilarByName(Words, "David", "JaroDistance") as jd, HowSimilarByName(Words, "David", "NormalizedLevenshteinDistance") as nld
, HowSimilarByName(Words, "David", "Levenshtein2Distance") as lev2, HowSimilarByName(Words, "David", "TanimotoCoefficientDistance") as t
, HowSimilarByName(Words, "David", "PhraseTokenize") as pt, HowSimilarByName(Words, "David", "SimplePhraseTokenize") as spt
FROM SimilarWords