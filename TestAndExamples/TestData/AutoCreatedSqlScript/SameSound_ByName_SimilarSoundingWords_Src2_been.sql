select Words as src1, 'been' as src2 
, SameSound(Words, 'been', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'been', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'been', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'been', 'EnPhoneticDistance') as a3 -- EnPhoneticDistance (ID# 3)
, SameSound(Words, 'been', 'fuzzy_caver') as a4 -- fuzzy_caver (ID# 4)
, SameSound(Words, 'been', 'fuzzy_phonetic') as a5 -- fuzzy_phonetic (ID# 5)
, SameSound(Words, 'been', 'fuzzy_soundex') as a6 -- fuzzy_soundex (ID# 6)
, SameSound(Words, 'been', 'fuzzy_rsoundex') as a7 -- fuzzy_rsoundex (ID# 7)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
