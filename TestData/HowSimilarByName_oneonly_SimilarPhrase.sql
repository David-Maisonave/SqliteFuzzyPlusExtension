select Phrases
, HowSimilarByName(Phrases, "This is a similar phrase test", "Levenshtein") as lev, HowSimilarByName(Phrases, "This is a similar phrase test", "DamerauLevenshtein") as dlev
, HowSimilarByName(Phrases, "This is a similar phrase test", "JaroWinkler") as jw, HowSimilarByName(Phrases, "This is a similar phrase test", "LongestCommonSequence") as lcs
, HowSimilarByName(Phrases, "This is a similar phrase test", "JaccardIndex") as jaci, HowSimilarByName(Phrases, "This is a similar phrase test", "OverlapCoefficient") as ocoef
, HowSimilarByName(Phrases, "This is a similar phrase test", "NeedlemanWunsch") as n, HowSimilarByName(Phrases, "This is a similar phrase test", "SorensenDiceDistance") as sd
, HowSimilarByName(Phrases, "This is a similar phrase test", "RatcliffObershelpSimilarityDistance") as r, HowSimilarByName(Phrases, "This is a similar phrase test", "HammingDistance") as h
, HowSimilarByName(Phrases, "This is a similar phrase test", "LongestCommonSubstringDistance") as lcsd, HowSimilarByName(Phrases, "This is a similar phrase test", "LongestCommonSubsequenceDistance") as lcsq
, HowSimilarByName(Phrases, "This is a similar phrase test", "JaroDistance") as jd, HowSimilarByName(Phrases, "This is a similar phrase test", "TanimotoCoefficientDistance") as t
, HowSimilarByName(Phrases, "This is a similar phrase test", "NormalizedLevenshteinDistance") as nld, HowSimilarByName(Phrases, "This is a similar phrase test", "Levenshtein2Distance") as lev2
, HowSimilarByName(Phrases, "This is a similar phrase test", "PhraseTokenize") as pt, HowSimilarByName(Phrases, "This is a similar phrase test", "SimplePhraseTokenize") as spt
, HowSimilarByName(Phrases, "This is a similar phrase test", "CosineSimilarity") as cosn, HowSimilarByName(Phrases, "This is a similar phrase test", "JaccardSimilarity") as Jacs
FROM SimilarPhrase