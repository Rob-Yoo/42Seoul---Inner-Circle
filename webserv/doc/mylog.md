# 8/4(목)

- Webserv 자료조사
	- 소켓프로그래밍 in c++
	- select, poll, epoll, kqueue 등 함수 조사
	- I/O multiplexing 조사
		- block I/O vs non-block I/O 개념 (https://www.youtube.com/watch?v=mb-QHxVfmcs&t=848s)
		- Blocking I/O와 Non-blocking I/O (https://www.youtube.com/watch?v=XNGfl3sfErc)

- Swagger 자료조사, 발표준비
- Exam4 응시준비

# 8/15(월)

- 오늘할일
	- 집현전에 책 반납
	- socket 예제만들기
		- tcp_server/client
		- select_server/client
		- kqueue_server/client
	- Swagger 튜토리얼 만들기

# 8/15(월) 16:39

- tcp_server에서 왜 adress 구조체를 0이아닌 '\0'으로 초기화?

- select 타임아웃값을 얼마로 설정해야 할까?
- listen 대기열(백로그)의 수를 얼마로 설정해야 할까?

# 8/15(월) 20:00

- 한 클라이언트가 서버에 접속하고 문자열을 전송하는 과정에서 3번의 select가 호출된다.
1. 클라이언트가 서버에 접속을 시도할때, 서버의 리스닝 소켓에서 이벤트가 발생.
2. 클라이언트소켓에서 전송한 문자열을 read하는 이벤트 발생
3. 수신한 데이터가 EOF인 경우의 이벤트 발생.

# 8/15(월) 20:43

- kevent에 대해,,,
	1. 큐에 이벤트를 등록한다.
	- select()는 감시대상이 read, write, error가 그 조건이었다.
	- 어떤 이벤트를 시스템이 감지하게 할지 직접 요청할 수 있다.
	2. 미처리된 이벤트를 사용자에게 반환한다.
	- select()가 미처리된 이벤트의 개수를 사용자에게 반환한 것과 비슷하다.

# 8/16(화) 22:00

# 8/17(수) 20:00

TIL

- user mode, kernel mode
- kevent 이해 70%?
- listen의 두번째 인자인 backlog
	- 클라이언트가 connect()를 시도할때 한번에 줄을 설수있는 대기열 크기를 말함.
	- 이때 대기열은 서버에서 accept()를 하기 전 클라이언트가 줄을 설때 생긴다.
	- 만약 멀티쓰레드/프로스세나 IO멀티플렉싱을 적용하지않아서 한번에 한 클라이언트랑만 송수신할수있다면
	  실제 연결되는 클라이언트를 제외하고 모두 대기열에 줄을 서게 된다.

- blocking socket vs non-blocking socket
- https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=i1004me2&logNo=140151020393
	- blocking socket
		- 소켓 기본값
		- block될 수 있는 system call 호출시 block 될 수 있음.

	- non-blocking socket
		- 만들어진 소켓을 가지고 fcntl 함수로 만들 수 있다.
		- system call 사용시 block되는 상황이면, -1을 리턴하며 errno가 EWOULDBLOCK | EAGAIN이됨.

- kevent
```C
int
	kevent(int	kq, const struct kevent	*changelist, int nchanges,
	struct	kevent *eventlist, int nevents,
	const struct timespec *timeout);

struct kevent
{
	uintptr_t ident; /* 이벤트에 대한 identifier(파일 기술자) */
	short filter;    /* 이벤트 필터 플래그 */
	u_short flags;   /* kqueue?대한 액션 플래그 */
	u_int fflags;    /* 필터 플래그 값 */
	intptr_t data;   /* 필터 데이터 값 */
	void * udata;    /* 사용자 정의 데이터 */
};
<ident, filter> 로 이벤트를 식별함.
filter, fflags로 상황 인식,
flags로 해당 상황에 대한 처리.
```
- 인자설명
	- kq			: kqueue()로 만든 fd.
	- changelist	: 감시할 이벤트리스트
	- nchanges		: changelist 크기
	- eventlist		: changelist중 발생한 이벤트 목록
	- nevents		: 들어오는 이벤트의 최대값 => nchanges 아닌가?
	- timeout		: 함수호출후, 몇초동안 대기할 것인지?
	- ret			: 타임아웃시 0, 아닐시 발생한 이벤트의 수 반환.

- 사용법
	- kevent()호출은 반복해서 일어난다.
	- 호출후엔 nchanges를 0 으로 설정해야 한다.
	- 이벤트 등록을 할때, changelist, nchanges값을 변화시키면 된다.

## fflags

EVFILT_READ
- 해당 fd에 읽을 수 있는 데이터가 존재할때.
- filter의 행동은 fd타입에 따라 조금씩 다르다.

EVFILT_WRITE
- 해당 fd에 write할 수 있을때.
- read/write를 동시에 할순 없으니, read할 데이터가 없을때가 write할수 있는 경우 아닐까?

				// string protocol = "HTT/1.0 200 OK\r\n";
				// string servName = "Server:simple web server\r\n";
				// string cntLen = "Content-length:2048\r\n";
				// string cntType = "Content-type:text/html; charset=UTF-8\r\n\r\n";
				// string content = "<html><head><title>Default Page</title></head><body><h1>Hello World!</h1></body></html>";
				// string response = protocol+servName+cntLen+cntType;
				//const char *res = response.c_str();

# 8/24(수) 15:43

- Request 객체를 설계하고 있다.
	- HTTP Request 문자열을 파싱하여 Request의 각 멤버변수에 넣을 것이다.
	- 파싱하기 위해 split류의 함수를 써야하는데 ft_split은 C 스타일이라 C++스타일을 찾기로함.
		- C의 문자열과 C++의 문자열은 어떻게 다른지?
	- CGI 객체? CGI에 해당하는 환경변수 초기화를 어떻게 할지?

	# 환경변수 목록
	AUTH_TYPE

	요청데이터에 있는거
	CONTENT_LENGTH
	CONTENT_TYPE
	PATH_INFO
	QUERY_STRING
	REQUEST_METHOD
	REQUEST_URI
	SCRIPT_NAME
	SERVER_NAME
	SERVER_PORT

	고정
	GATEWAY_INTERFACE

	몰루?
	PATH_TRANSLATED

	소켓
	REMOTE_ADDR
	REMOTE_IDENT
	REMOTE_USER => 불필요?
/script/index.html
# 8/29(월) 20:08

- read/write할때 non-blocking version으로 바꾸자.
- 각 이벤트를 처리할때, 읽기쓰기별로 함수를 쪼개자.'
- 감시중인 fd를 close하면, kqueue에서는 해당 fd를 계속 감시할까?
	- 그래서 그 fd가 다른파일을 open하여 반환된 값이 되어도 이전 파일과 동일하게 감시할까?
	- 내가보았을땐 fd를 close하고 kqueue의 changelist에서도 제거해주는 것이 맞는 것 같다.
	- 그냥 EV_DELETE하면 되겠네.

# 8/30(화) 18:55

- errno를 쓸수없어 non-blocking 방식으로 반복 read/write 할 수 없다.
- 현재 CGI에 meta-variable을 주기 위해 Client, Request 객체를 생성하였다.
	- Client에서 env를 생성하도록 하는데, string을 argv[]로 어떻게 변형해야 할지 모르겠다.

- 지금 모든 시스템콜을 기다리지 않기 위해 하나의 통신과정이 여러 단계로 나뉘고 있다. 정리해보자.

- 클라이언트가 서버에 접속한다.
- 클라이언트의 read event를 polling 한다.
- 자식프로세스를 생성하여 클라이언트의 request를 CGI에 전달한다.
- 부모프로세스는 자식을 기다리지 않고 자식과 연결된 파이프의 read event를 polling 한다.
- 파이프의 read event를 polling 한다.
- 꺼낸 데이터를 response에 담는다.
- 클라이언트의 write event를 polling 한다.
- response를 클라이언트에게 write 한다.

# 8/30(화) 20:08

- HTTP Request 를 \r\n으로 split하는데,,,
	- Request안에 content가 \r, \n을 포함하는데 그건 왜 자르지 않는걸까/

# 8/31(수) 15:40

파이프 [0]읽기/출구, [1]쓰기/입구
fd 0표준입력, 1표준출력

1. 부모가 파이프 입구에 req_body를 넘겨준다.
2. 자식이 파이프 출구에서 req_body를 읽고 동작한다.
	- 파이프 출구를 표준입력으로!
3. 자식이 동작후 파이프 입구에 결과물을 넘겨준다.
	- 파이프 입구를 표준출력으로!
4. 부모가 파이프 출구에서 결과물을 꺼낸다.
	- 꺼내는 시점은 파이프 출구에서 readable이벤트가 발생할 때이다.
	- 문제는 1) 이후 곧바로 4)가 수행되는 것이 문제상황...ㅠ
	- 애초에 fork전에 넣어두는 것이 좋을듯 하다.

현재 자식에서 표준입력을 받지 못하고 있다.
자식의 표준입력은 파이프의 입구로 두었다.

자식이 파이프에서 데이터를 읽지 못하여 1->4가 발생한다...

그냥 gnl로 읽어오려고 하는데 gnl이 안써진다... 왜지??
makefile 기초가 이렇게 빈약했었나..

# 9/1(목) 10:54

- gnl이 안써지는 이유를 도저히 모르겠다. makefile에서 문법적인 오류를 찾을 수 없다...ㅠ
	- libgnl.a가 c로 작성되어서 c++코드에선 사용할 수 없을 지도....?
	- 그러면 gnl코드를 모두 C++로 바꾸면 사용가능?

- 파이프 2개를 이용하여 자식이 데이터를 받는 파이프, 자식이 처리한 결과를 보내는 파이프로 나누었다.
	- 자식이 부모가 보낸 데이터(body)를 가져가지만, EOF를 만나지못해 끝을 못내고있다.
	- write할 버퍼에 eof까지 주는데도, 자식이 종료되지 않는다;;;
	- 아 혹시 부모측에서 파이프를 닫아버리면, EOF가 자동으로 가지 않을까?
		- 이 생각이 맞았다!
	- 근데 to_parent파이프를 통해 read를 하는 부분이 여전히 이상하다.
		- 자식 프로세스가 종료되었으니까 to_parent파이프는 닫혔을 것 같은데,,,
		- 왜 read가 끝나지 않고 blocking되어버린 거지?
		- 부모측에서 to_parent[1]을 close하지 않아서!
		- 파이프는 입력부분을 닫지않으면 EOF를 인식할 수 없다....!!
		=> 파이프에 대한 이해가 부족한 것 같다.
		=> 왜 EOF는 파이프가 닫혀야만 검출될까?
		=> 파이프로 연결된 두 프로세스중 자식이 종료되도 파이프는 여전히 열려있나?
		=> 나 미니쉘때 이 부분을 적용했었나...?

	- 파이프에서 더이상 write해줄 프로세스가 없으면 EOF가 들어가는듯...!

- read의 반환값이 뭔가 이상하다. BUF_SIZE랑 같은 값이 반환된다....왜지?
	- write할때 문자열길이만큼 write하지 않고 버퍼크기 전체를 write했다.
	- read는 문자열 길이만큼 읽어오는 기능이 아니다.
prefix처리 /directory/파일명 -> root dir뒤져서 맞는 파일 찾고 있으면 반환.
해당 작업은 모든 req에 적용되야 함.
