select Words
, soundex(Words) as s0
, rsoundex(Words) as r0
, SameSound(Words, "too") as s1
, SameSound(Words, "too", "fuzzy_soundex") as s2
, SameSound(Words, "too", "fuzzy_phonetic") as s3
, SameSound(Words, "too", "fuzzy_rsoundex") as s4
, SameSound(Words, "too", "fuzzy_soundex", "Levenshtein") as s5
, SameSound(Words, "too", "fuzzy_phonetic", "Levenshtein") as s6
, SameSound(Words, "too", "fuzzy_rsoundex", "Levenshtein") as s7
, SameSound(Words, "too", "fuzzy_soundex", "DamerauLevenshtein") as s8
, SameSound(Words, "too", "fuzzy_phonetic", "JaroWinkler") as s9

, SameSound(Words, "too", "fuzzy_soundex", "Levenshtein", 0) as ss5
, SameSound(Words, "too", "fuzzy_phonetic", "Levenshtein", FALSE) as ss6
, SameSound(Words, "too", "fuzzy_rsoundex", "Levenshtein", FALSE) as ss7
, SameSound(Words, "too", "fuzzy_soundex", "DamerauLevenshtein", 0) as ss8
, SameSound(Words, "too", "fuzzy_phonetic", "JaroWinkler", 0) as ss9

FROM SimilarSoundingWords