# 소켓사용순서
1. 소켓 생성				socket()
```C
int server_fd = socket(domain, type, protocol);
// 주소체계, 서비스 종류, 프로토콜 종류(필요없다면 0)
// 실패시 -1, 성공시 fd반환
```

2. IP, PORT 할당			bind()
	- 특정 port와 fd를 결합한다.
```C
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
// 실패시 -1, 성공시 0반환
// sockfd에 myaddr이 할당된다.
```

3. 연결요청 가능상태로 변경		listen()

4. 연결요청에 대한 수락			accept()


cgi

동적페이지 생성.
	컨테이너에 동적페이지 생성 역할을 넘김.
	웹서버, 컨테이너가 미들웨어 형식으로 내장된 경우 있음.
	cgi를 example.php
	phpcgi?


## send recv

## select_server sudo code

```C
int main()
{
	// 소켓생성 => bind => listen

	// fd_set을 0으로 초기화
	// fd_set에 서버소켓을 추가

	while (1)
	{
		copys = reads (fd_set 복사본에 대입)
		select 호출

		for(int i=0;i<fd_max+1;i++)
		{
			if (이벤트발생개수 == 0)
				break;
			if (i에서 이벤트가 발생하지않음)
				continue ;

			// 여기서부터 이벤트가 발생한 소켓의 경우에 동작하는 로직이다.
			if (i가 리스닝소켓)
			{
				accept호출
				fd_max 최신화
				클라이언트 소켓을 감시대상에 추가
			}
			else // i가 이미 연결된 클라이언트 소켓인 경우이다.
			{
				len = read()를 수행
				if (len == 0) // EOF를 수신한 경우
				{
					i를 감시대상에서 제거
					i소켓 닫기
				}
				else
					수신한 문자열 출력
			}
		}
	}
	서버소켓 닫기
}
```