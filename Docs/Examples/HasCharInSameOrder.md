``` SQL
SELECT Words, HasCharInSameOrder("david") FROM SimilarWords 
where Words like HasCharInSameOrder("david")
```
**Results**:
```
David	%d%a%v%i%d%
david	%d%a%v%i%d%
Dav id	%d%a%v%i%d%
Da.v.id	%d%a%v%i%d%
D-avid	%d%a%v%i%d%

```
