using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.PhoneticMatching;
using Microsoft.PhoneticMatching.Distance;
using Microsoft.PhoneticMatching.Matchers.FuzzyMatcher.Normalized;

namespace FuzzyPlusCSharp
{
    static class FuzzyPhoneticMatching
    {
        public const bool EnPhoneticDistance_Supported = true;
        public static EnPhoneticDistance enPhoneticDistance = new EnPhoneticDistance();
        public static EnPronouncer enPronouncer = EnPronouncer.Instance;

        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            try
            {
                EnPronunciation s1 = EnPronunciation.FromIpa(source1);
                EnPronunciation s2 = EnPronunciation.FromIpa(source2);
                double r = 1.0f - enPhoneticDistance.Distance(s1, s2);
                return isVerySimilar ? r > .9f : r > .75f;
            }
            catch
            {
                return false;
            }
        }
    }
}
