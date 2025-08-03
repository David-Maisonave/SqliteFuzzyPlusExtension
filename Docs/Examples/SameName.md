``` SQL
select Name, SameName(Name, "David") as sn FROM SimilarNames
```
**Results**:
```
David Jorge	1
DavidJorge	1
david jorge	1
davidjorge	1
David E. Jorge	1
David E. Gorge	1
Bob E. Gorge	0
Bob Egor Gorge	0
David Egor Gorge	1
D. Jorge	0
Jorge	0
David	1

```
