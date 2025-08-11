select Words as src1, 'been' as src2 
, SameSound(Words, 'been', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'been', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'been', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'been', 'MatchRatingApproach') as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'been', 'Metaphone') as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'been', 'CaverPhonePhonix') as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'been', 'DoubleMetaphone') as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'been', 'ColognePhonetics') as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'been', 'EnPhoneticDistance') as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'been', 'fuzzy_caver') as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'been', 'fuzzy_phonetic') as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'been', 'fuzzy_soundex') as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'been', 'fuzzy_rsoundex') as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
