using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class IJaccardIndex : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => JaccardIndex.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => JaccardIndex.Distance(source1, source2, isCaseSensitive);
    }
    internal class JaccardIndex
    {
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return (double)Distance(source1, source2);
            //return 1.0f - (double)Distance(source1, source2);
        }
        public static double Distance(string source1, string source2, bool isCaseSensitive)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return (double)Distance(source1, source2);
        }

        public static double Distance(string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Union(source2).Count());
    }
}
