# Webserv Todo List

- Client 정보를 저장할 list 자료구조가 필요. 어떻게 저장할지 설계할 것.
- 모든 fd를 nonblock해야 하는가?

- Client가 Request를 참조자로 들고있는데,,, Client->Request로 데이터가 생성되므로 구조를 바꿔야할듯

- new Request(a.req); 오류안나게 하기.