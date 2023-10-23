#include "Utility.h"
#include "ComPointer.h"
#include <d3dcompiler.h>
#include <codecvt>

bool Failed(HRESULT result) {

    if (FAILED(result)) {
        LPTSTR buffer;

        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)result, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);
        MessageBox(nullptr, buffer, L"ERROR", MB_OK | MB_ICONERROR);
        LocalFree(buffer);
        return true;
    }
    return false;
}

bool IsFlagSet(unsigned int flag, unsigned int mask) {

    return (flag & mask) != 0;
}



