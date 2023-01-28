# 1. Introduction

## 1.1 Purpose

- CGI는 HTTP 서버와 cgi 스크립트가 클라이언트의 요청에 응답하는 책임을 공유하도록 합니다.
- CGI는 추상적인 파라미터(meta-variables로 알려지고 고객의 요청을 설명함)를 정의합니다.
- 해당 서버는 연결 관리, 데이터 전송 및 전달이나 CGI 스크립트가 데이터 접근이나 문서 작업같은 일을
	처리하도록 하는 클라이언트 요청과 관련된 네트워크 이슈에 대한 책임을 가집니다.

## 1.2 Requirements

-

## 1.3 Specifications

## 1.4 Terminology

meta-variable	: 서버에서 스크립트로 가져와지는 정보를 나타내는 파라미터.
script			:
server			:


# 4. CGI Request

## 4.1 Request Meta-Variables

### 4.1.2 CONTENT_LENGTH
- 요청에 첨부된 메시지 본문의 크기(있는 경우)를 10진수 옥텟으로 포함합니다.
- 데이터가 첨부되지 않으면 NULL(또는 unset)입니다.
CONTENT_LENGTH = "" | 1*digit
- 서버는 요청이 메시지 본문 엔티티와 함께 제공된 경우에만 이 메타 변수를 설정해야 합니다.
- 서버가 전송 부호화 또는 내용 부호화를 제거한 후 메시지 본문의 길이를 반영해야 합니다.
	=>.....? 이걸 어떻게 처리하지.

### 4.1.3 CONTENT_TYPE
- 요청에 메시지 본문이 포함된 경우 CONTENT_TYPE 변수는 메시지 본문의 인터넷 미디어 유형으로 설정됩니다.
CONTENT_TYPE = "" | media-type
media-type   = type "/" subtype *( ";" parameter )
type         = token
subtype      = token
parameter    = attribute "=" value
attribute    = token
value        = token | quoted-string
- type, subtype 파라미터는 대소문자구분이 없다.
- parameter value는 대소문자 구분.
- 이 변수는 기본값이 없다. unset의 경우에만 스크리트가 수신된 데이터에서 미디어 유형을 확인하려 시도할 수 있다.
- 유형이 알려지지 않은 경우 스크립트는 응용 프로그램/옥텟 스트림 유형을 가정하거나 6.3.3 절에서 설명한 바와 같이 오류와 함께 요청을 거부할 수 있습니다.
	=> ...?'
- 각 미디어 유형은 선택적 및 필수 매개 변수 집합을 정의합니다. 이는 메시지 본문에 대한 코드화된 문자 집합을 정의하는 대소문자를 구분하지 않는 값을 갖는 문자 집합 매개변수를 포함할 수 있다.
- charset 매개 변수를 생략하면 다음 규칙 중 가장 먼저 적용되는 규칙에 따라 기본값을 도출해야 합니다.
1. 일부 미디어 유형에 대해 시스템 정의 기본 문자 집합이 있을 수 있습니다.
2. 미디어 유형 "텍스트"의 기본값은 ISO-8859-1 [4]입니다.
3. 미디어 유형 규격에 정의된 기본값입니다.
4. 기본값은 US-ASCII입니다.
- HTTP Content-Type 필드가 클라이언트 요청 헤더에 있는 경우 서버는 이 메타 변수를 설정해야 합니다.
- 서버가 연결된 엔티티가 있지만 내용 유형 헤더 필드가 없는 요청을 수신하면 올바른 내용 유형을 확인하려고 시도할 수 있으며, 그렇지 않으면 이 메타 변수를 생략해야 합니다.

### 4.1.4 GATEWAY_INTERFACE

### 4.1.5 PATH_INFO
- PATH_INFO 변수는 CGI 스크립트에 의해 해석될 경로를 지정합니다.
- CGI 스크립트에서 반환할 리소스 또는 하위 리소스를 식별하고 스크립트 자체를 식별하는 부분 다음에 오는 URI 경로 계층에서 파생됩니다.
- URI 경로와 달리 PATH_INFO는 URL로 인코딩되지 않으며 경로 세그먼트 매개 변수를 포함할 수 없습니다.
- "/"의 PATH_INFO는 단일 void 경로 세그먼트를 나타냅니다.
PATH_INFO = "" | ( "/" path )
path      = lsegment *( "/" lsegment )
lsegment  = *lchar
lchar     = <any TEXT or CTL except "/">

- 값은 대소문자를 구분하는 것으로 간주되며 서버는 요청 URI에 표시된 경로의 대소문자를 보존해야 합니다.
- 서버는 PATH_INFO에 대해 허용하는 값에 대해 제한 및 제한을 가할 수 있으며, 부적합하다고 간주되는 값이 발견되면 오류와 함께 요청을 거부할 수 있습니다.
- 이것은 인코딩된 "/"가 PATH_INFO로 디코딩되는 결과를 초래할 수 있는 요청을 포함할 수 있다.
- 마찬가지로 경로에서 US-ASCII가 아닌 문자를 처리하는 방법도 시스템 정의입니다.

localhost:3000/cgi/hello
localhost:3000/cgi/bye

cgi : SCRIPT_NAME
path: /cgi/hello or /hello
path: /cgi/bye or /bye

=> /cgi 이하의 요청은 스크립트를 호출하여 해결할 요청.
=>
l