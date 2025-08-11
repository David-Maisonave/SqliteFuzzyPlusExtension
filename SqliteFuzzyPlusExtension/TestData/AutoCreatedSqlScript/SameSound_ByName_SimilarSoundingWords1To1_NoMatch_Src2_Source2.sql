select Source1 as src1, Source2 as src2 
, SameSound(Source1, Source2, 'UseDefaultSameSoundMethod') as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Source1, Source2, 'Soundex2') as a1 -- Soundex2 (ID# 1)
, SameSound(Source1, Source2, 'Caverphone2') as a2 -- Caverphone2 (ID# 2)
, SameSound(Source1, Source2, 'MatchRatingApproach') as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Source1, Source2, 'Metaphone') as a4 -- Metaphone (ID# 4)
, SameSound(Source1, Source2, 'CaverPhonePhonix') as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Source1, Source2, 'DoubleMetaphone') as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Source1, Source2, 'ColognePhonetics') as a7 -- ColognePhonetics (ID# 7)
, SameSound(Source1, Source2, 'EnPhoneticDistance') as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Source1, Source2, 'fuzzy_caver') as a128 -- fuzzy_caver (ID# 128)
, SameSound(Source1, Source2, 'fuzzy_phonetic') as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Source1, Source2, 'fuzzy_soundex') as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Source1, Source2, 'fuzzy_rsoundex') as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords1To1_NoMatch;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
