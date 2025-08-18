using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static FuzzyPlusCSharp.Fuzzy;
using static System.Net.Mime.MediaTypeNames;

namespace FuzzyPlusCSharp
{
    static class FuzzyPhoneticMatching
    {
        public const bool EnPhoneticDistance_Supported = false;
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true, Phonix.Soundex soundexPhonix = null)
        {
            if (soundexPhonix == null)
                return false;
            string s1 = soundexPhonix.BuildKey(source1);
            string s2 = soundexPhonix.BuildKey(source2);
            return isVerySimilar ? Fuzzy.Compare(s1, s2, StringMatchingAlgorithm_ID.ExactMatch, isVerySimilar) 
                : Fuzzy.Compare(s1, s2, StringMatchingAlgorithm_ID.Levenshtein, isVerySimilar);
        }
        public static string GetEnPhoneticString(string source, Phonix.Soundex soundexPhonix = null)
        {
            return soundexPhonix == null ? "" : soundexPhonix.BuildKey(source);
        }
    }
}
