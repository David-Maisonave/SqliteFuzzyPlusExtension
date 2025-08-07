select Words
, JaroWin(Words, "David") as JaroWin, LCS(Words, "David") as LCS, LCSq(Words, "David") as LCSq
-- Need to fix the following distance functions so that they return a percentage of the difference 
, Lev(Words, "David") as Lev, DamLev(Words, "David") as DamLev, PhraseDiff(Words, "David") as PhraseDiff
-- Need to fix the following distance functions.  They're returning 0.0 on strings that don't match
, OverlapCoef(Words, "David") as OverlapCoef, Jaccard(Words, "David") as Jaccard, SorensenDice(Words, "David") as SorensenDice, Ratcliff(Words, "David") as Ratcliff, Tanimoto(Words, "David") as Tanimoto
-- Need to fix the following distance functions.  They're returning 1 instead of zero for a full match
, HammDist(Words, "David") as HammDist, Jaro(Words, "David") as Jaro, NormLev(Words, "David") as NormLev, Lev2(Words, "David") as Lev2
-- SQLean Fuzzy functions
, hamming(Words, "David") as ham, dlevenshtein(Words, "David") as dleve, levenshtein(Words, "David") as flev
, jaro_winkler(Words, "David") as fjw, osa_distance(Words, "David") as fosa, edit_distance(Words, "David") as edi
-- Misc C++ fuzzy functions
, SameName(Words, "David") as sn
FROM SimilarWords