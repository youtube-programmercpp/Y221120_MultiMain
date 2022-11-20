#include <stdio.h>
#if TEST == 1
#	define	MESSAGE_TEXT	"TEST は 1 です。"
#elif TEST == 2
#	define	MESSAGE_TEXT	"TEST は 2 です。"
#elif TEST == 3
#	define	MESSAGE_TEXT	"TEST は 3 です。"
#else
#	define	MESSAGE_TEXT	"TEST は 1～3 以外の値です。"
#endif
int main()
{
	puts(MESSAGE_TEXT);
}
