``` SQL
select Words
, soundex(Words) as s0
, rsoundex(Words) as r0
, SameSound(Words, "too") as s1
, SameSound(Words, "too", "fuzzy_soundex") as s2
, SameSound(Words, "too", "fuzzy_phonetic") as s3
, SameSound(Words, "too", "fuzzy_rsoundex") as s4
, SameSound(Words, "too", "fuzzy_soundex", "Levenshtein") as s5
, SameSound(Words, "too", "fuzzy_phonetic", "Levenshtein") as s6
, SameSound(Words, "too", "fuzzy_rsoundex", "Levenshtein") as s7
, SameSound(Words, "too", "fuzzy_soundex", "DamerauLevenshtein") as s8
, SameSound(Words, "too", "fuzzy_phonetic", "JaroWinkler") as s9

, SameSound(Words, "too", "fuzzy_soundex", "Levenshtein", 0) as ss5
, SameSound(Words, "too", "fuzzy_phonetic", "Levenshtein", FALSE) as ss6
, SameSound(Words, "too", "fuzzy_rsoundex", "Levenshtein", FALSE) as ss7
, SameSound(Words, "too", "fuzzy_soundex", "DamerauLevenshtein", 0) as ss8
, SameSound(Words, "too", "fuzzy_phonetic", "JaroWinkler", 0) as ss9

FROM SimilarSoundingWords
```
**Results**:
```
there	T600	T6090	0	0	0	0	0	0	0	0	0	1	0	0	1	1
their	T600	T609	0	0	0	0	0	0	0	0	0	1	0	1	1	1
they're	T600	T6090	0	0	0	0	0	0	0	0	0	1	0	0	1	1
to	T000	T60	1	1	1	1	1	1	1	1	1	1	1	1	1	1
too	T000	T60	1	1	1	1	1	1	1	1	1	1	1	1	1	1
two	T000	T60	1	1	0	1	1	0	1	1	0	1	0	1	1	1
pair	P600	P109	0	0	0	0	0	0	0	0	0	0	0	0	0	0
pear	P600	P109	0	0	0	0	0	0	0	0	0	0	0	0	0	0
see	S000	S30	0	0	0	0	0	0	0	0	0	1	0	0	1	1
sea	S000	S30	0	0	0	0	0	0	0	0	0	1	0	0	1	1
here	H600	H090	0	0	0	0	0	0	0	0	0	0	0	0	0	0
hear	H600	H09	0	0	0	0	0	0	0	0	0	0	0	0	0	0
ate	A300	A060	0	0	0	0	0	0	0	0	0	0	0	0	0	0
eight	E230	E0406	0	0	0	0	0	0	0	0	0	0	0	0	0	0
top	T100	T601	0	0	0	0	0	0	0	0	1	1	0	1	1	1
tool	T400	T607	0	0	0	0	0	0	0	0	0	1	0	1	1	1
cool	C400	C307	0	0	0	0	0	0	0	0	0	0	0	0	0	0

```
