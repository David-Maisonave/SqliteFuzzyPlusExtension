using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.Misc
{
    public static class SamenessAndNormalize
    {
        public static string NormalizeFirstLastName(string name)
        {
            name = Regex.Replace(name, "[\\s][A-Za-z]\\.", "");
            name = Regex.Replace(name, "[\\s][A-Za-z]$", "");
            name = Regex.Replace(name, "[\\s][0-9][A-Za-z]{2}", "");
            name = Regex.Replace(name, "[\\s][JSjs][Rr]\\.?", "");
            name = Regex.Replace(name, "[\\s][Ii]+$", "");
            name = Regex.Replace(name, "[\\s][Ii]+\\s", "");
            name = Regex.Replace(name, "([A-Za-z]+)\\s*\\,\\s*([A-Za-z]+.*)", "$2 $1");
            name = Regex.Replace(name, "[^A-Za-z\\s]+", "");
            name = name.Replace("  ", " ");
            return name;
        }
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false)
        {
            source1 = NormalizeFirstLastName(source1);
            source2 = NormalizeFirstLastName(source2);
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return source1 == source2;
        }
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
    }
}
