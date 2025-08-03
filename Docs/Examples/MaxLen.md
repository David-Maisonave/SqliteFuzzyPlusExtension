``` SQL
SELECT Words, soundex(Words,"to") as sn, MaxLen(Words, "to") as mxL, MinLen(Words, "to") as mnL FROM SimilarSoundingWords WHERE sn = 1;

```
**Results**:
```
to	1	2	2
too	1	3	2
two	1	3	2

```
