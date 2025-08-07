using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static FuzzyPlusCSharp.SmithWatermanGotohWindowedAffine;
using static System.Net.Mime.MediaTypeNames;

namespace FuzzyPlusCSharp
{
    static class FuzzyPhoneticMatching
    {
        public const bool EnPhoneticDistance_Supported = false;
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            return false;
        }
    }
}
