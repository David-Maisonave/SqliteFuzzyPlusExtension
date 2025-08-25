Select labels, Description, HowSimilar(description, "country in North America") as S 
FROM items WHERE 
-- SQLite3_trace() 
-- (description like "%country %" or description like "% North %" or description like "% America%") AND  
HasWordFrom("country in North America", 'Description') AND
S > 0.90  ORDER BY S;
