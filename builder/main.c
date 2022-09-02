#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

/*
const LCID lid = GetUserDefaultLCID();
WCHAR name[LOCALE_NAME_MAX_LENGTH + 1];
LCIDToLocaleName(lid, name, LOCALE_NAME_MAX_LENGTH, LOCALE_ALLOW_NEUTRAL_NAMES);
*/

static const uint32_t ver = 0x01000001;

void usage(void)
{
	wprintf(L"builder.exe <input file> <output file> <password>\n");
	ExitProcess(1);
}

int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT); // to print different languages (unicode)

	const wchar_t* infile = argv[1];
	const wchar_t* outfile = argv[2];
	const wchar_t* password = argv[3];

	const uint8_t ver1 = (ver >> 24) & 0xff;
	const uint8_t ver2 = (ver >> 16) & 0xff;
	const uint8_t ver3 = (ver >> 8) & 0xff;
	const uint8_t ver4 = ver & 0xff;

	wprintf(L"Builder v %d.%d.%d.%d\n", ver1, ver2, ver3, ver4);

	if (argc < 4)
		usage();

	const HANDLE h_in = CreateFileW(infile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	const HANDLE h_out = CreateFileW(outfile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h_in == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Failed to open input file\n");
		return 1;
	}

	if (h_out == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Failed to create output file\n");
		return 1;
	}

	CloseHandle(h_in);
	CloseHandle(h_out);

	return 0;
}
