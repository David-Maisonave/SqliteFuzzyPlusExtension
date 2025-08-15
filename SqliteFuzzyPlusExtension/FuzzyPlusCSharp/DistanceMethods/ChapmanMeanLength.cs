﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public sealed class ChapmanMeanLength : AbstractStringMetric, FuzzyPlusCSharp.DistanceMethods.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return GetSimilarity(source1, source2);
        }
        public double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            double distance = Percentage(source1, source2, isCaseSensitive);
            return (1.0f - distance) * 10;
        }
        private const int chapmanMeanLengthMaxString = 500;
        private const double defaultMismatchScore = 0.0;
        private const double defaultPerfectScore = 1.0;

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double num = secondWord.Length + firstWord.Length;
            if (num > 500.0)
            {
                return 1.0;
            }
            double num2 = (500.0 - num) / 500.0;
            return 1.0 - (num2 * num2 * num2 * num2);
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
                return "Implements the Chapman Mean Length algorithm provides a similarity measure between two strings from size of the mean length of the vectors - this approach is supposed to be used to determine which metrics may be best to apply rather than giving a valid response itself";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "ChapmanMeanLength";
            }
        }
    }
}
