select Source1 as src1, Source2 as src2 
, SameSound(Source1, Source2, 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Source1, Source2, 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Source1, Source2, 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Source1, Source2, 'EnPhoneticDistance') as a3 -- EnPhoneticDistance (ID# 3)
, SameSound(Source1, Source2, 'fuzzy_caver') as a4 -- fuzzy_caver (ID# 4)
, SameSound(Source1, Source2, 'fuzzy_phonetic') as a5 -- fuzzy_phonetic (ID# 5)
, SameSound(Source1, Source2, 'fuzzy_soundex') as a6 -- fuzzy_soundex (ID# 6)
, SameSound(Source1, Source2, 'fuzzy_rsoundex') as a7 -- fuzzy_rsoundex (ID# 7)
FROM SimilarSoundingWords1To1_NoMatch;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
