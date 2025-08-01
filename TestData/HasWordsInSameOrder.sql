SELECT Phrases, (HasWordsInSameOrder("foo phxrase", 'Phrases')) as cn FROM SimilarPhrase 
 where (HasWordsInSameOrder("foo phxrase", 'Phrases')) > 2