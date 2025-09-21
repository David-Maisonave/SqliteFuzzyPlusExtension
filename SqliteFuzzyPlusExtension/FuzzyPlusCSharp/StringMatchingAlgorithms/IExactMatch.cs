using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0050 // Disabling this warning, because using string.compare() does NOT make the code more readable compared to a simple ==  or != operators.
    public class IExactMatch : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return source1 == source2 ? (double)1.0f : (double)0.0f;
        }
        public double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return source1 == source2 ? (double)0.0f : (double)1.0f;
        }
    }
}
