using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class INormalizedLevenshtein : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => NormalizedLevenshtein.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => NormalizedLevenshtein.Distance(source1, source2, isCaseSensitive);
    }
    public static class NormalizedLevenshtein
    {
        public static double Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            double distance = Convert.ToDouble(Levenshtein2.NormalizedLevenshteinDistance(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length) - Levenshtein2.LevenshteinDistanceLowerBounds(source1, source2));
            return distance;
        }
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - (double)Distance(source1, source2, isCaseSensitive);
        }
    }
}
