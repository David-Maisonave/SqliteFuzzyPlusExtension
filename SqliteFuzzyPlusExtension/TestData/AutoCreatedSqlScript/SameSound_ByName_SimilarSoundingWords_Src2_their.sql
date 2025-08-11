select Words as src1, 'their' as src2 
, SameSound(Words, 'their', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'their', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'their', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'their', 'MatchRatingApproach') as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'their', 'Metaphone') as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'their', 'CaverPhonePhonix') as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'their', 'DoubleMetaphone') as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'their', 'ColognePhonetics') as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'their', 'EnPhoneticDistance') as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'their', 'fuzzy_caver') as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'their', 'fuzzy_phonetic') as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'their', 'fuzzy_soundex') as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'their', 'fuzzy_rsoundex') as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
