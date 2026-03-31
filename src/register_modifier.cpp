#include <thread>
#include <winreg.h>
int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
 
    for (int i = 0; i < 3600; ++i) {
        // read a value from an app configuration stored in the registry
        const uint32_t driver_database_version = wil::reg::get_value_dword(HKEY_LOCAL_MACHINE, LR"(SYSTEM\DriverDatabase)", L"Version");
        
        std::cout << "Iter " << i << ". Version is: 0x" << std::hex << driver_database_version << " (" << std::dec << driver_database_version << ")" << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return EXIT_SUCCESS;
}
