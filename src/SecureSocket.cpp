#include "SecureSocket.h"

void SecureSocket::SetUp()
{
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    
    method = TLSv1_2_client_method();
    if ( method == NULL )
    {
        ERR_error_string_n(errorCode, errorMessageBuffer, sizeof(errorMessageBuffer));
        throw CustomException(errorMessageBuffer, TEMP);
    }    

    ctx = SSL_CTX_new(method);
    if ( ctx == NULL )
    {
        ERR_error_string_n(errorCode, errorMessageBuffer, sizeof(errorMessageBuffer));
        throw CustomException(errorMessageBuffer, TEMP);
    }    

    bio = BIO_new_ssl_connect(ctx);
    if ( bio == NULL)
    {
        ERR_error_string_n(errorCode, errorMessageBuffer, sizeof(errorMessageBuffer));
        throw CustomException(errorMessageBuffer, TEMP);
    }
    

    BIO_get_ssl(bio, &ssl);

    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    BIO_set_conn_hostname(bio, "https://discord.com:https");

    tmpReturnValue = BIO_do_connect(bio);
    if ( tmpReturnValue < 0)
    {
        ERR_error_string_n(errorCode, errorMessageBuffer, sizeof(errorMessageBuffer));
        throw CustomException(errorMessageBuffer, TEMP);
    }
}

SecureSocket::~SecureSocket()
{
    SSL_CTX_free(ctx);
    BIO_free_all(bio);
}