select Name
-- Misc C++ fuzzy functions
, SameName(Name, "David Jorge") as sn
-- CSharp fuzzy functions
, JaroWin(Name, "David Jorge") as JaroWin, LCStr(Name, "David Jorge") as LCStr, LCSq(Name, "David Jorge") as LCSq
-- Need to fix the following distance functions so that they return a percentage of the difference 
, Lev(Name, "David Jorge") as Lev, DamLev(Name, "David Jorge") as DamLev, PhraseDiff(Name, "David Jorge") as PhraseDiff
-- Need to fix the following distance functions.  They're returning 0.0 on strings that don't match
, OverlapCoef(Name, "David Jorge") as OverlapCoef, Jaccard(Name, "David Jorge") as Jaccard, SorensenDice(Name, "David Jorge") as SorensenDice, Ratcliff(Name, "David Jorge") as Ratcliff, Tanimoto(Name, "David Jorge") as Tanimoto
-- Need to fix the following distance functions.  They're returning 1 instead of zero for a full match
, HammDist(Name, "David Jorge") as HammDist, Jaro(Name, "David Jorge") as Jaro, NormLev(Name, "David Jorge") as NormLev, Lev2(Name, "David Jorge") as Lev2
-- SQLean Fuzzy functions
, hamming(Name, "David Jorge") as ham, dlevenshtein(Name, "David Jorge") as dleve, levenshtein(Name, "David Jorge") as flev
, jaro_winkler(Name, "David Jorge") as fjw, osa_distance(Name, "David Jorge") as fosa, edit_distance(Name, "David Jorge") as edi
FROM SimilarNames