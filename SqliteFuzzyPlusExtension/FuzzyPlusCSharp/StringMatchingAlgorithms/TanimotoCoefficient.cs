using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class ITanimotoCoefficient : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => TanimotoCoefficient.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => TanimotoCoefficient.Distance(source1, source2, isCaseSensitive);
    }
    public static class TanimotoCoefficient
    {
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            return Distance(source1, source2, isCaseSensitive);
        }
        public static double Distance(string source1, string source2, bool isCaseSensitive)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            double Na = source1.Length;
            double Nb = source2.Length;
            double Nc = source1.Intersect(source2).Count();
            return Nc / (Na + Nb - Nc);
        }
    }
}
