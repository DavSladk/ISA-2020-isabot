#include "Options.h"

Options::Options(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

bool Options::helpIsSet()
{
    return this->helpFlag;
}

bool Options::verboseIsSet()
{
    return this->verboseFlag;
}

bool Options::tokenIsSet()
{
    return this->tokenFlag;
}

std::string Options::getToken()
{
    return this->token;
}

void Options::parseOptions()
{
    for (int i = 1; i < this->argc; i++)
    {
        if ( strcmp(argv[i], "-h") == MATCH || strcmp(argv[i], "--help") == MATCH)
        {
            helpFlag = true;
        }
        else if ( strcmp(argv[i], "-v") == MATCH || strcmp(argv[i], "--verbose") == MATCH)
        {
            verboseFlag = true;
        }
        else if ( strcmp(argv[i], "-t") == MATCH)
        {
            if ( argc == i )
            {
                throw new CustomException("Missing token after -t option.", MISSING_TOKEN);
            }
            tokenFlag = true;
            token = argv[++i];
            i++;
        }
        else
        {
            std::string msg = "Unknow parametr" + std::string(argv[i]) + "on position" + std::to_string(i);
            throw new CustomException(msg, OPTION_UNKNOW);
        }
        
    }

    if ( token == "")
    {
        throw new CustomException("Token can not be empty.", MISSING_TOKEN);
    }
}