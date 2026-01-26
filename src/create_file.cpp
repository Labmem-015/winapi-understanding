#include <iostream>
#include <Windows.h>

int createFile() {
	LPCSTR filename = R"(C:\created_file.txt)";
	HANDLE hFile = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Bad file handle" << std::endl;
		return -1;
	}

	char buffer[] = "Hello, World!";

	DWORD written = 0;
	BOOL error_flag = WriteFile(hFile, buffer, sizeof(buffer), &written, NULL);
	if (error_flag == FALSE) {
		std::cout << "Can't write data" << std::endl;
		return -1;
	}
	else if (sizeof(buffer) != written) {
		std::cout << "Not all of data was written" << std::endl;
		return -1;
	}

	std::cout << "Successfully wrote " << written << " bytes to the file: " << filename << std::endl;
	std::cout << "Press 'Enter' to exit" << std::endl;
	std::cin.get();
	return 0;
}

int main(int argc, char* argv[]) {
	auto res = createFile();

	return res;
}