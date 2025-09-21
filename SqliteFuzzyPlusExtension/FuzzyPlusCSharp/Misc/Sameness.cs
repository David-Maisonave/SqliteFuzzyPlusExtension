using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.Misc
{
#pragma warning disable CRR0050 // Disabling this warning, because using string.compare() does NOT make the code more readable compared to a simple ==  or != operators.
    public static class Sameness
    {
        // The Sameness functions first normalize the input values before comparing them.
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.FirstLastName(source1);
            source2 = Normalize.FirstLastName(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameNames(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.FirstLastName(source1);
            source2 = Normalize.FirstLastName(source2);
            if (Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance))
                return true;
            source2 = Normalize.ReverseNames(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            source1 = Normalize.Phone(source1);
            source2 = Normalize.Phone(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Remove non-numeric characters
            source1 = Normalize.Number(source1);
            source2 = Normalize.Number(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Zip(source1);
            source2 = Normalize.Zip(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Address(source1);
            source2 = Normalize.Address(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.Date(source1);
            source2 = Normalize.Date(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {
            source1 = Normalize.FileName(source1);
            source2 = Normalize.FileName(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.ExactMatch, double minimumDistance = Fuzzy.ISSIMILAR)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            source1 = Normalize.Number(source1);  // Returns a string instead of a number, because if distance method usage is required, a string is required
            source2 = Normalize.Number(source2);
            return Results(source1, source2, isCaseSensitive, stringMatchingAlgorithm, minimumDistance);
        }
        private static bool Results(string source1, string source2, bool isCaseSensitive, Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm, double minimumDistance)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            StringMatchingAlgorithms.IDistance iDistance = Fuzzy.GetIDistance(stringMatchingAlgorithm);
            if (iDistance == null)
                return source1 == source2;
            double distance = iDistance.Percentage(source1, source2);
            return distance >= minimumDistance;
        }
    }
}
