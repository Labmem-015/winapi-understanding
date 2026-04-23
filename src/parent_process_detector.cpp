DWORD GetParentProcessId() {
    // Get the current process ID
    DWORD currentProcessId = GetCurrentProcessId();
    DWORD parentProcessId = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateToolhelp32Snapshot failed. Error: " << GetLastError() << std::endl;
        return 0;
    }

    PROCESSENTRY32 pe32;
    ZeroMemory(&pe32, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);

    // Enumerate processes
    if (Process32First(hSnapshot, &pe32)) {
        do {
            // Find the current process entry
            if (pe32.th32ProcessID == currentProcessId) {
                parentProcessId = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    } else {
        std::cerr << "Process32First failed. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hSnapshot);
    return parentProcessId;
}

int main() {
    DWORD ppid = GetParentProcessId();
    if (ppid != 0) {
        std::cout << "Current Process ID: " << GetCurrentProcessId() << std::endl;
        std::cout << "Parent Process ID: " << ppid << std::endl;
    } else {
        std::cout << "Could not determine the parent process ID." << std::endl;
    }
    std::cout << "Press enter to exit" << std::endl;
    std::cin.get();
    return 0;
}
