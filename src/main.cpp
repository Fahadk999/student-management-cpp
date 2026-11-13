#include "Manager.hpp"

int main () {
    //Manager newManager;

    //newManager.Run();
    unsigned short int bfr;
    auto setUint = [] (
            unsigned short int& buffer,
            const short int& range,
            const char* msg = "") {
        bool valid = true;
        do {
            std::cout << msg;
            if(!(std::cin >> buffer)) {
                buffer = 0;
                std::cin.clear();
                std::cin.ignore();
                valid = false;
            } else { valid = true; }
        } while (buffer > range || buffer < 0 || !valid);
    };
    setUint(bfr, 100, "Enter: ");
    std::cout << bfr << std::endl;
    return 0;
}
