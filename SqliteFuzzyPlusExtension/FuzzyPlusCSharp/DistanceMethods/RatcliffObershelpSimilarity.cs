using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public class IRatcliffObershelpSimilarity : FuzzyPlusCSharp.DistanceMethods.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => RatcliffObershelpSimilarity.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => RatcliffObershelpSimilarity.Distance(source1, source2, isCaseSensitive);
    }
    public static class RatcliffObershelpSimilarity
    {
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - (double)Distance(source1, source2);
        }
        public static double Distance(this string source1, string source2, bool isCaseSensitive)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return (double)Distance(source1, source2);
        }
        public static double Distance(string source1, string source2) => 2 * Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Length + source2.Length);
    }
}
