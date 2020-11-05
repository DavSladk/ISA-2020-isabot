#ifndef XSLADK07_OPTIONS_H
#define XSLADK07_OPTIONS_H

#include <string>
#include <iostream>

#include <cstring>

#include "CustomException.h"

class Options
{
    public:
        Options(int argc, char** argv);

        bool helpIsSet();
        bool verboseIsSet();
        bool tokenIsSet();
        std::string getToken();

        void printOptionsValue();

    private:
        bool helpFlag = false;
        bool verboseFlag = false;
        bool tokenFlag = false;
        std::string token = "";

        int argc;
        char** argv;

        void parseOptions();

        const int MATCH = 0;
};

#endif //XSLADK07_OPTIONS_H