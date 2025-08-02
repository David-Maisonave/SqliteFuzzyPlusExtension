SELECT Words, soundex(Words,"to") as sn, MaxLen(Words, "to") as mxL, MinLen(Words, "to") as mnL FROM SimilarSoundingWords WHERE sn = 1;
