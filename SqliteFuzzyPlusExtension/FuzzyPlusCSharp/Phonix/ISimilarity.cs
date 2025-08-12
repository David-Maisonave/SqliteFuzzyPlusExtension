namespace Phonix.Similarity
{
    public interface ISimilarity
    {
        bool IsSimilar(string[] words);
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
    public interface ISimilarityAll : ISimilarity, ISimilarity5Types, IHowSimilar, INotSimilar
    {
    }
}
