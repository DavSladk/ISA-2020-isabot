#include <iostream>
#include "Options.h"
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
        std::cout << e.Message() << std::endl;
    }
    return 0;
}