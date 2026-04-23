#include <windows.h>

int main() {
    // Parameters: Parent handle, Message text, Title bar text, Flags
    MessageBoxA(NULL, "Hello, World!", "Test Application3", MB_OK | MB_ICONINFORMATION);
    return 0;
}
