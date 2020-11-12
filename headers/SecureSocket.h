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
        ~SecureSocket();

    private:
        const SSL_METHOD* method;
        SSL_CTX* ctx;
        BIO* bio;
        SSL* ssl;

        unsigned long errorCode;
        char errorMessageBuffer[1024];

        int tmpReturnValue;

        std::string getGuild = "GET /api/users/@me/guilds HTTP/1.1\nHost: discord.com\nConnection: close\nAuthorization: Bot Nzc1MzExNDIwMTcwNTY3Njkx.X6kfBw.cqj4oLQOzjRnwG3jI8o4aPWpQfo\n\n"; 
        char response[1024];
        std::string testResponse = "";

        int test = 0;
};

#endif