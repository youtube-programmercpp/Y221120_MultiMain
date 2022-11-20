#undef main
#include <Windows.h>
#include <iostream>
void f(const IMAGE_DOS_HEADER& imageDosHeader)
{
	const auto & d = *PIMAGE_EXPORT_DIRECTORY(&LPCSTR(&imageDosHeader)[PIMAGE_NT_HEADERS(&LPCSTR(&imageDosHeader)[imageDosHeader.e_lfanew])->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress]);
	const auto AddressOfFunctions = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfFunctions]);
	const auto AddressOfNames     = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfNames    ]);
	for (DWORD i = 0; i < d.NumberOfNames; ++i) {
		const auto Address = &LPCSTR(&imageDosHeader)[AddressOfFunctions[i]];
		const auto Name    = &LPCSTR(&imageDosHeader)[AddressOfNames    [i]];
	}
}
extern "C" extern const IMAGE_DOS_HEADER __ImageBase;
int main()
{
	f(__ImageBase);
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
