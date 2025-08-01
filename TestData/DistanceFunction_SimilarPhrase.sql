select Phrases
, Lev(Phrases, "This is a similar phrase test") as Lev, DamLev(Phrases, "This is a similar phrase test") as DamLev, JaroWin(Phrases, "This is a similar phrase test") as JaroWin
, PhraseDiff(Phrases, "This is a similar phrase test") as PhraseDiff, Jaccard(Phrases, "This is a similar phrase test") as Jaccard
, LCStr(Phrases, "This is a similar phrase test") as LCStr, LCSq(Phrases, "This is a similar phrase test") as LCSq
-- Need to fix the following distance functions.  They're returning between .33 to .73
, OverlapCoef(Phrases, "This is a similar phrase test") as OverlapCoef, Ratcliff(Phrases, "This is a similar phrase test") as Ratcliff, SorensenDice(Phrases, "This is a similar phrase test") as SorensenDice, Jaro(Phrases, "This is a similar phrase test") as Jaro, Tanimoto(Phrases, "This is a similar phrase test") as Tanimoto
-- Need to fix the following distance functions.  They're returning 1 instead of zero for a full match
, HammDist(Phrases, "This is a similar phrase test") as HammDist, NormLev(Phrases, "This is a similar phrase test") as NormLev, Lev2(Phrases, "This is a similar phrase test") as Lev2
-- SQLean Fuzzy functions
, hamming(Phrases, "This is a similar phrase test") as ham, dlevenshtein(Phrases, "This is a similar phrase test") as dleve, levenshtein(Phrases, "This is a similar phrase test") as flev
, jaro_winkler(Phrases, "This is a similar phrase test") as fjw, osa_distance(Phrases, "This is a similar phrase test") as fosa, edit_distance(Phrases, "This is a similar phrase test") as edi
-- Misc C++ fuzzy functions
, SameName(Phrases, "This is a similar phrase test") as sn
FROM SimilarPhrase