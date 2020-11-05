#include "isabot.h"

ISAbot::ISAbot(int argc, char** argv)
{
    this->opt = new Options(argc, argv);
    this->opt->printOptionsValue();
}

ISAbot::~ISAbot()
{
    delete this->opt;
}