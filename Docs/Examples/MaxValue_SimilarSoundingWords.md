``` SQL
SELECT Words, soundex(Words,"to") as sn, MaxValue(length(Words), length("to")) as L FROM SimilarSoundingWords WHERE sn = 1
```
**Results**:
```
to	1	2
too	1	3
two	1	3

```
