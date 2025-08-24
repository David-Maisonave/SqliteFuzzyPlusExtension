UPDATE items -- Executes in about 103 seconds (103396ms 1000000 rows)
SET 
 Labels_MD5 = ToHash(Labels, "MD5"), Description_MD5 = ToHash(Description, "MD5")
,Labels_SHA1 = ToHash(Labels, "SHA1"), Description_SHA1 = ToHash(Description, "SHA1")
,Labels_SHA256 = ToHash(Labels, "SHA256"), Description_SHA256 = ToHash(Description, "SHA256")
,Labels_SHA512 = ToHash(Labels, "SHA512"), Description_SHA512 = ToHash(Description, "SHA512")
