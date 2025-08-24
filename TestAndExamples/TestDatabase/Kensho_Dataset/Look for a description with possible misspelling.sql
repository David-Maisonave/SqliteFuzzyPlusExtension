Select labels, description,HasCharInSameOrder("country in North America", 2) as h, HowSimilar(description, "country in North America") as S 
FROM items WHERE 
(description like "%country %" or description like "% North %" or description like "% America%") AND  
description like h AND
S > 0.90 and description NOT like "%country in North America%" ORDER BY S;
