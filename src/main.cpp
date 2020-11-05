#include <iostream>
#include "isabot.h"

using namespace std;

int main(int argc, char **argv)
{
    try
    {
        ISAbot bot(argc, argv);
    }
    catch (CustomException e)
    {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}