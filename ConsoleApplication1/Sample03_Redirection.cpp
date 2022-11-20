#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
int main()
{
	int fd;
	const int e = /*_Check_return_wat_ _ACRTIMP errno_t __cdecl */_sopen_s
	( /*_Out_  int       * _FileHandle    */&fd
	, /*_In_z_ char const* _FileName      */__FILE__
	, /*_In_   int         _OpenFlag      */_O_RDONLY | _O_TEXT
	, /*_In_   int         _ShareFlag     */_SH_DENYWR
	, /*_In_   int         _PermissionMode*/_S_IREAD
	);
	_close(0);
	const auto new_fd = _dup(fd);
	_close(fd);
	char buf[256];
	if (fgets(buf, sizeof buf, stdin))
		fputs(buf, stdout);
}
