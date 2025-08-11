select Phrases
, HowSimilarByName(Phrases, "This is a similar phrase test", "NormalizedLevenshteinDistance") as nld
, HowSimilarByName(Phrases, "This is a similar phrase test", "Levenshtein2Distance") as lev2
FROM SimilarPhrase