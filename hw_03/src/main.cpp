#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>
#include "HuffmanArchiver.h"

int main(int argc, char **argv) {
    bool error = false;
    if (argc > 5) {
        const char* infile = nullptr;
        const char* outfile = nullptr;
        if (!strcmp(argv[2], "-f") || !strcmp(argv[2], "--file")) {
            infile = argv[3];
        } else {
            error = true;
        }
        if (!strcmp(argv[4], "-o") || !strcmp(argv[4], "--output")) {
            outfile = argv[5];
        } else {
            error = true;
        }
        HuffmanArchiver HuffArch(infile, outfile);
        if (!strcmp(argv[1], "-c")) {
            try {
                HuffArch.archiving();
            } catch (HuffException &e) {
                std::cout << e.get() << std::endl;
            }
            HuffArch.get_stat();
        }
        if (!strcmp(argv[1], "-u")) {
            try {
                HuffArch.unzipping();
            } catch (HuffException &e) {
                std::cout << e.get() << std::endl;
            }
            HuffArch.get_stat();
        }

        if ((strcmp(argv[1], "-c") != 0) && (strcmp(argv[1], "-u") != 0)) {
            error = true;
        }

    } else {
        error = true;
    }

    if (error) {
        std::cout << "bad input parameters";
    }
    return 0;
}