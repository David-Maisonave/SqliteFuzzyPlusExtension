using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public static class Jaro
    {
        public static double Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int m = source1.Intersect(source2).Count();
            if (m == 0)
                return 0;
            string sourceTargetIntersectAsString = "";
            string targetSourceIntersectAsString = "";
            IEnumerable<char> sourceIntersectTarget = source1.Intersect(source2);
            IEnumerable<char> targetIntersectSource = source2.Intersect(source1);
            foreach (char character in sourceIntersectTarget)
                sourceTargetIntersectAsString += character;
            foreach (char character in targetIntersectSource)
                targetSourceIntersectAsString += character;
            double t = Levenshtein.Distance(sourceTargetIntersectAsString, targetSourceIntersectAsString, isCaseSensitive) / 2;
            return (double)((m / source1.Length) + (m / source2.Length) + ((m - t) / m)) / 3;
        }
    }
}
