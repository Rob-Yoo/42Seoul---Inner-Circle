# php

## 출현 배경
- html을 수동으로 만드는 한계 극복
	- html을 기계가 만든다면?
	- php,jsp,asp,Django,RubyOnRails,Node.js 출현

- php를 이용해 웹페이지를 자동으로 생성
	- 모든 웹페이지를 수정해야할때 수동으로 해야한다면 불편
	- php를 이용

- 하나의 php파일로 서로다른 페이지를 만들어낼 수 있다.

## WebServ에 어떻게 적용?

- php가 동적인 데이터를 생성하여 웹서버가 반환해주는 것까진 이해완료.
- php가 무슨 작업을 해줘야 하는지?

업로드된 파일을 route할 수 있게 만든다.
그리고 파일이 있어야 하는 위치를 구성한다.

### 서브젝ㅌ트에서 cgi 언급한 내용
* CGI가 무엇인지 궁금하십니까?
* CGI를 직접 호출하지 않기 때문에 전체 경로를 PATH_INFO로 사용하십시오.
	- cgi파일의 경로는 절대경로로 한다.
* 청크 요청의 경우 서버가 청크를 해제해야 함을 기억하십시오.
	- 무거운 요청은 나눠서 들어오는데 이를 청크라고 하는 거 같음
	- 그 청크를 해제한다는게 무슨말인지 잘 모르겠다.
	- NginX에서 청크를 어떻게 처리하는지 알아보자.
그것과 CGI는 본문의 EOF를 예상할 것입니다.
* CGI의 출력도 마찬가지입니다. content_length가 반환되지 않는 경우
CGI에서 EOF는 반환된 데이터의 끝을 표시합니다.
	- ?????
* 프로그램은 요청된 파일을 첫 번째 인수로 사용하여 CGI를 호출해야 합니다.
* CGI는 상대 경로 파일 액세스를 위해 올바른 디렉토리에서 실행되어야 합니다.
* 서버는 하나의 CGI(php-CGI, Python 등)로 작동해야 합니다.
	- cgi 파일은 한개!