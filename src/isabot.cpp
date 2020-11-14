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
    SecureSocket soc(opt->getToken(), opt->verboseIsSet());
    
    soc.SetUp();
    soc.SendRequestForGuilds();
    soc.response = soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.ParseOutGuildID();

    soc.SetUp();
    soc.SendRequestForGuildChannels();
    soc.response = soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.ParseOutChannelID();

    soc.SetUp();
    soc.SendRequestForLastMessage();
    soc.response = soc.ReceiveResponse();
    soc.clean();
    soc.CheckResponseForOK();
    soc.lastMessageID = soc.ParseOutLastMessageID();

    //main loop
    while (true)
    {
        soc.SetUp();
        soc.SendRequestForLastMessages();
        soc.response = soc.ReceiveResponse();
        soc.clean();
        soc.CheckResponseForOK();

        if ( soc.CheckForNoNewMessages() )
        {
            ;
        }
        else
        {
            soc.EchoMessages();
        }
        std::this_thread::sleep_for (std::chrono::seconds(5));
    }

}