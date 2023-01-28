#

```C
// "1.2.3.4" => 주소구조체값으로 설정
in_addr_t	inet_addr(const char *string);
int			inet_aton(const char *string, struct in_addr *addr);

// 주소구조체값 => "1.2.3.4"
// 내부적으로 메모리를 할당하는데 strdup하는 편이 좋다.
// 함수 재호출시 이전에 할당한 메모리에 값을 덮어쓰기 때문
// 함수내부에서 static한 공간이 존재하는 듯
char*		inet_ntoa(struct in_addr adr);

```

## 빅 엔디안, 리틀 엔디안 방식

- 빅 엔디안
	1234 => 1  2  3  4
- 리틀 엔디안
	1234 => 4  3  2  1

## bind
- 서버에서 수행
- 특정<IP,PORT>로 들어오는 모든 데이터를 나한테 보낸다.
- INADDR_ANY : 현재 열려있는 모든 IP인듯?

## connect
- 클라이언트에서 수행
- 특정<IP,PORT>로 연결한다.

