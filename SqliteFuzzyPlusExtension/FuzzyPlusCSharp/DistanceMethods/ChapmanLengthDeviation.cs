using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public sealed class ChapmanLengthDeviation : AbstractStringMetric
    {
        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double length = firstWord.Length;
            double num2 = secondWord.Length;
            return length >= num2 ? num2 / length : length / num2;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetSimilarity(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Chapman Length Deviation algorithm whereby the length deviation of the word strings is used to determine if the strings are similar in size - This approach is not intended to be used single handedly but rather alongside other approaches";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "ChapmanLengthDeviation";
            }
        }
    }
}
