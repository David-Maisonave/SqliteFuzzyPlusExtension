select Words
, HowSimilar(Words, "David", "Levenshtein") as lev, HowSimilar(Words, "David", "DamerauLevenshtein") as dlev, HowSimilar(Words, "David", "LongestCommonSequence") as lcs, HowSimilar(Words, "David", "NeedlemanWunsch") as n
, HowSimilar(Words, "David", "JaroWinkler") as jw
, HowSimilar(Words, "David", "JaccardIndex") as jaci, HowSimilar(Words, "David", "OverlapCoefficient") as ocoef
, HowSimilar(Words, "David", "SorensenDiceDistance") as sd
, HowSimilar(Words, "David", "RatcliffObershelpSimilarityDistance") as r
, HowSimilar(Words, "David", "LongestCommonSubstringDistance") as lcsd, HowSimilar(Words, "David", "LongestCommonSubsequenceDistance") as lcsq
, HowSimilar(Words, "David", "Levenshtein2Distance") as lev2, HowSimilar(Words, "David", "TanimotoCoefficientDistance") as t
, HowSimilar(Words, "David", "PhraseTokenize") as pt, HowSimilar(Words, "David", "SimplePhraseTokenize") as spt
, HowSimilar(Words, "David", "CosineSimilarity") as cosn, HowSimilar(Words, "David", "JaccardSimilarity") as Jacs
-- The following distance functions return .80 on a match.
, HowSimilar(Words, "David", "NormalizedLevenshteinDistance") as nld
, HowSimilar(Words, "David", "JaroDistance") as jd, HowSimilar(Words, "David", "HammingDistance") as h -- These two return 1 on a full fail match

FROM SimilarWords