using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class ITverskyIndex : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            throw new NotImplementedException();
        }
        public double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            throw new NotImplementedException();
        }
    }
    public class TverskyIndex
    {
    }
}
