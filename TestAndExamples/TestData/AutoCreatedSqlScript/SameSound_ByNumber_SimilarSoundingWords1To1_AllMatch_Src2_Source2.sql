select Source1 as src1, Source2 as src2 
, SameSound(Source1, Source2, 0) as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Source1, Source2, 1) as a1 -- Soundex2 (ID# 1)
, SameSound(Source1, Source2, 2) as a2 -- Caverphone2 (ID# 2)
, SameSound(Source1, Source2, 3) as a3 -- EnPhoneticDistance (ID# 3)
, SameSound(Source1, Source2, 4) as a4 -- fuzzy_caver (ID# 4)
, SameSound(Source1, Source2, 5) as a5 -- fuzzy_phonetic (ID# 5)
, SameSound(Source1, Source2, 6) as a6 -- fuzzy_soundex (ID# 6)
, SameSound(Source1, Source2, 7) as a7 -- fuzzy_rsoundex (ID# 7)
FROM SimilarSoundingWords1To1_AllMatch;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
