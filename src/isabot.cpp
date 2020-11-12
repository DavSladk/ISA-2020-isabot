#include "isabot.h"

ISAbot::ISAbot(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

ISAbot::~ISAbot()
{
    delete this->opt;
}

void ISAbot::printHelp()
{
    std::cout << "I am very helpful help." << std::endl;
}

void ISAbot::setUpOptions()
{
    this->opt = new Options(argc, argv);
    opt->parseOptions();
}

void ISAbot::checkForHelp()
{
    if(
        opt->helpIsSet() ||
        ( !opt->tokenIsSet() && !opt->verboseIsSet() )
    )
    {
        printHelp();
    }
}

void ISAbot::checkForToken()
{
    if ( !opt->tokenIsSet() )
    {
        throw CustomException("Option -t must be specified.", OPTION_MISSING);
    }
    
    if ( opt->getToken().empty() )
    {
        throw CustomException("Token can not be empty.", MISSING_TOKEN);
    }
}
void ISAbot::run()
{
    setUpOptions();

    checkForHelp();
    checkForToken();
    SecureSocket soc(opt->getToken());
    
    soc.SetUp();
    soc.SendRequestForGuilds();
    soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.ParseOutGuildID();

    soc.SetUp();
    soc.SendRequestForGuildChannels();
    soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.ParseOutChannelID();

    soc.SetUp();
    soc.SendRequestForLastMessage();
    soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.ParseOutLastMessageID();

    soc.SetUp();
    soc.SendRequestForLastMessages();
    soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();

}