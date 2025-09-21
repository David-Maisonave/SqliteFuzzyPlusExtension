using Phonix.Similarity;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    // At minimum, all FuzzyPlusCSharp distance classes must support IDistance.
    public interface IDistance
    {
        double Percentage(string source1, string source2, bool isCaseSensitive = true);
        double Distance(string source1, string source2, bool isCaseSensitive = true);
    }
    public interface ISimilarity2Types
    {
        bool IsVerySimilar(string source1, string source2);
        bool IsSimilar(string source1, string source2);
    }
    public interface ISimilarity3Types : ISimilarity2Types
    {
        bool IsSomeWhatSimilar(string source1, string source2);
    }
    public interface ISimilarity4Types : ISimilarity3Types
    {
        bool IsSlightlySimilar(string source1, string source2);
    }
    public interface ISimilarity5Types : ISimilarity4Types
    {
        bool IsHardlySimilar(string source1, string source2);
    }
    public interface IHowSimilar
    {
        double HowSimilar(string source1, string source2);
    }
    public interface INotSimilar
    {
        bool IsNotSimilar(string source1, string source2);
    }
    // The goal is to have all the distance classes support ISimilarityFullSupport interface
    public interface ISimilarityFullSupport : ISimilarity5Types, IHowSimilar, INotSimilar, IDistance
    {
    }
}
