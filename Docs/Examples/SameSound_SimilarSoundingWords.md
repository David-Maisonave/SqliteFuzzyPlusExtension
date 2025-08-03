``` SQL
SELECT Words, SameSound(Words,"pair") sn, "pair" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"too") sn, "too" as comp FROM SimilarSoundingWords WHERE sn = 1
union all
SELECT Words, SameSound(Words,"there") sn, "there" as comp FROM SimilarSoundingWords WHERE sn = 1

```
**Results**:
```
pair	1	pair
pear	1	pair
to	1	too
too	1	too
two	1	too
there	1	there
their	1	there
they're	1	there

```
