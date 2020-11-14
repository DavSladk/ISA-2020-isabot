#ifndef XSLADK07_SECURESOCKET_H
#define XSLADK07_SECURESOCKET_H

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <iostream>
#include <cstring>

#include "CustomException.h"

#include <thread>
#include <chrono>

class SecureSocket
{
    public:
        void SetUp();
        SecureSocket(std::string token, bool verbose);
        void SendRequestForGuilds();
        std::string ReceiveResponse();
        void CheckResponseForOK();
        void ParseOutGuildID();
        void SendRequestForGuildChannels();
        void clean();
        void ParseOutChannelID();
        void SendRequestForLastMessage();
        std::string ParseOutLastMessageID();
        void SendRequestForLastMessages();
        bool CheckForNoNewMessages();
        void EchoMessages();
        std::string::size_type ParseOutLastMessageContent();
        std::string::size_type ParseOutLastMessageUsername();
        void SendEchoRequest();
        std::string response = "";
        std::string lastMessageID;

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
        std::string content;
        std::string username;

        bool verbose;

        std::string::size_type lastPos;

        char responseBuffer[BUFFER_SIZE];

        const std::string idPrefix = "{\"id\": \"";
        const std::string channelName = "\"isa-bot\"";
        const std::string lastMessagePrefix = "\"last_message_id\": \"";
        const std::string contentPrefix = "\"content\": \"";
        const std::string usernamePrefix = "\"username\": \"";

};

#endif