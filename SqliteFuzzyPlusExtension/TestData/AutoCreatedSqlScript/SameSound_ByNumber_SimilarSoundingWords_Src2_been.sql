select Words as src1, 'been' as src2 
, SameSound(Words, 'been', 0) as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'been', 1) as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'been', 2) as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'been', 3) as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'been', 4) as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'been', 5) as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'been', 6) as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'been', 7) as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'been', 64) as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'been', 128) as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'been', 129) as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'been', 130) as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'been', 131) as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
