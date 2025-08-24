-- Look for a DefaultName with possible [The Super Mario World] misspelling.
Select DefaultName, Alternate, Title, HowSimilar(DefaultName, "The Super Mario World") as S FROM AlternateNames WHERE S > 0.75 and DefaultName NOT like "%Super Mario World%" ORDER BY S;
