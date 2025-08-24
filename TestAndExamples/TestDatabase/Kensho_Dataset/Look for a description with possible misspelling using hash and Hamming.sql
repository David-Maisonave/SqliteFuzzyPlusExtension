-- Look for a description with possible misspelling using hash and Hamming
Select labels, description, HowSimilar(Description_MD5, "6a3e188d4a80d2c66aba7bf0b058298a", 4) as S FROM items WHERE description like "%n North America%"

--Select labels, description, HowSimilar(Description_MD5, "6a3e188d4a80d2c66aba7bf0b058298a", 4) as S FROM items WHERE S > 0.75 
-- and description NOT like "%country in North America%" ORDER BY S;