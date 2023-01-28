#include <stdio.h>

int main()
{
	bool fileflag;

	if (file_exist())
		fileflag = true;
	else
		fileflag = false;


	if (method == GET)
	{
		if (!fileflag)
			return 404;

		if (is_dir(file))
			return 200 and file;
		else
			return 200 and index file;
	}
	else if (method == POST)
	{
		if (fileflag)
		{
			if (파일명 존재)
		}
		else
		{

		}
	}
	else if (method == DELETE)
	{
		if (!fileflag)
			return 404;
		else
			return some_status and delete file;
		// delete의 반환값은? -> 아마 없을듯 => 홈페이지나 오토인덱스로 redirect?
	}
}

int makeResponse(file)
{
	if (cgi_flag)
	{
		return cgi(file);
	}
}