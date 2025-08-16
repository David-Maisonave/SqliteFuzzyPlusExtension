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
        // The Sameness functions first normalize the input values before comparing them.
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.FirstLastName(source1);
            source2 = Normalize.FirstLastName(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            source1 = Normalize.Phone(source1);
            source2 = Normalize.Phone(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Remove non-numeric characters
            source1 = Normalize.Social(source1);
            source2 = Normalize.Social(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Zip(source1);
            source2 = Normalize.Zip(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Address(source1);
            source2 = Normalize.Address(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Date(source1);
            source2 = Normalize.Date(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.FileName(source1);
            source2 = Normalize.FileName(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false, Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            source1 = Normalize.Number(source1);  // Returns a string instead of a number, because if distance method usage is required, a string is required
            source2 = Normalize.Number(source2);
            return Results(source1, source2, isCaseSensitive, distanceMethod, minimumDistance);
        }
        private static bool Results(string source1, string source2, bool isCaseSensitive, Fuzzy.DistanceMethod distanceMethod, double minimumDistance)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            DistanceMethods.IDistance iDistance = Fuzzy.GetIDistance(distanceMethod);
            if (iDistance == null)
                return source1 == source2;
            double distance = iDistance.Distance(source1, source2);
            return distance >= minimumDistance;
        }
    }
}
