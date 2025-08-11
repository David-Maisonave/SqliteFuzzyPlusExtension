select Words as src1, 'being' as src2 
, SameSound(Words, 'being', 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'being', 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'being', 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'being', 'MatchRatingApproach') as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'being', 'Metaphone') as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'being', 'CaverPhonePhonix') as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'being', 'DoubleMetaphone') as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'being', 'ColognePhonetics') as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'being', 'EnPhoneticDistance') as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'being', 'fuzzy_caver') as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'being', 'fuzzy_phonetic') as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'being', 'fuzzy_soundex') as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'being', 'fuzzy_rsoundex') as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
