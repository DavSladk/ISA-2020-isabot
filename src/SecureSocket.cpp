#include "SecureSocket.h"

SecureSocket::SecureSocket(std::string token)
{
    this->token = token;
}

void SecureSocket::SetUp()
{
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    
    method = TLS_client_method();
    if ( method == NULL )
    {
        throw CustomException("Obtaining TLS method failed.", TEMP);
    }

    ctx = SSL_CTX_new(method);
    if ( ctx == NULL )
    {
        throw CustomException("Obtaining CTX failed.", TEMP);
    }

    bio = BIO_new_ssl_connect(ctx);
    if ( bio == NULL)
    {
        throw CustomException("Obtaining BIO failed.", TEMP);
    }

    BIO_get_ssl(bio, &ssl);

    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    BIO_set_conn_hostname(bio, "discord.com:https");

    if ( BIO_do_connect(bio) < 0)
    {
        throw CustomException("Connecting to server failed.", TEMP);
    }

}

void SecureSocket::SendRequestForGuilds()
{
    std::string guildRequest = "GET /api/users/@me/guilds HTTP/1.1\nHost: discord.com\nConnection: close\nAuthorization: Bot " + token + "\n\n";
    std::cout << guildRequest << std::endl;
    if( BIO_puts(bio, guildRequest.c_str()) < 1 )
    {
        throw CustomException("Sending request for list of guilds failed.", TEMP);
    }
}

void SecureSocket::ReceiveResponse()
{
    response.clear();
    while (true)
    {
        memset(responseBuffer, '\0', BUFFER_SIZE);
        if ( BIO_read(bio, responseBuffer, BUFFER_SIZE) <= 0 )
        {
            break;
        }
        response.append(responseBuffer);
    }
    std::cout << response << std::endl;
}

void SecureSocket::CheckResponseForOK()
{
    if ( response.compare(9,3,"200") != 0 )
    {
        throw CustomException("Respnse did not returned with code 200.", TEMP);
    }
}

void SecureSocket::ParseOutGuildID()
{
    std::string::size_type pos;
    pos = response.find(idPrefix, 0);
    if ( pos == std::string::npos )
    {
        throw CustomException("Response does not have guild id.", TEMP);
    }
    guildID = response.substr(pos + idPrefix.size(), ID_SIZE);
    std::cout << guildID << std::endl;
}

void SecureSocket::SendRequestForGuildChannels()
{
    std::string channelsRequest = "GET /api/guilds/" + guildID + "/channels HTTP/1.1\nHost: discord.com\nConnection: close\nAuthorization: Bot " + token + "\n\n";
    std::cout << channelsRequest <<  std::endl;
    if( BIO_puts(bio, channelsRequest.c_str()) < 1 )
    {
        throw CustomException("Sending request for list of guild channels.", TEMP);
    }
}

void SecureSocket::ParseOutChannelID()
{
    std::string::size_type pos;
    std::string tmp;

    pos = response.find(channelName, 0);
    tmp = response.substr(0, pos);
    pos = tmp.rfind(idPrefix, tmp.size());
    channelID = tmp.substr(pos + idPrefix.size(), ID_SIZE);
    std::cout << channelID << std::endl;
}

void SecureSocket::SendRequestForLastMessage()
{
    std::string channelRequest = "GET /api/channels/" + channelID + "/messages?limit=1 HTTP/1.1\nHost: discord.com\nConnection: close\nAuthorization: Bot " + token + "\n\n";
    std::cout << channelRequest <<  std::endl;
    if( BIO_puts(bio, channelRequest.c_str()) < 1 )
    {
        throw CustomException("Sending request for list of guild channels.", TEMP);
    }
}

void SecureSocket::ParseOutLastMessageID()
{
    std::string::size_type pos;

    pos = response.find(idPrefix, 0);
    lastMessageID = response.substr(pos + idPrefix.size(), ID_SIZE);
    std::cout << lastMessageID << std::endl;
}

void SecureSocket::SendRequestForLastMessages()
{
    std::string messagesRequest = "GET /api/channels/" + channelID + "/messages?after=" + lastMessageID + " HTTP/1.1\nHost: discord.com\nConnection: close\nAuthorization: Bot " + token + "\n\n";
    std::cout << messagesRequest <<  std::endl;
    if( BIO_puts(bio, messagesRequest.c_str()) < 1 )
    {
        throw CustomException("Sending request for list of guild channels.", TEMP);
    }
}

SecureSocket::~SecureSocket()
{

}

void SecureSocket::clean()
{
    SSL_CTX_free(ctx);
    BIO_free_all(bio);
}