#ifndef XSLADK07_SECURESOCKET_H
#define XSLADK07_SECURESOCKET_H

#include <openssl/ssl.h>
#include <openssl/err.h>

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
};

#endif