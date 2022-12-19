# blocking I/O
- I/O 작업을 요청한 프로세스/쓰레드는 요청이 완료될때까지 블락(대기)된다.

# non-blocking I/O
- 블락되지 않고 즉시 리턴(pending)을 받음으로써 프로세스/쓰레드가 다른 작업을 수행할 수 있다.

# non-blocking I/O의 결과 처리방식

- 완료되었는지 반복적으로 확인
	- 완료시간 ~ 확인시간사이의 갭이 존재 => 처리속도 느려질 가능성
	- 반복적 확인으로 CPU 낭비가 발생

- I/O multiplexing(다중 입출력)
	- I/O 작업들을 동시에 모니터링하고 완료된 작업들을 한번에 알려준다.
	- 네트워크 통신에 많이 사용

- Callback/Signal
	- POSIX AIO
	- LINUX AIO

- io_uring
	- file i/o에 좋다?

## non-block I/O를 통해 I/O 요청 완료 전에도 다른 일을 할 수 있다!

# I/O multiplexing 종류

- select
- poll
=> 2종류는 성능이 좋지 않다.

- epoll(Linux)
	- N개의 소켓중 하나라도 read 이벤트가 발생하면 알려주도록 설정가능.

- kqueue(MacOS)

- IOCP(I/O completion port)(Win, 솔라리스)


