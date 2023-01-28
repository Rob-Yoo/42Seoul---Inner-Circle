#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#define MAX_CHANGE 100
#define MAX_EVENT 100

int main()
{

	/****************************************
	// 1. kqueue를 초기화 및 데이터 설정
	****************************************/
	int nKqueue;
	nKqueue = kqueue();

	struct kevent ChangeList[MAX_CHANGE];
	int nChanges = 0;

	struct kevent EventList[MAX_EVENT];


	/****************************************
	// 2. 알고자하는 READ/WRITE 이벤트를 준비
	****************************************/

	// 예를 들어 READ 이벤트를 잡고 싶다면
	// filter =  EVFILE_READ, flags = EV_ADD | EV_ENABLE
	// 삭제시에는 EV_ADD 대신 EV_DELETE를 주고 호출
	ChangeEvent( socket, EVFILT_READ, EV_ADD | EV_ENABLE, pData );


	/****************************************
	// 3. 준비된 이벤트를 커널에 등록
	****************************************/

	// 타임아웃 설정
	struct timespec timeout = { 0, 0 };

	int nEventCount = 0;
	nEventCount = kevent( nKqueue, ChangeList, nChanges, EventList, MAX_EVENT, &timeout );
	// 등록할 이벤트는 등록되었으므로 다시 초기화 시킨다.
	nChanges = 0;


	/****************************************
	// 4. 에러 처리
	****************************************/

	if( nEventCount == -1 )
	{
		// error
	}
	if( nEventCount == 0 )
	{
		// timeout
	}


	/****************************************
	// 5. 돌아온 이벤트의 종류를 보고 적당히 처리
	****************************************/

	for( int i = 0; i < nEventCount; i++ )
	{
		if( EventList[i].flags & EV_ERROR )
		{
			if( EventList[i].data == EBADF || m_pEventList[i].data == ENOENT )
				// 이게 무슨 경우였는지 생각이 안나네요. -_-;
			else
				// 이 경우도... 아시는 분 수정해주세요.
		}

		if( m_pEventList[i].filter == EVFILT_READ )
		{
			// 사용자로부터 패킷을 받았다.
			( ( CUser * ) m_pEventList[i].udata )->OnRead();
		}
	}

	/****************************************
	// 6. 사용이 끝나면 kqueue를 닫는다.
	****************************************/

	close( nKqueue );
}