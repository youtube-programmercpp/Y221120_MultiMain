#include <stdio.h>
#define	TEST  //値を定義するのではなく #define しているか否か
//preprocessor プリプロセッサ
int main()
{
#ifdef TEST//これは #define されてる？
	puts("TESTが#defineされている場合の実装");
#else
	puts("TESTが#defineされていない場合の実装");
#endif
}
