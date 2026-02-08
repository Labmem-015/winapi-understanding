#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

int main(void) {
	try {
		std::cout << "Welcome to ProcessSpawner!" << std::endl;

		std::wstring input;
		std::wstring filename;
		std::wstring arguments;
		BOOL b_inherit_handles = TRUE;
		DWORD dw_creation_flags = CREATE_NO_WINDOW;
		LPCWSTR lp_current_directory = NULL;
		bool b_set_current_directory = false;

		STARTUPINFOW startup_info;
		PROCESS_INFORMATION process_info;
		ZeroMemory(&startup_info, sizeof(startup_info));
		startup_info.cb = sizeof(startup_info);
		ZeroMemory(&process_info, sizeof(process_info));

		do {
			std::cout << "\nEnter 'q' to exit. Enter 'c' to create process in new console.\n\
	Enter 'n' to create process with no window." << std::endl;

			std::getline(std::wcin, input);
			if (input != L"c" and input != L"n") continue;

			if (input == L"c") {
				dw_creation_flags = CREATE_NEW_CONSOLE;
			}
			else {
				dw_creation_flags = CREATE_NO_WINDOW;
			}

			std::cout << "Enter filepath: ";
			std::getline(std::wcin, filename);

			std::cout << "Enter args: ";
			std::getline(std::wcin, arguments);

			if (!std::filesystem::exists(std::filesystem::path{ filename })) {
				std::cout << "File is not found" << std::endl;
				continue;
			}

			std::wcout << L"Creating process from entered data: " << filename << " " << arguments << std::endl;

			LPCWSTR app_name = filename.c_str();
			std::vector<WCHAR> app_arg(arguments.begin(), arguments.end());
			//LPWSTR app_arg = &arguments[0];/*new WCHAR[arguments.size()];
			//wcscpy_s(app_arg, arguments.size(), arguments.c_str());*/

			BOOL result = CreateProcessW(app_name, app_arg.data(), NULL, NULL, FALSE, dw_creation_flags, NULL, lp_current_directory, &startup_info, &process_info);
			if (result) {
				std::wcout << L"Started process ID: " << process_info.dwProcessId << std::endl;
			}
			else {
				std::cout << GetLastErrorAsString() << std::endl;
			}
			std::cout << "Created process status: " << result << std::endl;


		} while (input != L"q");

	}
	catch (const std::exception& e) {
		std::cout << "Last error is: " << GetLastError() << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}