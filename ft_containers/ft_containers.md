# FT_CONTAINERS TIL

## Day 1

1.	vector 관련 개념 공부

-	vector의 멤버 타입
	벡터의 value_type에 대한 iterator 타입을 선언해줘야 하는데 이때 iterator는 random_access_iterator이다.
	따라서 random_access_iterator에 대한 구현이 먼저여야 한다. iterator을 구현하기 위해서는 iterators_traits를 구현해야한다,,,

-	iterators_traits이란?
	