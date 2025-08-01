select Name
, HowSimilar(Name, "David Jorge", "Levenshtein") as lev, HowSimilar(Name, "David Jorge", "DamerauLevenshtein") as dlev, HowSimilar(Name, "David Jorge", "LongestCommonSequence") as lcs, HowSimilar(Name, "David Jorge", "NeedlemanWunsch") as n
, HowSimilar(Name, "David Jorge", "JaroWinkler") as jw
, HowSimilar(Name, "David Jorge", "JaccardIndex") as jaci, HowSimilar(Name, "David Jorge", "OverlapCoefficient") as ocoef
, HowSimilar(Name, "David Jorge", "SorensenDiceDistance") as sd
, HowSimilar(Name, "David Jorge", "RatcliffObershelpSimilarityDistance") as r
, HowSimilar(Name, "David Jorge", "LongestCommonSubstringDistance") as lcsd, HowSimilar(Name, "David Jorge", "LongestCommonSubsequenceDistance") as lcsq
, HowSimilar(Name, "David Jorge", "Levenshtein2Distance") as lev2, HowSimilar(Name, "David Jorge", "TanimotoCoefficientDistance") as t
, HowSimilar(Name, "David Jorge", "PhraseTokenize") as pt, HowSimilar(Name, "David Jorge", "SimplePhraseTokenize") as spt
, HowSimilar(Name, "David Jorge", "CosineSimilarity") as cosn, HowSimilar(Name, "David Jorge", "JaccardSimilarity") as Jacs
-- The following distance functions return .80 on a match.
, HowSimilar(Name, "David Jorge", "NormalizedLevenshteinDistance") as nld
, HowSimilar(Name, "David Jorge", "JaroDistance") as jd, HowSimilar(Name, "David", "HammingDistance") as h -- These two return 1 on a full fail match

FROM SimilarNames