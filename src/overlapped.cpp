void write_to_file(OVERLAPPED* overlapped) {

}

void read_from_file(OVERLAPPED* overlapped) {

}

int main(int argc, char* argv[]) {
    HANDLE hFile = CreateFile(
        L"test_overlapped_io.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_FLAG_OVERLAPPED,
        NULL
    );
    OVERLAPPED overlapped = { 0 };
    BYTE buffer[4096];
    DWORD bytesRead;

    overlapped.hEvent = CreateEventA(NULL, TRUE, FALSE, "Test Event");

    return EXIT_SUCCESS;
}