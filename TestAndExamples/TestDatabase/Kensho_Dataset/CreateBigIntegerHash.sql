-- Creates BigInt hash for all records
UPDATE Items SET HashDescription = FastHash(Description);
-- FastHash Performance:
--		100,000 records in less than a second (610ms)
--		1,000,000 records in less than a 7 second (6472ms)