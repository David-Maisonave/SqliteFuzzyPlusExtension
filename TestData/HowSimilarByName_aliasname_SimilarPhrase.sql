select Phrases
, HowSimilar(Phrases, "This is a similar phrase test", "Levenshtein") as lev, HowSimilar(Phrases, "This is a similar phrase test", "DamerauLevenshtein") as dlev
, HowSimilar(Phrases, "This is a similar phrase test", "JaroWinkler") as jw, HowSimilar(Phrases, "This is a similar phrase test", "LongestCommonSequence") as lcs
, HowSimilar(Phrases, "This is a similar phrase test", "JaccardIndex") as jaci, HowSimilar(Phrases, "This is a similar phrase test", "OverlapCoefficient") as ocoef
, HowSimilar(Phrases, "This is a similar phrase test", "NeedlemanWunsch") as n, HowSimilar(Phrases, "This is a similar phrase test", "SorensenDiceDistance") as sd
, HowSimilar(Phrases, "This is a similar phrase test", "RatcliffObershelpSimilarityDistance") as r, HowSimilar(Phrases, "This is a similar phrase test", "HammingDistance") as h
, HowSimilar(Phrases, "This is a similar phrase test", "LongestCommonSubstringDistance") as lcsd, HowSimilar(Phrases, "This is a similar phrase test", "LongestCommonSubsequenceDistance") as lcsq
, HowSimilar(Phrases, "This is a similar phrase test", "JaroDistance") as jd, HowSimilar(Phrases, "This is a similar phrase test", "TanimotoCoefficientDistance") as t
, HowSimilar(Phrases, "This is a similar phrase test", "NormalizedLevenshteinDistance") as nld, HowSimilar(Phrases, "This is a similar phrase test", "Levenshtein2Distance") as lev2
, HowSimilar(Phrases, "This is a similar phrase test", "PhraseTokenize") as pt, HowSimilar(Phrases, "This is a similar phrase test", "SimplePhraseTokenize") as spt
, HowSimilar(Phrases, "This is a similar phrase test", "CosineSimilarity") as cosn, HowSimilar(Phrases, "This is a similar phrase test", "JaccardSimilarity") as Jacs
FROM SimilarPhrase