#include "utils.h"

int Utils::parseArgs(int argc, char** argv) {
    int i = 0;
    while (i < argc) {
        std::cout << argv[i] << std::endl;
        i++;
    }
    return 0;
}
