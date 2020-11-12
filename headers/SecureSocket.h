#ifndef XSLADK07_SECURESOCKET_H
#define XSLADK07_SECURESOCKET_H

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <iostream>
#include <cstring>

#include "CustomException.h"

class SecureSocket
{
    public:
        void SetUp();
        SecureSocket(std::string token);
        void SendRequestForGuilds();
        void ReceiveResponse();
        void CheckResponseForOK();
        void ParseOutGuildID();
        void SendRequestForGuildChannels();
        void clean();
        void ParseOutChannelID();
        void SendRequestForLastMessage();
        void ParseOutLastMessageID();
        void SendRequestForLastMessages();
        ~SecureSocket();

    private:
        static const int BUFFER_SIZE = 1024;
        static const int ID_SIZE = 18;

        const SSL_METHOD* method;
        SSL_CTX* ctx;
        BIO* bio;
        SSL* ssl;
        
        std::string token;
        std::string guildID;
        std::string channelID;
        std::string lastMessageID;


        char responseBuffer[BUFFER_SIZE];
        std::string response = "";

        const std::string idPrefix = "{\"id\": \"";
        const std::string channelName = "\"isa-bot\"";
        const std::string lastMessagePrefix = "\"last_message_id\": \"";

};

#endif