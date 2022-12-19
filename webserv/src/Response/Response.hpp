#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>

# include <string>
# include <map>
# include <vector>
# include <fstream>
# include <cctype>
# include <iostream>
# include <utility>

# include "../Config/Config.hpp"

# define NO_FILE -1
# define VALID_REQ_FILE 1
# define VALID_REQ_DIR 0

# define BUFF_SIZE 1024

using namespace std;

class Response {
private:
	static map<int, string>	m_status_description;
	static bool				is_init;
	int						m_status_code;
	map<string, string>		m_headers;
	map<int, int>			m_fdMode;
	string					m_content;
	LocationBlock			m_location;
	int						m_openFilesNum;

	string					makeHeaders();
	string					parseHeader(string& content_type);
	string					getFileContent(string& content_type, string last_boundary);

	void					serveFile(int fd, intptr_t datalen);
	int						deleteFile(string file_path);

	int						getFileList(vector<string>& li, const char *dir_path);
	int						makeAutoIndex(const char *dir_path);

	void					makeContentError(int status, int fd);
	void					makeContentFile(int fd);

public:
	Response ();
	Response (int status);
	~Response ();
	static void				ResponseInit(); // Response 클래스를 초기화하는 한번만 실행 가능함수

// Getter
	int						getStatusCode();
	map<int ,string>		getStatusDesc();
	map<string,string>		getHeaders();
	string					&getContent();
	int						getRequestFile(string request_file, string dir_path);
	int						getFdMode(int fd);

// Setter
	void					setStatusCode(int code);
	void					setStatusDesc(int code, string desc);
	void					setHeaders(string key, string value);
	void					setContent(string content);
	void					setLocationBlock(LocationBlock loc);

	void					appendHtmlHeader();
	void					appendHtmlFooter();
	void					appendContent(string content);

// Make
	void					makeContent(string content);

// Response
	void					cgiResponse(string cgi_result);  // cgi 결과를 요청하는 경우의 응답처리
	void					defaultResponse(int fd);
//	void					uploadResponse(vector<int> fd, string content_type, string content_body);  // 파일 업로드 경우의 응답처리
//	void					downloadResponse(int fd);  // 파일 다운로드 응답처리
	void					deleteResponse(string file_path);  // 파일 삭제 응답처리
	void					autoIndexResponse(const char *dir_path);
	void					errorResponse(int fd, int status);
	void					redirectResponse(int status, string url);
	void					fileResponse(int fd);

	string					getHttpResponse();

// File

	int						openFile(string path, int flag);
	vector<int>				openFiles(vector<pair<string, string> > in, int flag);
	string					read_fd(int fd, intptr_t datalen);
	ssize_t					write_fd(int fd, intptr_t datalen);

	bool					readFile(int fd, intptr_t datalen);
	bool					writeFile(int fd, intptr_t datalen);

// 새로 만드는 중인 메소드
	map<string, string>		parseFormData(string content_type, string content_body, string path);  // m_content로 받을 데이터를 파싱해서 파일로 저장하는 함수
	map<int, string>		formFilesOpen(map<string, string> m);
};

// encode와 decode관련 비멤버 함수
char	hex2int(char input);
char	int2hex(char input);
string	URLEncoding(const char *pIn);
string	URLDecoding(const char *pIn);
bool	is_directory(const char *suffix_url);
#endif
