# Asynchronous Notification I/O

- 비동기 입출력이란 입출력 함수의 반환시점과 데이터 송수신의 완료시점이 일치하지 않는 경우를 뜻한다.
- 동기 입출력이 입출력을 하는동안 다른일을 못하는데 반해, 비동기 입출력은 보다 효율적으로 CPU를 활용함.
- 동기 입출력의 단점을 극복한 모델임.

## Notification I/O ??

- Notification I/O란, IO와 관련해서 특정 상황이 발생했음을 알리는 것을 뜻한다.
	- 대표적인 모델은 select()이다.
		- select는 특정 시점에 리턴된다.
		- 비동기 Notification IO는 상황에 관계없이 즉시 리턴되는 모델이다.
		- select는 동기 notification IO에 해당.
		- 다만 그로인한 단점 해결을 위해 타임아웃지정이 가능하도록 정의되었다.