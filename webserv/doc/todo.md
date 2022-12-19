설정파일
- [O]main에 인자없을시 기본설정파일로 동작.
- [O]listen 뒤에 여러 숫자 들어오게.
- [O]delete, upload는 같은 root에서 동작.
- [O]type 지우기

멀티플렉싱
-  [O]하나의 서버블럭에 여러 포트존재.
-  [O]노파일명 && 빈바디 -> 에러처리
-  [O]파일명을 파싱해서 cgi요청인지 확인 후 플래그 설정.

Response
- [O]=boundary는 form태그로 파일전송시에만 유효. 인지할것.
  - [O]size_t i = content_type.find("boundary="); 이 부분 예외처리필요.
- [O]sudo dir를 하드코딩에서 변수사용하도록 수정할 것.
- [?]download는 mandatory달성 & 테스트통과전까지 보류.
- [X]location block "return"

- GET
  - if file exist
    - view file
  - if file is directory
    - find index file
      - if not exist, 404

  -

- POST
  - file name exist
    - make file with req body
  - file name not exist
    - ...?

- DELETE
  - find file in root.
    - delete file
  - if file not exist
    - error

- type 모두대체.
  - cgi flag
  - upload flag
- 정적파일요청 수행후, 플래그에 따라 값 가공.



오늘의 할일
- 최종 request를 출력할것.
- cgi flag
-
- 현재 upload가 안되는 이유
  - HTTP method에서 get/post를 구분하지 않기 때문이다.
  - file을 찾지못할때,
    - POST/PUT	: 새로운 파일을 생성함
    - GET		: 404 error

파일명이 없을때. -> 무조건 404

파일명은 있는데 유효하지 않은 파일명일때.
- POST/PUT	: 새로운 파일을 생성함
- GET		: 404 error


원코드에서 파일명이 ""인 경우와 아닌경우를 나누었는데 굳이 나눌 필요가 있었을까?

[O]파이프에 데이터 보낼때, read한 뒤에 eof 붙이기.
	- 읽고 EOF찍고 strlen만큼만 write한다.

[O]파이프에서 eof를 만날때만 로그찍기. 안그러면 미완성본이 여러번 출력될테니..
request도 완성본을 만들고나서 로그찍기
	현재 memory leak 우려파트 존재..


파일fd가 업로드(쓰기용)인지 조회용(읽기용)인지 알아야함?

write, 업로드 -> write를 모두 수행.
	- 파일생성후, 생성한 파일을 반환.

read, 조회 -> write이벤트 감지할 필요 없음.
	- 파일읽어서 반환.\

====================================

error페이지를 반환하도록...!
Test GET Expected 404 on http://localhost:4240/directory/Yeah
content returned: H

===================================

정적파일을 비동기로 처리할때,,, 과정을 정리해보자.

서버 디렉토리에 있는 정적파일을 GET할때의 과정이다.

1. 반환할 파일을 open한다. 파일디스크립터값 fd를 얻는다.

2. cli측에서 fd를 반환하면 Server가 해당 fd를 kqueue에 등록한다.

3. fd의 read이벤트를 감지된다. read한 값을 Response의 버퍼(이하 버퍼)에 저장한다.

4. 계속하여 read하다가 어느순간 read의 반환값이 0이된다. EOF를 의미하므로 read가 완료되었다.

5. 버퍼에 있는 값(content)이 Response body에 들어가게 된다.

다음으로, 클라이언트에서 POST메소드로 파일을 업로드하는 과정이다.

1. a.txt라는 파일명과 request body에 aaa가 들어간 요청이 날아왔다.

2. a.txt파일을 open한다. 파일디스크립터값 fd를 얻는다.

3. fd의 write이벤트를 감지한다. req_body값을 write한다.

4. write의 누적 반환값이 Requet's content-length와 일치하면 write가 종료된다.

5. 업로드 성공 응답을 전송한다.

============================================

# 11.10(목) 오늘의 할일

keep-alive에 따라 포트를 유지시키거나 삭제한다.
-> 동작 확인할 것.
-> 브라우저는 keep-alive on, curl은 keep-alive off이다.

file_to_client에 있는 튜플은 언제삭제시키지?
->file_fd를 close할때 같이해야 한다.

multiplexing timeout 설정 찾아보기.

cgi를 돌릴때...
	- 실행파일 이름을 하드코딩이 아닌 변수명으로 사용할것.
	- 파일을 인자로 넣지 말고 문자열을 인자로 넣을 것.
	- 해당 문자열을 파이프입구에 write해야 하는데... 파이프 입구도 저장을 해두어야 하나?

CGI 과정 정리

1. CGI 객체를 생성한다.(파이프 생성 및 파이프fd 논블락처리, 환경변수는 외부에서 만들어 넣어줌)
   - [O]CGI(env);
   - [X]pipe_to_client에 입력 출력 fd를 등록해야함.
2. cgi에 넘어온 content를 cgi의 input에 write 한다.
   - [O]CGI.setInput(sample);
3. input데이터를 to_child[1]에 write한다.
   - pipe fd's write event
4. to_parent[0]를 read하고 결과를 output에 저장한다.
   - pipe fd's read event
5. output데이터를 클라이언트 소켓에 write한다.
   - cli fd's write event


https://brook-paw-154.notion.site/Inception-70b40226228c4fab96f1943aefca0d1a
====================

get : 읽기 전용
post : 쓰기용

=> 아님... post요청이라도 errorpage를 반환할때는 open시 readonly로 함!.
=> fd를 통해 열려있는 모드 플래그값을 알아내는 것이 best일 듯 하다.

====================
# 11.11(금) 오늘의 할일

1. GET이외에 POST, DELETE를 구현완료하고 테스트한다.

- req's body를 file에 write해야 한다.
- 이때 read할 file과 write할 파일을 모두 fd로 다루므로 둘을 분간할 방법이 필요하다.
  - Client에서 read_flag, write_flag를 이용한다.

- GET,POST,Method함수에서 3번째 인자인 filepath제거할것.

2. CGI를 구현하고 테스트한다.
3. keep-alive를 테스트한다.

======================

/audoindex/bbbb/aaa.bla
1. locationblock[autoindex] == true,
2. if (ISDIR(filename))
   1. autoindex 응답
3. else
   1. errorpage 응답
	-> filename == IS_DIR true일때만 응답. false errorpage.

- aaa
=============

ctrl - 누르면 함수이동 뒤로가기가 된다.

m_cgi 0 초기화

업로드완성.
	- 리턴페이지가 이상하다.
    	- 업로드파일 내용이 마지막 문자가 남아있다.
      	- Response.cpp writeFile함수 맨밑.
	- 파일 이름이 겹칠때 이상함.

https://stackoverflow.com/questions/70369289/why-cant-i-open-my-file-using-open-methode

====================

autoindex
[O]redirection
[O]cgi

서버 오래켜놓으면 어느순간 죽음;; 왜그러는지 모르겠음
- keep-alive로 살려놓은 포트가 닫힐때 터진다?

Cgi 요청처리할때 상태코드를 어떻게 처리할지 모르겠다.
- 현재 cgi_init에서 무조건 200으로 셋팅하고있다.

======================

# 11/13 (일)

오늘의 목표!
- [O]autoindex 기능 완성
- [O]disconnect상황에 각 fd들이 close되고 map에서 지워지도록 하자.
  - keep-alive 옵션은 HTTP 표준이 아니다.
  - 생각보다 처리가 잘 안되서 해당 헤더가 들어오던말던 상관없이 포트연결은 한번의 요청-응답이 끝나면 삭제되도록 구현하였다.
- [O]siege test
- [X]statuscode값을 검사하는 함수만들기
- [O]리팩토링!

===============

autoindex
	- 1. CGI가 아닐때만 동작함.
	- 메소드별로 실행하지 않고 CGI처럼 별도의 실행흐름을 가진다.
	- 2. 대상이 디렉토리 -> 파일리스팅
	- 3. 대상이 파일 -> 다운로드
	- 4. 대상이 없음 -> 404 error

나머지 할일....
- FlowChart 를 그려서 전체적인 순서도 그려보기.
- 필요없는 부분은 지우고 코드가 잘 읽히도록 구조를 개선하기
- 변수명 통일하기.
- 코딩컨벤션(중괄호 띄어쓰기 들여쓰기등과 같은 부분)을 통일하자.
- 설정파일에서 특정 파일이 없으면 에러처리를 하는 로직이 필요할 것 같다.
- 서버블럭과 로케이션블럭을 request에서 저장할때 포인터 레퍼런스로 저장하면 좋을 것 같다.

아직 내가 모르는 부분....
- 왜 파일fd를 이벤트처리할때, 읽을수 있는길이인 data필드가 1로 들어올까?