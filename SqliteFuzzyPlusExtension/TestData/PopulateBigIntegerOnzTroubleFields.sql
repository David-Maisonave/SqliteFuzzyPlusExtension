UPDATE "zz Trouble Fields"
SET "Unsigned Big Integer Support" = ToHash("City and State" , 'FastHash')
-- Different ways to support fields with spaces. Do NOT use single quote.
, "Unsigned Big Integer Support2" = ToHash("Some Names" , 'FastHash')
, "Big Integer Support" = ToHash((`Some Names`) , 'FastHash')
, "Big Integer Support 2" = ToHash(`Some Names` , 'FastHash')
, "Big Integer Support 3" = ToHash(("Some Names") , 'FastHash')
