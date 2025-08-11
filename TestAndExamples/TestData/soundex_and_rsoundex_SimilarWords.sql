select Words
, soundex(Words) as s0
, soundex("David") as s1
, soundex(Words, "David") as s3
, soundex(Words, "David", "Levenshtein") as s4
, soundex(Words, "David", 3) as s5

, rsoundex(Words) as r0
, rsoundex("David") as r1
, rsoundex(Words, "David") as r3
, rsoundex(Words, "David", "Fuzzy_Damlev") as r4
, rsoundex(Words, "David", 1) as r5

FROM SimilarWords