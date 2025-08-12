using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public static class OverlapCoefficient
    {
        public static double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return (double)GetDistance(source1,source2);
        }
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - (double)Distance(source1, source2, isCaseSensitive);
        }
        public static double GetDistance(string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(Math.Min(source1.Length, source2.Length));
    }
}
