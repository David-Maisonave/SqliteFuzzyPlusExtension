using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static FuzzyPlusCSharp.StringMatchingAlgorithms.SmithWatermanGotohWindowedAffine;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
#pragma warning disable CRR0048
    public interface IStringMetric
    {
        double GetSimilarity(string firstWord, string secondWord);
        string GetSimilarityExplained(string firstWord, string secondWord);
        long GetSimilarityTimingActual(string firstWord, string secondWord);
        double GetSimilarityTimingEstimated(string firstWord, string secondWord);
        double GetUnnormalisedSimilarity(string firstWord, string secondWord);

        string LongDescriptionString { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractStringMetric : IStringMetric
    {
        protected AbstractStringMetric()
        {
        }

        public double[] BatchCompareSet(string[] setRenamed, string comparator)
        {
            if ((setRenamed == null) || (comparator == null))
            {
                return null;
            }
            double[] numArray = new double[setRenamed.Length];
            for (int i = 0; i < setRenamed.Length; i++)
            {
                numArray[i] = this.GetSimilarity(setRenamed[i], comparator);
            }
            return numArray;
        }

        public double[] BatchCompareSets(string[] firstSet, string[] secondSet)
        {
            double[] numArray;
            if ((firstSet == null) || (secondSet == null))
            {
                return null;
            }
            numArray = firstSet.Length <= secondSet.Length ? (new double[firstSet.Length]) : (new double[secondSet.Length]);
            for (int i = 0; i < numArray.Length; i++)
            {
                numArray[i] = this.GetSimilarity(firstSet[i], secondSet[i]);
            }
            return numArray;
        }

        public abstract double GetSimilarity(string firstWord, string secondWord);
        public abstract string GetSimilarityExplained(string firstWord, string secondWord);
        public long GetSimilarityTimingActual(string firstWord, string secondWord)
        {
            long num = (DateTime.Now.Ticks - 0x89f7ff5f7b58000L) / 0x2710L;
            this.GetSimilarity(firstWord, secondWord);
            long num2 = (DateTime.Now.Ticks - 0x89f7ff5f7b58000L) / 0x2710L;
            return num2 - num;
        }

        public abstract double GetSimilarityTimingEstimated(string firstWord, string secondWord);
        public abstract double GetUnnormalisedSimilarity(string firstWord, string secondWord);

        public abstract string LongDescriptionString { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public sealed class DummyStopTermHandler : ITermHandler
    {
        public void AddWord(string termToAdd)
        {
        }

        public bool IsWord(string termToTest)
        {
            return false;
        }

        public void RemoveWord(string termToRemove)
        {
        }

        public int NumberOfWords
        {
            get
            {
                return 0;
            }
        }

        public string ShortDescriptionString
        {
            get
            {
                return "DummyStopTermHandler";
            }
        }

        public StringBuilder WordsAsBuffer
        {
            get
            {
                return new StringBuilder();
            }
        }
    }
#pragma warning disable IDE0028
#pragma warning disable IDE0079
#pragma warning disable IDE0047
#pragma warning disable IDE0046
#pragma warning disable IDE0044
#pragma warning disable IDE0032 // Use auto property
    public class TokeniserUtilities<T>
    {
        private Collection<T> allTokens;
        private int firstSetTokenCount;
        private int firstTokenCount;
        private int secondSetTokenCount;
        private int secondTokenCount;
        private Collection<T> tokenSet;

        public TokeniserUtilities()
        {
            this.AllTokens = new Collection<T>();
            this.tokenSet = new Collection<T>();
        }

        private void AddTokens(Collection<T> tokenList)
        {
            foreach (T local in tokenList)
            {
                this.AllTokens.Add(local);
            }
        }

        private void AddUniqueTokens(Collection<T> tokenList)
        {
            foreach (T local in tokenList)
            {
                if (!this.tokenSet.Contains(local))
                {
                    this.tokenSet.Add(local);
                }
            }
        }

        private int CalculateUniqueTokensCount(Collection<T> tokenList)
        {
            Collection<T> collection = new Collection<T>();
            foreach (T local in tokenList)
            {
                if (!collection.Contains(local))
                {
                    collection.Add(local);
                }
            }
            return collection.Count;
        }

        public int CommonSetTerms()
        {
            return this.FirstSetTokenCount + this.SecondSetTokenCount - this.tokenSet.Count;
        }

        public int CommonTerms()
        {
            return this.FirstTokenCount + this.SecondTokenCount - this.AllTokens.Count;
        }

        public Collection<T> CreateMergedList(Collection<T> firstTokens, Collection<T> secondTokens)
        {
            this.AllTokens.Clear();
            this.firstTokenCount = firstTokens.Count;
            this.secondTokenCount = secondTokens.Count;
            this.MergeLists(firstTokens);
            this.MergeLists(secondTokens);
            return this.AllTokens;
        }

        public Collection<T> CreateMergedSet(Collection<T> firstTokens, Collection<T> secondTokens)
        {
            this.tokenSet.Clear();
            this.firstSetTokenCount = this.CalculateUniqueTokensCount(firstTokens);
            this.secondSetTokenCount = this.CalculateUniqueTokensCount(secondTokens);
            this.MergeIntoSet(firstTokens);
            this.MergeIntoSet(secondTokens);
            return this.tokenSet;
        }

        public Collection<T> CreateSet(Collection<T> tokenList)
        {
            this.tokenSet.Clear();
            this.AddUniqueTokens(tokenList);
            this.firstTokenCount = this.tokenSet.Count;
            this.secondTokenCount = 0;
            return this.tokenSet;
        }

        public void MergeIntoSet(Collection<T> firstTokens)
        {
            this.AddUniqueTokens(firstTokens);
        }

        public void MergeLists(Collection<T> firstTokens)
        {
            this.AddTokens(firstTokens);
        }

        public int FirstSetTokenCount
        {
            get
            {
                return this.firstSetTokenCount;
            }
        }

        public int FirstTokenCount
        {
            get
            {
                return this.firstTokenCount;
            }
        }

        public Collection<T> MergedTokens
        {
            get
            {
                return this.AllTokens;
            }
        }

        public int SecondSetTokenCount
        {
            get
            {
                return this.secondSetTokenCount;
            }
        }

        public int SecondTokenCount
        {
            get
            {
                return this.secondTokenCount;
            }
        }

        public Collection<T> TokenSet
        {
            get
            {
                return this.tokenSet;
            }
        }

        public Collection<T> AllTokens { get => AllTokens1; set => AllTokens1 = value; }
        public Collection<T> AllTokens1 { get => allTokens; set => allTokens = value; }
    }

    public interface ITermHandler
    {
        void AddWord(string termToAdd);
        bool IsWord(string termToTest);
        void RemoveWord(string termToRemove);

        int NumberOfWords { get; }

        string ShortDescriptionString { get; }

        StringBuilder WordsAsBuffer { get; }
    }
    public interface ITokeniser
    {
        Collection<string> Tokenize(string word);
        Collection<string> TokenizeToSet(string word);

        string Delimiters { get; }

        string ShortDescriptionString { get; }

        ITermHandler StopWordHandler { get; set; }
    }
    public sealed class TokeniserWhitespace : ITokeniser
    {
        private string delimiters = "\r\n\t \x00a0";
        private ITermHandler stopWordHandler = new DummyStopTermHandler();
        private TokeniserUtilities<string> tokenUtilities = new TokeniserUtilities<string>();

        public Collection<string> Tokenize(string word)
        {
            Collection<string> collection = new Collection<string>();
            if (word != null)
            {
                int length;
                for (int i = 0; i < word.Length; i = length)
                {
                    char c = word[i];
                    if (char.IsWhiteSpace(c))
                    {
                        i++;
                    }
                    length = word.Length;
                    for (int j = 0; j < this.delimiters.Length; j++)
                    {
                        int index = word.IndexOf(this.delimiters[j], i);
                        if ((index < length) && (index != -1))
                        {
                            length = index;
                        }
                    }
                    string termToTest = word.Substring(i, length - i);
                    if (!this.stopWordHandler.IsWord(termToTest))
                    {
                        collection.Add(termToTest);
                    }
                }
            }
            return collection;
        }
        public Collection<string> TokenizeToSet(string word)
        {
            return word != null ? this.tokenUtilities.CreateSet(this.Tokenize(word)) : null;
        }

        public string Delimiters
        {
            get
            {
                return this.delimiters;
            }
        }

        public string ShortDescriptionString
        {
            get
            {
                return "TokeniserWhitespace";
            }
        }

        public ITermHandler StopWordHandler
        {
            get
            {
                return this.stopWordHandler;
            }
            set
            {
                this.stopWordHandler = value;
            }
        }
    }
    public interface ISubstitutionCost
    {
        double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex);

        double MaxCost { get; }

        double MinCost { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractSubstitutionCost : ISubstitutionCost
    {
        protected AbstractSubstitutionCost()
        {
        }

        public abstract double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex);

        public abstract double MaxCost { get; }

        public abstract double MinCost { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public interface IAffineGapCost
    {
        double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap);

        double MaxCost { get; }

        double MinCost { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractAffineGapCost : IAffineGapCost
    {
        protected AbstractAffineGapCost()
        {
        }

        public abstract double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap);

        public abstract double MaxCost { get; }

        public abstract double MinCost { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public sealed class AffineGapRange5To0Multiplier1 : AbstractAffineGapCost
    {
        private const int charExactMatchScore = 5;
        private const int charMismatchMatchScore = 0;

        public override double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap)
        {
            if (stringIndexStartGap >= stringIndexEndGap)
            {
                return 0.0;
            }
            return (double)(5 + ((stringIndexEndGap - 1) - stringIndexStartGap));
        }

        public override double MaxCost
        {
            get
            {
                return 5.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return 0.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "AffineGapRange5To0Multiplier1";
            }
        }
    }
    public sealed class SubCostRange5ToMinus3 : AbstractSubstitutionCost
    {
        private Collection<string>[] approx = new Collection<string>[7];
        private const int charApproximateMatchScore = 3;
        private const int charExactMatchScore = 5;
        private const int charMismatchMatchScore = -3;

        public SubCostRange5ToMinus3()
        {
            this.approx[0] = new Collection<string>();
            this.approx[0].Add("d");
            this.approx[0].Add("t");
            this.approx[1] = new Collection<string>();
            this.approx[1].Add("g");
            this.approx[1].Add("j");
            this.approx[2] = new Collection<string>();
            this.approx[2].Add("l");
            this.approx[2].Add("r");
            this.approx[3] = new Collection<string>();
            this.approx[3].Add("m");
            this.approx[3].Add("n");
            this.approx[4] = new Collection<string>();
            this.approx[4].Add("b");
            this.approx[4].Add("p");
            this.approx[4].Add("v");
            this.approx[5] = new Collection<string>();
            this.approx[5].Add("a");
            this.approx[5].Add("e");
            this.approx[5].Add("i");
            this.approx[5].Add("o");
            this.approx[5].Add("u");
            this.approx[6] = new Collection<string>();
            this.approx[6].Add(",");
            this.approx[6].Add(".");
        }

        public override double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                if ((firstWord.Length <= firstWordIndex) || (firstWordIndex < 0))
                {
                    return -3.0;
                }
                if ((secondWord.Length <= secondWordIndex) || (secondWordIndex < 0))
                {
                    return -3.0;
                }
                if (firstWord[firstWordIndex] == secondWord[secondWordIndex])
                {
                    return 5.0;
                }
                char ch = firstWord[firstWordIndex];
                string item = ch.ToString().ToLowerInvariant();
                char ch2 = secondWord[secondWordIndex];
                string str2 = ch2.ToString().ToLowerInvariant();
                for (int i = 0; i < this.approx.Length; i++)
                {
                    if (this.approx[i].Contains(item) && this.approx[i].Contains(str2))
                    {
                        return 3.0;
                    }
                }
            }
            return -3.0;
        }

        public override double MaxCost
        {
            get
            {
                return 5.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return -3.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SubCostRange5ToMinus3";
            }
        }
    }

    public class TokeniserQGram3 : AbstractTokeniserQGramN
    {
        public TokeniserQGram3()
        {
            base.StopWordHandler = new DummyStopTermHandler();
            base.TokenUtilities = new TokeniserUtilities<string>();
            base.CharacterCombinationIndex = 0;
            base.QGramLength = 3;
        }

        public override Collection<string> Tokenize(string word)
        {
            return base.Tokenize(word, false, base.QGramLength, base.CharacterCombinationIndex);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(base.SuppliedWord))
            {
                return $"{this.ShortDescriptionString} : not word passed for tokenizing yet.";
            }
            return string.Format("{0} - currently holding : {1}.{2}The method is using a QGram length of {3}.", new object[] { this.ShortDescriptionString, base.SuppliedWord, Environment.NewLine, Convert.ToInt32(base.QGramLength) });
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "TokeniserQGram3";
            }
        }
    }
    public abstract class AbstractTokeniserQGramN : ITokeniser
    {
        private int characterCombinationIndex;
        private const string defaultEndPadCharacter = "#";
        private const string defaultStartPadCharacter = "?";
        private int qGramLength;
        private ITermHandler stopWordHandler;
        private string suppliedWord;
        private TokeniserUtilities<string> tokenUtilities;

        protected AbstractTokeniserQGramN()
        {
        }

        public abstract Collection<string> Tokenize(string word);
        public Collection<string> Tokenize(string word, bool extended, int tokenLength, int characterCombinationIndexValue)
        {
            int num3;
            if (string.IsNullOrEmpty(word))
            {
                return null;
            }
            this.SuppliedWord = word;
            Collection<string> collection = new Collection<string>();
            int length = word.Length;
            int count = 0;
            if (tokenLength > 0)
            {
                count = tokenLength - 1;
            }
            StringBuilder builder = new StringBuilder(length + (2 * count));
            if (extended)
            {
                builder.Insert(0, "?", count);
            }
            builder.Append(word);
            if (extended)
            {
                builder.Insert(builder.Length, "#", count);
            }
            string str = builder.ToString();
            num3 = extended ? length + count : (length - tokenLength) + 1;
            for (int i = 0; i < num3; i++)
            {
                string termToTest = str.Substring(i, tokenLength);
                if (!this.stopWordHandler.IsWord(termToTest))
                {
                    collection.Add(termToTest);
                }
            }
            if (characterCombinationIndexValue != 0)
            {
                str = builder.ToString();
                num3--;
                for (int j = 0; j < num3; j++)
                {
                    string str3 = $"{(str.Substring(j, count))}{(str.Substring(j + tokenLength, 1))}";
                    if (!this.stopWordHandler.IsWord(str3) && !collection.Contains(str3))
                    {
                        collection.Add(str3);
                    }
                }
            }
            return collection;
        }

        public Collection<string> TokenizeToSet(string word)
        {
            if (!string.IsNullOrEmpty(word))
            {
                this.SuppliedWord = word;
                return this.TokenUtilities.CreateSet(this.Tokenize(word));
            }
            return null;
        }

        public int CharacterCombinationIndex
        {
            get
            {
                return this.characterCombinationIndex;
            }
            set
            {
                this.characterCombinationIndex = value;
            }
        }

        public string Delimiters
        {
            get
            {
                return string.Empty;
            }
        }

        public int QGramLength
        {
            get
            {
                return this.qGramLength;
            }
            set
            {
                this.qGramLength = value;
            }
        }

        public abstract string ShortDescriptionString { get; }

        public ITermHandler StopWordHandler
        {
            get
            {
                return this.stopWordHandler;
            }
            set
            {
                this.stopWordHandler = value;
            }
        }

        public string SuppliedWord
        {
            get
            {
                return this.suppliedWord;
            }
            set
            {
                this.suppliedWord = value;
            }
        }

        public TokeniserUtilities<string> TokenUtilities
        {
            get
            {
                return this.tokenUtilities;
            }
            set
            {
                this.tokenUtilities = value;
            }
        }
    }
    public class TokeniserQGram3Extended : TokeniserQGram3
    {
        public override Collection<string> Tokenize(string word)
        {
            return base.Tokenize(word, true, base.QGramLength, base.CharacterCombinationIndex);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(base.SuppliedWord))
            {
                return $"{this.ShortDescriptionString} : not word passed for tokenizing yet.";
            }
            return string.Format("{0} - currently holding : {1}.{2}The method is using a QGram length of {3}.", new object[] { this.ShortDescriptionString, base.SuppliedWord, Environment.NewLine, Convert.ToInt32(base.QGramLength) });
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "TokeniserQGram3Extended";
            }
        }
    }
    public sealed class SubCostRange1ToMinus2 : AbstractSubstitutionCost
    {
        private const int charExactMatchScore = 1;
        private const int charMismatchMatchScore = -2;

        public override double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return -2.0;
            }
            if ((firstWord.Length <= firstWordIndex) || (firstWordIndex < 0))
            {
                return -2.0;
            }
            if ((secondWord.Length <= secondWordIndex) || (secondWordIndex < 0))
            {
                return -2.0;
            }
            return ((firstWord[firstWordIndex] != secondWord[secondWordIndex]) ? ((double)(-2)) : ((double)1));
        }

        public override double MaxCost
        {
            get
            {
                return 1.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return -2.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SubCostRange1ToMinus2";
            }
        }
    }
#pragma warning restore IDE0032
#pragma warning restore IDE0044
#pragma warning restore IDE0046
#pragma warning restore IDE0047
#pragma warning disable IDE0079
#pragma warning disable IDE0028
}
