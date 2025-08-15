using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.Misc
{
    public static class Sameness
    {
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = 0.75)
        {
            source1 = Normalize.FirstLastName(source1);
            source2 = Normalize.FirstLastName(source2);
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            DistanceMethods.IDistance iDistance = Fuzzy.GetIDistance(distanceMethod);
            if (iDistance == null )
                return source1 == source2;
            double distance = iDistance.Distance(source1, source2);
            return distance >= minimumDistance;
        }
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Phone(source1);
            source2 = Normalize.Phone(source2);
            return source1 == source2;
        }
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Social(source1);
            source2 = Normalize.Social(source2);
            return source1 == source2;
        }
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Zip(source1);
            source2 = Normalize.Zip(source2);
            return source1 == source2;
        }
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Address(source1);
            source2 = Normalize.Address(source2);
            return source1 == source2;
        }
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Date(source1);
            source2 = Normalize.Date(source2);
            return source1 == source2;
        }
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.FileName(source1);
            source2 = Normalize.FileName(source2);
            return source1 == source2;
        }
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            source1 = Normalize.Number(source1);
            source2 = Normalize.Number(source2);
            return source1 == source2;
        }
    }
}
