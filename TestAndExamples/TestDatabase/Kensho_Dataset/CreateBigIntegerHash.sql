-- Creates Big Integer hash for 100,000 records in less than a second (610ms)
UPDATE Items SET HashDescription = FastHash(Description);