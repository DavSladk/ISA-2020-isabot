#ifndef XSLADK07_ISABOT_H
#define XSLADK07_ISABOT_H

#include "Options.h"
#include "CustomException.h"

class ISAbot
{
    public:
        ISAbot(int argc, char** argv);
        ~ISAbot();

        void printHelp();
        void run();

    private:
        Options *opt;
        int argc;
        char** argv;

        void checkForHelp();
        void setUpOptions();
        void checkForToken();
};

#endif //XSLADK07_ISABOT_H