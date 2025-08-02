SELECT Word, soundex(Word,"to") as sn, MaxLen(Word, "to") as mxL, MinLen(Word, "to") as mnL FROM SimilarSoundingWords WHERE sn = 1;
