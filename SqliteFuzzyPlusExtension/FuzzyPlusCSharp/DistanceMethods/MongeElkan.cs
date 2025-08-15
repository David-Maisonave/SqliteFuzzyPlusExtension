using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public class MongeElkan : AbstractStringMetric, FuzzyPlusCSharp.DistanceMethods.IDistance
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
        private const double defaultMismatchScore = 0.0;
        private readonly double estimatedTimingConstant;
        private readonly AbstractStringMetric internalStringMetric;
        internal ITokeniser tokeniser;

        public MongeElkan() : this(new TokeniserWhitespace())
        {
        }

        public MongeElkan(AbstractStringMetric metricToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = new TokeniserWhitespace();
            this.internalStringMetric = metricToUse;
        }

        public MongeElkan(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = tokeniserToUse;
            this.internalStringMetric = new SmithWatermanGotoh();
        }

        public MongeElkan(ITokeniser tokeniserToUse, AbstractStringMetric metricToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = tokeniserToUse;
            this.internalStringMetric = metricToUse;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return -1;
            }
            Collection<string> collection = this.tokeniser.Tokenize(firstWord);
            Collection<string> collection2 = this.tokeniser.Tokenize(secondWord);
            double num = 0.0;
            for (int i = 0; i < collection.Count; i++)
            {
                string str = collection[i];
                double num3 = 0.0;
                for (int j = 0; j < collection2.Count; j++)
                {
                    string str2 = collection2[j];
                    double similarity = this.internalStringMetric.GetSimilarity(str, str2);
                    if (similarity > num3)
                    {
                        num3 = similarity;
                    }
                }
                num += num3;
            }
            return num / ((double)collection.Count);
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double count = this.tokeniser.Tokenize(firstWord).Count;
                double num2 = this.tokeniser.Tokenize(secondWord).Count;
                return (((count + num2) * count) + ((count + num2) * num2)) * estimatedTimingConstant;
            }
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
                return "Implements the Monge Elkan algorithm providing an matching style similarity measure between two strings";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "MongeElkan";
            }
        }
    }
}
