#include <stdio.h>
int main()
{
	for (;;) {
		char buf[256];
		if (fgets(buf, sizeof buf, stdin))
			fputs(buf, stdout);
		else
			break;
	}
	return 0;
}
