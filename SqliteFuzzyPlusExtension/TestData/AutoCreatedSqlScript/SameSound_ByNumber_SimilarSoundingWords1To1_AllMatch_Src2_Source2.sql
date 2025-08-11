select Source1 as src1, Source2 as src2 
, SameSound(Source1, Source2, 0) as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Source1, Source2, 1) as a1 -- Soundex2 (ID# 1)
, SameSound(Source1, Source2, 2) as a2 -- Caverphone2 (ID# 2)
, SameSound(Source1, Source2, 3) as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Source1, Source2, 4) as a4 -- Metaphone (ID# 4)
, SameSound(Source1, Source2, 5) as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Source1, Source2, 6) as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Source1, Source2, 7) as a7 -- ColognePhonetics (ID# 7)
, SameSound(Source1, Source2, 64) as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Source1, Source2, 128) as a128 -- fuzzy_caver (ID# 128)
, SameSound(Source1, Source2, 129) as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Source1, Source2, 130) as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Source1, Source2, 131) as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords1To1_AllMatch;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
