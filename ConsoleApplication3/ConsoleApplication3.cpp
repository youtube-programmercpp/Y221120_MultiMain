#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#undef main
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

void f(const IMAGE_DOS_HEADER& imageDosHeader)
{
    const auto &ntHeaders = *PIMAGE_NT_HEADERS ( & LPCSTR(&imageDosHeader)[imageDosHeader.e_lfanew]);
    const auto &dd = ntHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (dd.Size) {
    const auto VirtualAddress = dd.VirtualAddress;
	const auto & d = *PIMAGE_EXPORT_DIRECTORY(&LPCSTR(&imageDosHeader)[VirtualAddress]);

	const auto AddressOfFunctions = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfFunctions]);
	const auto AddressOfNames     = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfNames    ]);
    const auto AddressOfNameOrdinals = reinterpret_cast<const WORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfNameOrdinals]);
    for (DWORD i = 0; i < d.NumberOfNames; ++i) {
		const auto Address = &LPCSTR(&imageDosHeader)[AddressOfFunctions[AddressOfNameOrdinals[i]]];
		const auto Name    = &LPCSTR(&imageDosHeader)[AddressOfNames    [i]];
        OutputDebugStringA(Name);
        OutputDebugStringA("\n");
        (*FARPROC(Address))();//関数を呼び出す
	}
    }
}


//本物の main
int main()
{
    std::cout << "Hello World!\n";
#if 1
    const auto fd = _open("input.txt", _O_RDONLY | _O_TEXT);
    if (fd != -1) {
        _close(_fileno(stdin));
        _dup(fd);
        _close(fd);
        const auto hModule = GetModuleHandleW(nullptr);
        f(*PIMAGE_DOS_HEADER(hModule));
    }
#else
    Test01();//Test01.cpp の main 関数を呼び出す
    Test02();//Test02.cpp の main 関数を呼び出す
#endif
}
