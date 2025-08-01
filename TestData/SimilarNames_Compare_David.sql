select Name
-- Misc C++ fuzzy functions
, SameName(Name, "David") as sn
, JaroWin(Name, "David") as JaroWin, LCStr(Name, "David") as LCStr, LCSq(Name, "David") as LCSq
-- Need to fix the following distance functions so that they return a percentage of the difference 
, Lev(Name, "David") as Lev, DamLev(Name, "David") as DamLev, PhraseDiff(Name, "David") as PhraseDiff
-- Need to fix the following distance functions.  They're returning 0.0 on strings that don't match
, OverlapCoef(Name, "David") as OverlapCoef, Jaccard(Name, "David") as Jaccard, SorensenDice(Name, "David") as SorensenDice, Ratcliff(Name, "David") as Ratcliff, Tanimoto(Name, "David") as Tanimoto
-- Need to fix the following distance functions.  They're returning 1 instead of zero for a full match
, HammDist(Name, "David") as HammDist, Jaro(Name, "David") as Jaro, NormLev(Name, "David") as NormLev, Lev2(Name, "David") as Lev2
-- SQLean Fuzzy functions
, hamming(Name, "David") as ham, dlevenshtein(Name, "David") as dleve, levenshtein(Name, "David") as flev
, jaro_winkler(Name, "David") as fjw, osa_distance(Name, "David") as fosa, edit_distance(Name, "David") as edi
FROM SimilarNames