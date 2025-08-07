select Words as src1, 'bean' as src2 
, SameSound(Words, 'bean', 0) as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'bean', 1) as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'bean', 2) as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'bean', 3) as a3 -- EnPhoneticDistance (ID# 3)
, SameSound(Words, 'bean', 4) as a4 -- fuzzy_caver (ID# 4)
, SameSound(Words, 'bean', 5) as a5 -- fuzzy_phonetic (ID# 5)
, SameSound(Words, 'bean', 6) as a6 -- fuzzy_soundex (ID# 6)
, SameSound(Words, 'bean', 7) as a7 -- fuzzy_rsoundex (ID# 7)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
