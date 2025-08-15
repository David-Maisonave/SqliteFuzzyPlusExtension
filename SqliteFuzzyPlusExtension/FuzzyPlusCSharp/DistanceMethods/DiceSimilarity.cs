using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public sealed class DiceSimilarity : AbstractStringMetric, FuzzyPlusCSharp.DistanceMethods.IDistance
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
        private readonly double estimatedTimingConstant;
        private readonly ITokeniser tokeniser;
        private readonly TokeniserUtilities<string> tokenUtilities;

        public DiceSimilarity() : this(new TokeniserWhitespace())
        {
        }

        public DiceSimilarity(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 3.4457139008736704E-07;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            return (firstWord != null) && (secondWord != null) && (tokenUtilities.CreateMergedSet(tokeniser.Tokenize(firstWord), this.tokeniser.Tokenize(secondWord)).Count > 0)
                ? 2.0 * tokenUtilities.CommonSetTerms() / (this.tokenUtilities.FirstSetTokenCount + this.tokenUtilities.SecondSetTokenCount)
                : 0.0;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return (length + num2) * ((length + num2) * this.estimatedTimingConstant);
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
                return "Implements the DiceSimilarity algorithm providing a similarity measure between two strings using the vector space of present terms";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "DiceSimilarity";
            }
        }
    }
}
