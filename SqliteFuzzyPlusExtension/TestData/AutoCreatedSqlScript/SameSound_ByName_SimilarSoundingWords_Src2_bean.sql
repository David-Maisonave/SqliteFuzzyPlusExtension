select Words as src1, 'bean' as src2 
, SameSound(Words, 'bean', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'bean', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'bean', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'bean', 'MatchRatingApproach') as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'bean', 'Metaphone') as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'bean', 'CaverPhonePhonix') as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'bean', 'DoubleMetaphone') as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'bean', 'ColognePhonetics') as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'bean', 'EnPhoneticDistance') as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'bean', 'fuzzy_caver') as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'bean', 'fuzzy_phonetic') as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'bean', 'fuzzy_soundex') as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'bean', 'fuzzy_rsoundex') as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
