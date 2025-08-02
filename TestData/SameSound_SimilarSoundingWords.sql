SELECT Words, SameSound(Words,"pair") sn, "pair" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"too") sn, "too" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"there") sn, "there" as comp FROM SimilarSoundingWords WHERE sn = 1

