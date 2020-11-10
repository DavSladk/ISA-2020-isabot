#include "SecureSocket.h"

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

    tmpReturnValue = BIO_do_connect(bio);
    if ( tmpReturnValue < 0)
    {
        throw CustomException("Connecting to server failed.", TEMP);
    }
}

SecureSocket::~SecureSocket()
{
    SSL_CTX_free(ctx);
    BIO_free_all(bio);
}