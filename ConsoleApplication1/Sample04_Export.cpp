#include <Windows.h>
#include <iostream>
void f(const IMAGE_DOS_HEADER& imageDosHeader)
{
	const auto &dd = PIMAGE_NT_HEADERS(&LPCSTR(&imageDosHeader)[imageDosHeader.e_lfanew])->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	if (dd.Size) {
	const auto & d = *PIMAGE_EXPORT_DIRECTORY(&LPCSTR(&imageDosHeader)[dd.VirtualAddress]);
	const auto AddressOfFunctions = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfFunctions]);
	const auto AddressOfNames     = reinterpret_cast<const DWORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfNames    ]);
	const auto AddressOfNameOrdinals = reinterpret_cast<const WORD*>(&LPCSTR(&imageDosHeader)[d.AddressOfNameOrdinals]);
	for (DWORD i = 0; i < d.NumberOfNames; ++i) {
		const auto Address = &LPCSTR(&imageDosHeader)[AddressOfFunctions[AddressOfNameOrdinals[i]]];
		const auto Name    = &LPCSTR(&imageDosHeader)[AddressOfNames    [i]];
		std::cout << static_cast<const void*>(Address) << '\t' << Name << '\n';
	}
	}
}
extern "C" void __declspec(dllexport) test()
{
}
extern "C" extern const IMAGE_DOS_HEADER __ImageBase;
int main()
{
#if 0
	if (const auto pfn = GetProcAddress(GetModuleHandleW(nullptr), "test"))
		(*pfn)();
#else
	f(__ImageBase);
#endif
}
