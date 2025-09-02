SELECT Labels, Description, HowSimilar(Description, 'country in North America') as h 
FROM (SELECT DISTINCT Description, Labels FROM Items INNER JOIN json_each(WordsToJson('country in North America'))  ON Description like '%'|| value || '%') 
WHERE  h  > .85
-- and Description <> 'country in South America' and Description <> 'country in North America' and Description not like 'country in north Africa'