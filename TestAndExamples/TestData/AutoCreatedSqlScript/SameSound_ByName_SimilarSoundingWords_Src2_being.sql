select Words as src1, 'being' as src2 
, SameSound(Words, 'being', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'being', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'being', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'being', 'EnPhoneticDistance') as a3 -- EnPhoneticDistance (ID# 3)
, SameSound(Words, 'being', 'fuzzy_caver') as a4 -- fuzzy_caver (ID# 4)
, SameSound(Words, 'being', 'fuzzy_phonetic') as a5 -- fuzzy_phonetic (ID# 5)
, SameSound(Words, 'being', 'fuzzy_soundex') as a6 -- fuzzy_soundex (ID# 6)
, SameSound(Words, 'being', 'fuzzy_rsoundex') as a7 -- fuzzy_rsoundex (ID# 7)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
