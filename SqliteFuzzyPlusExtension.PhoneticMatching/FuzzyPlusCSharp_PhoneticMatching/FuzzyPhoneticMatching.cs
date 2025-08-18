using Microsoft.PhoneticMatching;
using Microsoft.PhoneticMatching.Distance;
using Microsoft.PhoneticMatching.Matchers.FuzzyMatcher.Normalized;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static FuzzyPlusCSharp.Fuzzy;

namespace FuzzyPlusCSharp
{
    static class FuzzyPhoneticMatching
    {
        public const bool EnPhoneticDistance_Supported = true;
        public static EnPhoneticDistance enPhoneticDistance = new EnPhoneticDistance();
        public static EnPronouncer enPronouncer = EnPronouncer.Instance;

        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true, Phonix.Soundex soundexPhonix = null)
        {
            try
            {
                EnPronunciation s1 = EnPronunciation.FromIpa(source1);
                EnPronunciation s2 = EnPronunciation.FromIpa(source2);
                string s = s1.ToString();
                double r = 1.0f - enPhoneticDistance.Distance(s1, s2);
                return isVerySimilar ? r > .9f : r > .75f;
            }
            catch
            {
                string s1 = soundexPhonix.BuildKey(source1);
                string s2 = soundexPhonix.BuildKey(source2);
                return isVerySimilar ? Fuzzy.Compare(s1, s2, StringMatchingAlgorithm_ID.ExactMatch, isVerySimilar)
                : Fuzzy.Compare(s1, s2, StringMatchingAlgorithm_ID.Levenshtein, isVerySimilar);
            }
        }
        public static string GetEnPhoneticString(string source, Phonix.Soundex soundexPhonix = null)
        {
            try
            {
                EnPronunciation s1 = EnPronunciation.FromIpa(source);
                return s1.ToString();
            }
            catch
            {
                return soundexPhonix.BuildKey(source);
            }
        }
    }
}
