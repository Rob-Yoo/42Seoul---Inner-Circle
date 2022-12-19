# Webserv

본 문서는 42Seoul inner circle(5circle) 과제를 수행하며 정리한 내용입니다.

## Webserv 과제이해

- Multiplexing을 적용하여 blocking I/O가 아닌 non-blocking I/O로 구현한다.

- Non-blocking fd를 사용하여 입출력시 blocking되지 않으므로 poll()류의 함수를 선행할것.

## 과제를 하며 궁금했던 개념

- 허용함수 원형 + 설명하기.

- Multiplexing
	- C10K Problem
		- https://www.gpgstudy.com/forum/viewtopic.php?t=2097
		- https://heeestorys.tistory.com/513
	- Blocking I/O vs Non-blocking I/O
	- 기본 socket 함수 in C language
	- select(), poll(), epoll(), kqueue() 류와 같은 소켓함수

- HTTP 1.1
	- HTTP Method
	- HTTP Chunked Message

- 정적 vs 동적 페이지
- [Web Server]
	- Web Server software ranking 2022를 검색하면..
	- NGinX
	- Apache HTTP Server
	- IIS
- Container(=CGI?)
- [Web Application Server] = Web Server + Container
	-

- CGI
	- Meta-variables

https://velog.io/@ayokinya/CGI
https://qaos.com/sections.php?op=viewarticle&artid=194
- static Website

## 구현사항.

- upload
	- html <form> 태그를 이용해 파일을 업로드 할 수 있게하면 좋을 것 같다.

1. config안에서 서버블록마다 listen소켓을 열어준다.
   1. 듣기 소켓을 열때 이미 열린 소켓인지 검사해야 함.
2. 이벤트가 발생한 소켓이 어떤 서버블록에 해당하는지 알아낸다.
3. 요청을 읽고 해당 서버블록의 룰에 위반되는지 확인한다.

임시

- read_client_reqeust에서 pending이 true일떄 ret값 반환이 모호함.

- Content-Type: multipart/form-data; boundary=--------------------------911677640024699020355582
에 대한 이해가 필요함

왜 upload요청 처리한다음에 요청보내면 터짐?
