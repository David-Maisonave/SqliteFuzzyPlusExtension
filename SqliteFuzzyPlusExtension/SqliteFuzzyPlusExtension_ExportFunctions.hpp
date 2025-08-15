// This file is meant to be an extension to SqliteFuzzyPlusExtension.cpp

/////////////////////////////////////////////////////////////////////////////////
// SQLean Functions
__declspec(dllexport)
std::string fuzzy_rsoundex(const char* source) {
    char* value = refined_soundex(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
std::string fuzzy_caver(const char* source) {
    char* value = caverphone(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
std::string fuzzy_phonetic(const char* source) {
    char* value = (char*)phonetic_hash((const unsigned char*)source, (int)strlen(source));
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
std::string fuzzy_soundex(const char* source) {
    char* value = soundex(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
std::string fuzzy_translit(const char* source) {
    char* value = (char*)transliterate((const unsigned char*)source, (int)strlen(source));
    std::string returnValue = value;
    free(value);
    return returnValue;
}

/////////////////////////////////////////////////////////////////////////////////
// Export Regex Functions
__declspec(dllexport)
std::string RegexSearch(const char* source, const char* pattern) {
    String^ source1 = gcnew String(source);
    String^ source2 = gcnew String(pattern);
    CString results = FuzzyPlusCSharp::Fuzzy::RegexSearch(source1, source2);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

__declspec(dllexport)
std::string RegexReplace(const char* source, const char* pattern, const char* replacement) {
    String^ source1 = gcnew String(source);
    String^ source2 = gcnew String(pattern);
    String^ source3 = gcnew String(replacement);
    CString results = FuzzyPlusCSharp::Fuzzy::RegexReplace(source1, source2, source3);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

extern "C"
{
    /////////////////////////////////////////////////////////////////////////////////
    // Export Distance Functions
    __declspec(dllexport)
        double DamerauLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::DamerauLevenshteinDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double DamerauLevenshtein(const char* str1, const char* str2, bool isCaseSensitive) { // This is an alias for DamerauLevenshteinDistance
        return DamerauLevenshteinDistance(str1, str2, isCaseSensitive);
    }

    __declspec(dllexport)
        double LevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::LevenshteinDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double Levenshtein(const char* str1, const char* str2, bool isCaseSensitive) { // This is an alias for LevenshteinDistance
        return LevenshteinDistance(str1, str2, isCaseSensitive);
    }

    __declspec(dllexport)
        double BlockDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::BlockDistance(source1, source2, isCaseSensitive);
    }
    __declspec(dllexport)
        double HammingDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::HammingDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double Hamming(const char* str1, const char* str2, bool isCaseSensitive) { // This is an alias for HammingDistance
        return HammingDistance(str1, str2, isCaseSensitive);
    }

    __declspec(dllexport)
        double JaccardDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::JaccardDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double JaroDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::JaroDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double JaroWinklerDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::JaroWinklerDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double Levenshtein2Distance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::Levenshtein2Distance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double LongestCommonSubsequenceDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::LongestCommonSubsequenceDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double LongestCommonSubstringDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::LongestCommonSubstringDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double NormalizedLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::NormalizedLevenshteinDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double OverlapCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::OverlapCoefficientDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double PhraseSimplifiedDiff(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::PhraseSimplifiedDiff(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        double RatcliffObershelpSimilarityDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::RatcliffObershelpSimilarityDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double SorensenDiceDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::SorensenDiceDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double TanimotoCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        double distance = FuzzyPlusCSharp::Fuzzy::TanimotoCoefficientDistance(source1, source2, isCaseSensitive);
        return distance;
    }

    __declspec(dllexport)
        double NeedlemanWunsch(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::NeedlemanWunsch(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double JaccardIndex(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::JaccardIndex(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double ChapmanLengthDeviation(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::ChapmanLengthDeviation(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double ChapmanMeanLength(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::ChapmanMeanLength(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double EuclideanDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::EuclideanDistance(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double MatchingCoefficient(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::MatchingCoefficient(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double MongeElkan(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::MongeElkan(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double QGramsDistance(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::QGramsDistance(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double SmithWaterman(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SmithWaterman(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double SmithWatermanGotoh(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SmithWatermanGotoh(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double SmithWatermanGotohWindowedAffine(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SmithWatermanGotohWindowedAffine(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double CosineSimilarity(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::CosineSimilarity(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double JaccardSimilarity(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::JaccardSimilarity(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double LongestCommonSequence(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::LongestCommonSequence(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double DiceSimilarity(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::DiceSimilarity(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double PhraseTokenize(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::PhraseTokenize(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        double SimplePhraseTokenize(const char* str1, const char* str2, bool isCaseSensitive) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SimplePhraseTokenize(source1, source2, isCaseSensitive);
    }

    __declspec(dllexport)
        bool SameFirstLastName(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameFirstLastName(source1, source2, false);
    }

    __declspec(dllexport)
        bool SamePhone(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SamePhone(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameSocial(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameSocial(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameZip(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameZip(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameAddress(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameAddress(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameDate(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameDate(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameFileName(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameFileName(source1, source2, false);
    }

    __declspec(dllexport)
        bool SameNumber(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::SameNumber(source1, source2, false);
    }

    __declspec(dllexport)
        double EdlibDistance(const char* source1, const char* source2) {
        return Edlib_Distance(source1, source2, true);
    }

    // Export Edlib fuzzy Distance Functions
    __declspec(dllexport)
        double iEdlibDistance(const char* source1, const char* source2) {
        return Edlib_Distance(source1, source2, false);
    }

    // Export SQLean fuzzy Distance Functions
    __declspec(dllexport)
        unsigned fuzzy_damlev(const char* source1, const char* source2) {
        return damerau_levenshtein(source1, source2);
    }

    __declspec(dllexport)
        int fuzzy_editdist(const char* source1, const char* source2) {
        return edit_distance(source1, source2, 0);
    }

    __declspec(dllexport)
        int fuzzy_hamming(const char* source1, const char* source2) {
        return hamming(source1, source2);
    }

    __declspec(dllexport)
        double fuzzy_jarowin(const char* source1, const char* source2) {
        return jaro_winkler(source1, source2);
    }

    __declspec(dllexport)
        unsigned fuzzy_leven(const char* source1, const char* source2) {
        return levenshtein(source1, source2);
    }

    __declspec(dllexport)
        unsigned fuzzy_osadist(const char* source1, const char* source2) {
        return optimal_string_alignment(source1, source2);
    }


    /////////////////////////////////////////////////////////////////////////////////
    // Export Wrapper Distance Functions
    __declspec(dllexport)
        int SetDefaultDistanceMethodByName(const char* DistanceMethod_Name) {
        String^ source1 = gcnew String(DistanceMethod_Name);
        FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(source1);
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
    }

    __declspec(dllexport)
        int SetDefaultDistanceMethodByID(int DistanceMethod_Id) {
        FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(DistanceMethod_Id);
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
    }

    __declspec(dllexport)
        int SetDefaultSameSoundMethod(int sameSoundMethod_ID) {
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(sameSoundMethod_ID);
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultSameSoundMethod;
    }

    __declspec(dllexport)
        int SetDefaultSameSoundMethodByName(const char* sameSoundMethod_Name) {
        String^ source1 = gcnew String(sameSoundMethod_Name);
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(source1);
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultSameSoundMethod;
    }

    __declspec(dllexport)
        int GetDistanceMethodID(const char* DistanceMethod_Name) {
        return (int)GetDistanceMethod(DistanceMethod_Name);
    }

    __declspec(dllexport)
        int GetDefaultDistanceMethod() {
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
    }

    __declspec(dllexport)
        int GetDefaultSoundMethod() {
        return (int)FuzzyPlusCSharp::Fuzzy::DefaultSameSoundMethod;
    }

    __declspec(dllexport)
        double Distance(const char* source1, const char* source2, int DistanceMethod_Id) {
        return Distance(source1, source2, GetDistanceMethod(DistanceMethod_Id));
    }

    __declspec(dllexport)
        double DistanceByName(const char* source1, const char* source2, const char* DistanceMethod_Name) {
        return Distance(source1, source2, GetDistanceMethod(DistanceMethod_Name));
    }

    __declspec(dllexport)
        double HowSimilar(const char* source1, const char* source2, int DistanceMethod_Id) {
        return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Id));
    }

    __declspec(dllexport)
        double HowSimilarById(const char* source1, const char* source2, int DistanceMethod_Id) {
        return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Id));
    }

    __declspec(dllexport)
        double HowSimilarByName(const char* source1, const char* source2, const char* DistanceMethod_Name) {
        return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Name));
    }

    /////////////////////////////////////////////////////////////////////////////////
    // Export Phonetic Functions
    __declspec(dllexport)
        bool EnPhoneticDistance(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::EnPhoneticDistance(source1, source2, TRUE);
        return distance;
    }

    __declspec(dllexport)
        bool EnPhoneticDistance_IsSupported() {
        return FuzzyPlusCSharp::Fuzzy::EnPhoneticDistance_IsSupported();
    }

    __declspec(dllexport)
        bool Caverphone2(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::Caverphone2(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool Soundex2(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::Soundex2(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool MatchRatingApproach(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::MatchRatingApproach(source1, source2, true);
        return distance;
    }

    __declspec(dllexport)
        bool Metaphone(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::Metaphone(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool CaverPhonePhonix(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::CaverPhonePhonix(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool DoubleMetaphone(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::DoubleMetaphone(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool ColognePhonetics(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        bool distance = FuzzyPlusCSharp::Fuzzy::ColognePhonetics(source1, source2);
        return distance;
    }

    __declspec(dllexport)
        bool fuzzy_caver(const char* source1, const char* source2) {
        std::string s1 = fuzzy_caver(source1);
        std::string s2 = fuzzy_caver(source2);
        return s1 == s2;
    }

    __declspec(dllexport)
        int get_fuzzy_script(const char* source) {
        return script_code((const unsigned char*)source, (int)strlen(source));;
    }

    __declspec(dllexport)
        bool fuzzy_script(const char* source1, const char* source2) {
        int s1 = script_code((const unsigned char*)source1, (int)strlen(source2));
        int s2 = script_code((const unsigned char*)source2, (int)strlen(source2));
        return s1 == s2;
    }

    __declspec(dllexport)
        bool fuzzy_phonetic(const char* source1, const char* source2) {
        std::string s1 = fuzzy_phonetic(source1);
        std::string s2 = fuzzy_phonetic(source2);
        return s1 == s2;
    }

    __declspec(dllexport)
        bool fuzzy_rsoundex(const char* source1, const char* source2) {
        std::string s1 = fuzzy_rsoundex(source1);
        std::string s2 = fuzzy_rsoundex(source2);
        return s1 == s2;
    }

    __declspec(dllexport)
        bool fuzzy_soundex(const char* source1, const char* source2) {
        std::string s1 = fuzzy_soundex(source1);
        std::string s2 = fuzzy_soundex(source2);
        return s1 == s2;
    }

    __declspec(dllexport)
        bool fuzzy_translit(const char* source1, const char* source2) {
        std::string s1 = fuzzy_translit(source1);
        std::string s2 = fuzzy_translit(source2);
        return s1 == s2;
    }

    __declspec(dllexport)
        int get_fuzzy_caver(const char* source, char* distBuffer, int bufferSize)
    {
        std::string s = fuzzy_caver(source);
        if (s.length() + 1 > bufferSize)
            return (int)s.length() + 1;
        strcpy_s(distBuffer, bufferSize, s.c_str());
        return 0;
    }

    __declspec(dllexport)
        int get_fuzzy_phonetic(const char* source, char* distBuffer, int bufferSize)
    {
        std::string s = fuzzy_phonetic(source);
        if (s.length() + 1 > bufferSize)
            return (int)s.length() + 1;
        strcpy_s(distBuffer, bufferSize, s.c_str());
        return 0;
    }

    __declspec(dllexport)
        int get_fuzzy_rsoundex(const char* source, char* distBuffer, int bufferSize)
    {
        std::string s = fuzzy_rsoundex(source);
        if (s.length() + 1 > bufferSize)
            return (int)s.length() + 1;
        strcpy_s(distBuffer, bufferSize, s.c_str());
        return 0;
    }

    __declspec(dllexport)
        int get_fuzzy_soundex(const char* source, char* distBuffer, int bufferSize)
    {
        std::string s = fuzzy_soundex(source);
        if (s.length() + 1 > bufferSize)
            return (int)s.length() + 1;
        strcpy_s(distBuffer, bufferSize, s.c_str());
        return 0;
    }

    __declspec(dllexport)
        int get_fuzzy_translit(const char* source, char* distBuffer, int bufferSize)
    {
        std::string s = fuzzy_translit(source);
        if (s.length() + 1 > bufferSize)
            return (int)s.length() + 1;
        strcpy_s(distBuffer, bufferSize, s.c_str());
        return 0;
    }

    __declspec(dllexport)
        int GetSameSoundMethodID(const char* SameSoundMethod_Name) {
        return (int)GetSameSoundMethod(SameSoundMethod_Name);
    }

    __declspec(dllexport)
        bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id, bool isVerySimilar) {
        return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Id), GetDistanceMethod(DistanceMethod_Id), isVerySimilar);
    }

    /////////////////////////////////////////////////////////////////////////////////
    // Export Regex Functions
    __declspec(dllexport)
        bool RegexMatch(const char* source, const char* pattern) {
        String^ source1 = gcnew String(source);
        String^ source2 = gcnew String(pattern);
        return FuzzyPlusCSharp::Fuzzy::RegexMatch(source1, source2);
    }

    __declspec(dllexport)
        char* RegexSearch(const char* source, const char* pattern, char* returnBuffer, int bufferSize)
    {
        std::string r = RegexSearch(source, pattern);
        if (r.length() < bufferSize)
        {
            strcpy_s(returnBuffer, bufferSize, r.c_str());
            return returnBuffer;
        }
        return NULL;
    }

    __declspec(dllexport)
        char* RegexReplace(const char* source, const char* pattern, const char* replacement, char* returnBuffer, int bufferSize)
    {
        std::string r = RegexReplace(source, pattern, replacement);
        if (r.length() < bufferSize)
        {
            strcpy_s(returnBuffer, bufferSize, r.c_str());
            return returnBuffer;
        }
        return NULL;
    }

    /////////////////////////////////////////////////////////////////////////////////
    // Export Miscellaneous Functions
    __declspec(dllexport)
        unsigned __int64 NormalizeNum(const char* source) {
        try {
            return convertToInt64(source);
        }
        catch (...) {
            return -1;
        }
    }

    __declspec(dllexport)
        int MaxValue(int source1, int source2) {
        return FuzzyPlusCSharp::Fuzzy::MaxValue(source1, source2);
    }

    __declspec(dllexport)
        int MinValue(int source1, int source2) {
        return FuzzyPlusCSharp::Fuzzy::MinValue(source1, source2);
    }

    __declspec(dllexport)
        int MaxLength(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::MaxLength(source1, source2);
    }

    __declspec(dllexport)
        int MinLength(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        return FuzzyPlusCSharp::Fuzzy::MinLength(source1, source2);
    }
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// C++ function

/////////////////////////////////////////////////////////////////////////////////
// Export Wrapper Distance Functions
__declspec(dllexport)
SqliteFuzzyPlusExtension::DistanceMethod_ID SetDefaultDistanceMethod(const char* DistanceMethod_Name) {
    String^ source1 = gcnew String(DistanceMethod_Name);
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(source1);
    return (SqliteFuzzyPlusExtension::DistanceMethod_ID)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
}

__declspec(dllexport)
SqliteFuzzyPlusExtension::DistanceMethod_ID SetDefaultDistanceMethod(int DistanceMethod_Id) {
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(DistanceMethod_Id);
    return (SqliteFuzzyPlusExtension::DistanceMethod_ID)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
}

__declspec(dllexport)
double Distance(const char* source1, const char* source2, const char* DistanceMethod_Name) {
    return Distance(source1, source2, GetDistanceMethod(DistanceMethod_Name));
}

__declspec(dllexport)
double HowSimilar(const char* source1, const char* source2, const char* DistanceMethod_Name) {
    return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Name));
}

/////////////////////////////////////////////////////////////////////////////////
// Export Phonetic Functions
__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name, bool isVerySimilar) {
    if (SameSoundMethod_Name == NULL)
        return SameSound(source1, source2, 0, 0, true);
    if (DistanceMethod_Name == NULL)
        return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Name), GetDistanceMethod(0), true);
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Name), GetDistanceMethod(DistanceMethod_Name), isVerySimilar);
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Id), GetDistanceMethod(DistanceMethod_Id), true);
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Name), GetDistanceMethod(DistanceMethod_Name), true);
}

/////////////////////////////////////////////////////////////////////////////////
// Export Miscellaneous Functions
__declspec(dllexport)
std::string NormalizeFirstLastName(const char* name) {
    String^ nameStr = gcnew String(name);
    CString results = FuzzyPlusCSharp::Misc::Normalize::FirstLastName(nameStr);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

__declspec(dllexport)
std::string HasCharInSameOrder(const char* str) {
    String^ source = gcnew String(str);
    CString results = FuzzyPlusCSharp::Fuzzy::HasCharInSameOrder(source);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

