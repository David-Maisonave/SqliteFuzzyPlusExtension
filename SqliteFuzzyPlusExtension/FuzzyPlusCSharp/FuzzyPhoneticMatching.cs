using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace FuzzyPlusCSharp
{
    static class FuzzyPhoneticMatching
    {
        public const bool EnPhoneticDistance_Supported = false;
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            return false;
        }
    }
}
