#include "./Response.hpp"

bool	check_valid(const char *suffix_url)
{
	struct stat buf;
	bool	ret = false;

	stat(suffix_url, &buf);
	if (S_ISREG(buf.st_mode))
		ret = false;
	else if (S_ISDIR(buf.st_mode))
		ret = true;
	return ret;
}

map<int, string> Response::m_status_description;
bool Response::is_init = false;

// Constructor && Destructor ===========================================

Response::Response() : m_status_code(0), m_content(""), m_openFilesNum(0) {
	if (Response::is_init == false)
		Response::ResponseInit();
}

Response::Response(int status) : m_status_code(0), m_content(""), m_openFilesNum(0) {
	if (Response::is_init == false)
		Response::ResponseInit();
	this->setStatusCode(status);
}

Response::~Response() {
}

// Static Method =======================================================

void Response::ResponseInit() {
	Response::m_status_description[200] = "200 OK";
	Response::m_status_description[201] = "201 Created";
	Response::m_status_description[204] = "204 No Content";
	Response::m_status_description[300] = "300 Multiple Choices";
	Response::m_status_description[301] = "301 Moved Permanently";  // 페이지가 영구적으로 바뀐 것을 알림. get은 그대로고 그 외는 get으로 바뀔수도 안바뀔수도 있음
	Response::m_status_description[302] = "302 Found";  // get은 그대로고 그 외는 get으로 바뀔수도 안바뀔수도 있음
	Response::m_status_description[303] = "303 See Other";  // body를 잃고 메소드가 모두 get이 됨
	Response::m_status_description[307] = "307 Temporary Redirect";  // 리디렉션하는데 메소드 안바꿈
	Response::m_status_description[400] = "400 Bad Request";
	Response::m_status_description[404] = "404 Not Found";
	Response::m_status_description[405] = "405 Method Not Allowed";
	Response::m_status_description[408] = "408 Request Timeout";
	Response::m_status_description[411] = "411 Length Required";
	Response::m_status_description[413] = "413 Request Entity Too Large";
	Response::m_status_description[414] = "414 Request-URI Too Long";
	Response::m_status_description[500] = "500 Internal Server Error";
	Response::m_status_description[502] = "502 Bad Gateway";
	Response::m_status_description[505] = "505 HTTP Version Not Supported";

	Response::is_init = true;
}


// 여기서부터 멤버함수들 ++++++++++++++++++++++++++++++++++++++++++++++++++++

// Private Method  ==============================================


string Response::makeHeaders() {
	string result = "";

	result.append("HTTP/1.1 " + this->m_status_description[this->m_status_code] + "\r\n");
	for (map<string, string>::iterator i = this->m_headers.begin(); i != this->m_headers.end(); i++)
		result.append((*i).first + ": " + (*i).second + "\r\n");
	result.append("\r\n");

	return result;
}

string Response::parseHeader(string& sub_content) {
	size_t i;

	i = sub_content.find("\r\n");  // 첫줄 바운더리 끝 찾기
	sub_content = sub_content.substr(i+2);  // 첫줄 지우기
	i = sub_content.find("\r\n");  // 둘째줄 끝 읽기
	string tmp = sub_content.substr(0, i);  // 둘쨰줄 읽기
	string name, f_name = "";

	i = tmp.find("name=");  // 이름 위치 읽기
	tmp = tmp.substr(i+6); // 이름부터 끝까지 자르기
	i = tmp.find("\"");
	name = tmp.substr(0, i);  // 파일 이름 구하기

	if (tmp.find("filename=") != string::npos) {  // 파일 이름이 있는 경우
		i = tmp.find("filename=");  // 파일 이름 위치 읽기
		tmp = tmp.substr(i+10); // 파일 이름부터 끝까지 자르기
		i = tmp.find("\"");
		f_name = tmp.substr(0, i);  // 파일 이름 구하기
	}
	i = sub_content.find("\r\n\r\n");  // 헤더 끝 위치 찾기
	sub_content = sub_content.substr(i+4);  // 바디 위치부터 시작
	if (f_name != "")
		return name + "_" + f_name;
	return name;
}

string Response::getFileContent(string &sub_content, string boundary) {
	size_t i;

	i = sub_content.find(boundary);  // 바디 끝 찾기
	string body = sub_content.substr(0, i);  // 원하는 파일의 바디 저장
	sub_content = sub_content.substr(i);  // 바디 이후부터 다시 저장
	return body;
}


// 에러시 -1 반환 성공시 0, 잘못된 경로시 1 반환
void Response::serveFile(int fd, intptr_t datalen) {
	string data = "";
	data = this->readFile(fd, datalen);
	close(fd);
	this->setContent(data);
}

int Response::deleteFile(string file_path) {
	if (file_path.find("../") != string::npos)  // 지정 디렉토리 벗어나기 금지
		return -1;
	string full_name = URLDecoding(file_path.c_str());
	std::cout << "Decode file name: " << full_name << "\n";
	return unlink(full_name.c_str());
}


int Response::getFileList(vector<string>& li, const char *dir_path) {
	struct dirent	*file    = NULL;
	DIR				*dir_ptr = NULL;

	// 목록을 읽을 디렉토리명으로 DIR *를 return
	if((dir_ptr = opendir(dir_path)) == NULL)
		return -1;

	// 디렉토리의 처음부터 파일 또는 디렉토리명을 순서대로 한개씩 읽기r.
	while((file = readdir(dir_ptr)) != NULL) {
		li.push_back(file->d_name);
	}
	// open된 directory 정보를 close.

	closedir(dir_ptr);
	return 0;
}

int Response::makeAutoIndex(const char *dir_path) {
	vector<string> li;
	string result = "";
	if (getFileList(li, dir_path) == -1)
		return -1;
	result.append("<ul>\n");
	for (size_t i=2; i<li.size(); ++i) {
		result.append("<li><a href=\"/download/" + li[i] + "\" download>");
		result.append(li[i]);
		result.append("</a>");
		result.append("</li>");
	}
	result.append("\n</ul>\n");
	this->setContent(result);
	return 0;
}


void Response::makeContentError(int status, int fd) {
	int datalen = 100;
	this->setStatusCode(status);
	this->serveFile(fd, datalen);
}

void Response::makeContentFile(int fd) {
	int datalen = 100;
	this->serveFile(fd, datalen);
}


// Public Method ========================================================

// getter ==============================================================

int	Response::getStatusCode() {
	return this->m_status_code;
}
map<int ,string> Response::getStatusDesc() {
	return this->m_status_description;
}
map<string,string> Response::getHeaders() {
	return this->m_headers;
}
string &Response::getContent() {
	return this->m_content;
}

int	Response::getRequestFile(string request_file, string dir_path) {
	struct stat buf;

	if (stat((dir_path + "/" + request_file).c_str(), &buf) < 0)
		return NO_FILE; // NO FILE!!
	if (S_ISREG(buf.st_mode))
		return VALID_REQ_FILE; // 존재하는 파일 요청
	else if (S_ISDIR(buf.st_mode))
		return VALID_REQ_DIR; // 존재하는 디렉토리 요청
	return 2;  // 예외
}

int Response::getFdMode(int fd) {
	if (this->m_fdMode.find(fd) == this->m_fdMode.end()) {
		cerr << "[Error] getFdMode에 존재하지 않는 fd를 입력하였습니다.\n";
		return -1;
	}
	return this->m_fdMode[fd];
}


// setter ==========================================================


void Response::setStatusCode(int code) {
	this->m_status_code = code;
}
void Response::setStatusDesc(int code, string desc) {
	this->m_status_description[code] = desc;
}
void Response::setHeaders(string key, string value) {
	this->m_headers[key] = value;
}
void Response::setContent(string content) {
	this->m_content.clear();
	this->m_content = content;
	this->setHeaders("Content-length", to_string(content.length()));
}
void Response::setLocationBlock(LocationBlock loc) {
	this->m_location = loc;
}

// append  ============================================

// append content를 반복 사용하여 html을 만드는 경우 먼저 호출
void Response::appendHtmlHeader() {
	string result;
	result.append("<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/><title>webserv</title></head>");
	result.append("<body>");
	this->setContent(result);
}

// append content를 반복 사용하여 html을 만드는 경우 마지막에 호출
void Response::appendHtmlFooter() {
	string result;
	result.append("<p>Click <a href=\"/\">here</a> to return home.</p>");
	result.append("</body></html>");
	this->appendContent(result);
}

// 기존 m_content에 append함
void Response::appendContent(string content) {
	this->m_content.append(content);
}


// Make ===============================================================


void Response::makeContent(string content) {
	string result = "";
	result.append("<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/><title>webserv</title></head>");
	result.append("<body>");
	result.append(content);
	result.append("<p>Click <a href=\"/\">here</a> to return home.</p>");
	result.append("</body></html>");

	this->setContent(result);
}


// Response ==========================================================


void Response::cgiResponse(string cgi_result) {
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	this->makeContent(cgi_result);
}

void Response::defaultResponse(int fd) {
	std::cout << "default Response start : " << this->m_location.getRootDir() + "/" + this->m_location.getIndexFile() + " ======== \n";
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	this->makeContentFile(fd);
	std::cout << "default Response end ======== \n";
}

// void Response::uploadResponse(vector<int> fd, string content_type, string content_body) {
// 	cout << "[DEBUG] uploadResponse start\n";
// 	cout << "content_body : " + content_body + "\n";
// 	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
// 	this->makeContent("Upload Success");
// 	cout << "[DEBUG] uploadResponse end\n";
// }

// void Response::downloadResponse(int fd) {
// 	cout << "[DEBUG] downloadResponse start" << endl;
// 	//this->setHeaders("Content-Disposition", "attachment; filename=\"" + file_path + "\"");
// 	//this->serveFile(fd);
// 		//this->makeContent("Download Fail");
// 	cout << "[DEBUG] downloadResponse start" << endl;
// }

void Response::deleteResponse(string file_path) {
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	if (deleteFile(file_path) == 0)
		this->makeContent("Delete Success");
	else
		this->makeContent("Delete Fail");
}

void Response::autoIndexResponse(const char *dir_path) {
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	if (this->makeAutoIndex(dir_path) == -1)
		this->makeContent("Auto Index Fail");
}

void Response::errorResponse(int fd, int status) {
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	this->makeContentError(status, fd);
}

void Response::redirectResponse(int status, string url) {
	this->setStatusCode(status);
	this->setHeaders("Location", url);
	this->makeContent("Redirection Success");
}

void Response::fileResponse(int fd) {
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	this->makeContentFile(fd);
}


// 최종 응답 만들기 메소드
string Response::getHttpResponse() {
	this->setHeaders("Content-length", to_string(this->m_content.length()));
	this->setHeaders("Content-Type", "text/html; charset=UTF-8");
	string result = this->makeHeaders() + this->getContent();
	return result;
}

// File ====================================================================

int Response::openFile(string path, int flag) {
	int fd;
	fd =  open(path.c_str(), flag, 0644);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	this->m_fdMode[fd] = flag;
	++this->m_openFilesNum;
	return fd;
}

vector<int> Response::openFiles(vector<pair<string, string> > in, int flag) {
	vector<int> out;
	int fd;
	for (size_t i=0; i<in.size(); ++i) {
		fd = this->openFile(in[i].first, flag);
		out.push_back(fd);
	}
	return out;
}

// 읽은 파일 스트링으로 반환 다 읽으면 "" 반환
string Response::read_fd(int fd, intptr_t datalen) {
	char *buf = (char*)malloc(sizeof(char) * datalen);
	if (buf == 0) {
		this->setStatusCode(500);
		std::cerr << "Read Error!\n";
		return "";
	}
	ssize_t ret = read(fd, buf, datalen);
	if (ret == -1) {
		this->setStatusCode(500);
		std::cerr << "Read Error!\n";
		free(buf);
		return "";
	}
	string str(buf, ret);
	free(buf);
	return str;
}

// write 결과 값 반환
ssize_t Response::write_fd(int fd, intptr_t datalen) {
	(void)datalen;
	ssize_t size = write(fd, this->m_content.c_str(), this->m_content.size());
	if (size == -1) {
		this->setStatusCode(500);
		std::cerr << "Write Error!\n";
	}
	return size;
}

// readFile 완성시 return true
bool Response::readFile(int fd, intptr_t datalen) {
	string ret = this->read_fd(fd, datalen);
	this->appendContent(ret);
	if (ret.size() == (size_t)datalen) {
		close(fd); // 사용이 끝난 정적파일 fd는 닫아준다.
		return true;
	}
	return false;
}

// writeFile 완성시 return true
bool Response::writeFile(int fd, intptr_t datalen) {
	ssize_t write_len = this->write_fd(fd, datalen);
	// write 반환값의 누적합이 req의 content-length와 일치 시에 완료로 정의한다.
	if (write_len == -1) { // 에러 발생
		close(fd);
		//this->appendHtmlFooter();
		this->appendHtmlHeader();
		this->appendContent("Error: writeFile");
		this->appendHtmlFooter();
		return true;
	}
	else if (this->m_content.size() == (size_t)write_len) {  // 완성
		close(fd); // 사용이 끝난 정적파일 fd는 닫아준다.
		this->appendHtmlHeader();
		this->appendContent("writeFile success");
		this->appendHtmlFooter();
		return true;
	}

	//=========================================================================
	// content를 한글자씩 보내다가 마지막 한글자가 content에 남아있게 된다.
	this->setContent(this->getContent().substr(write_len));
	//=========================================================================
	return false;
}

map<string, string> Response::parseFormData(string content_type, string content_body, string path) {
	size_t i = content_type.find("boundary=");
	map<string, string> ret;
	if (i == string::npos)
		return ret;
	string boundary = content_type.substr(i+9);
	string sub_content = content_body;
	string file_name;
	string file_body;

	while (sub_content.find("--" + boundary + "--") != 0) {
		file_name = this->parseHeader(sub_content);
		file_body = this->getFileContent(sub_content, "--" + boundary);
		if (file_name.find("../") != string::npos)  // 지정 디렉토리 벗어나기 금지
			continue;
		ret[path + "/" + file_name] = file_body;
	}
	return ret;
}

// map<opened_fd, content> 저장해서 반환
map<int, string> Response::formFilesOpen(map<string, string> m) {
	map<int, string> ret;
	map<string, string>::iterator iter = m.begin();
	while (iter != m.end()) {
		ret[this->openFile(iter->first, O_WRONLY)] = iter->second;
		++iter;
	}
	return ret;
}

/*
	여기부터 비 멤버함수  ======================================================
*/

// 16진수 문자값을 10진수 문자값으로 변환
char hex2int(char input) {
	// 숫자
	if (input >= '0' && input <= '9') {
		return input - '0';
	}
	// 대문자
	else if (input >= 'A' && input <= 'Z') {
		return input - 'A' + 10;
	}
	// 소문자
	else if (input >= 'a' && input <= 'z') {
		return input - 'a' + 10;
	}
	return 0;
}

// 10진수 문자값을 16진수 문자값으로 변환
char int2hex(char input) {
	char hex[17] = "0123456789abcdef";
	return hex[0x0f & input];
}

// URL 인코딩 한다.
string URLEncoding(const char *pIn) {
	if (pIn == 0) {
		return 0;
	}
	string result;
	char temp = 0;
	while (*pIn != 0) {
		temp = *pIn;
		// ASCII 대소문자와 숫자인 경우만 그대로 저장
		if (std::isprint(temp) != 0) {
			result += temp;
		}
		// % 와 2자리 16진수 문자값으로 만들어 저장
		else {
			result += "%";
			result += int2hex(temp >> 4);
			result += int2hex(temp);
		}
		pIn++;
	}
	return result;
}

// URL 디코딩 한다.
string URLDecoding(const char *pIn) {
	if (pIn == 0) {
		return 0;
	}
	string result;
	char temp = 0;
	while (*pIn != 0) {
		temp = *pIn;
		// % 로 시작되면 % 빼고 2자리 16진수 문자값을 10진수 문자값으로 변경하여 저장
		if (temp == '%') {
			char buf = 0;
			pIn++;
			temp = *pIn;
			buf = hex2int(temp);

			pIn++;
			temp = *pIn;
			buf = buf << 4 | hex2int(temp);

			result += buf;
		}
		// 출력 가능한 경우 그대로 저장
		else if (std::isprint(temp) != 0) {
			result += temp;
		}
		pIn++;
	}
	return result;
}
