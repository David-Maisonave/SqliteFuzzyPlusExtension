``` SQL
SELECT Phrases, HasChr("similar phrase test") h FROM SimilarPhrase 
where Phrases like h
```
**Results**:
```
This is similar phrases tests	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%
This is similar phrase tests	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%
This is similar phrase test	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%
This is similar phrase tested	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%
This is a similar phrase test	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%
That is a similar phrase test	%s%i%m%i%l%a%r% %p%h%r%a%s%e% %t%e%s%t%

```
