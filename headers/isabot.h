#ifndef XSLADK07_ISABOT_H
#define XSLADK07_ISABOT_H

#include "Options.h"

class ISAbot
{
    public:
        ISAbot(int argc, char** argv);
        ~ISAbot();

    private:
        Options *opt;
};

#endif //XSLADK07_ISABOT_H