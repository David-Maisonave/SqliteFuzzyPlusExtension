select Phrases
, HowSimilar(Phrases, "This is a similar phrase test", 1) as d1, HowSimilar(Phrases, "This is a similar phrase test", 11) as d11
, HowSimilar(Phrases, "This is a similar phrase test", 2) as d2, HowSimilar(Phrases, "This is a similar phrase test", 12) as d12
, HowSimilar(Phrases, "This is a similar phrase test", 3) as d3, HowSimilar(Phrases, "This is a similar phrase test", 13) as d13
, HowSimilar(Phrases, "This is a similar phrase test", 4) as d4, HowSimilar(Phrases, "This is a similar phrase test", 14) as d14
, HowSimilar(Phrases, "This is a similar phrase test", 5) as d5, HowSimilar(Phrases, "This is a similar phrase test", 15) as d15
, HowSimilar(Phrases, "This is a similar phrase test", 6) as d6, HowSimilar(Phrases, "This is a similar phrase test", 16) as d16
, HowSimilar(Phrases, "This is a similar phrase test", 7) as d7, HowSimilar(Phrases, "This is a similar phrase test", 17) as d17
, HowSimilar(Phrases, "This is a similar phrase test", 8) as d8, HowSimilar(Phrases, "This is a similar phrase test", 18) as d18
, HowSimilar(Phrases, "This is a similar phrase test", 9) as d9, HowSimilar(Phrases, "This is a similar phrase test", 19) as d19
, HowSimilar(Phrases, "This is a similar phrase test", 10) as d10, HowSimilar(Phrases, "This is a similar phrase test", 20) as d20
FROM SimilarPhrase