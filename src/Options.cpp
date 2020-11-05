#include "Options.h"

Options::Options(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
    parseOptions();
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
    if ( argc == 1 )
    {
        helpFlag = true;
        return;
    }

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
                throw CustomException("Missing token after -t option.", MISSING_TOKEN);
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
        throw CustomException("Token can not be empty.", MISSING_TOKEN);
    }
}

void Options::printOptionsValue()
{
    std::cout << "-h/--help : " << helpFlag << std::endl;
    std::cout << "-v/--verbose : " << verboseFlag << std::endl;
    std::cout << "-t : " << tokenFlag << " - \"" << token << "\"" << std::endl;
}