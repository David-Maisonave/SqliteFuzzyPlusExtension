// UnitTestConsole_C_Runner.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
//#define COMPILE_TO_C_LANGUAGE__
#include "..\SqliteFuzzyPlusExtension.h"

int main()
{
    printf("Running UnitTestConsole_C_Runner\n");
    bool s1 = SameSound("to", "to", enum_Soundex2, GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s2 = SameSound("to", "two", enum_Soundex2, GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s3 = SameSound("to", "too", GetSameSoundMethodID("Soundex2"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s4 = SameSound("to", "if", GetSameSoundMethodID("Soundex2"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s5 = SameSound("to", "no", enum_Soundex2, GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s6 = SameSound("to", "to", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s7 = SameSound("to", "two", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s8 = SameSound("to", "too", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s9 = SameSound("to", "if", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    bool s0 = SameSound("to", "no", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("SameSound_StrCmp"), 1);
    printf("s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
    s1 = SAMESOUND("there", "there", "Soundex2");
    s2 = SAMESOUND("there", "their", "Soundex2");
    s3 = SAMESOUND("there", "they're", "Soundex2");
    s4 = SAMESOUND_ID("there", "bear", enum_Soundex2);
    s5 = SAMESOUND_ID("there", "band", enum_Soundex2);
    s6 = SAMESOUND("there", "there", "fuzzy_soundex");
    s7 = SAMESOUND("there", "their", "fuzzy_soundex");
    s8 = SAMESOUND("there", "they're", "fuzzy_soundex");
    s9 = SAMESOUND_ID("there", "bear", enum_fuzzy_soundex);
    s0 = SAMESOUND_ID("there", "band", enum_fuzzy_soundex);
    printf("s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
    s1 = SAMESOUND("been", "been", "Soundex2");
    s2 = SAMESOUND("been", "being", "Soundex2");
    s3 = SAMESOUND("been", "flat", "Soundex2");
    s4 = SAMESOUND_ID("been", "bean", enum_Soundex2);
    s5 = SAMESOUND_ID("been", "bin", enum_Soundex2);
    s6 = SAMESOUND("been", "been", "fuzzy_soundex");
    s7 = SAMESOUND("been", "being", "fuzzy_soundex");
    s8 = SAMESOUND("been", "flat", "fuzzy_soundex");
    s9 = SAMESOUND_ID("been", "bean", enum_fuzzy_soundex);
    s0 = SAMESOUND_ID("been", "bin", enum_fuzzy_soundex);
    printf("s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
}
