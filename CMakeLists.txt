cmake_minimum_required(VERSION 3.10.2)
add_compile_options(-lssl -lcrypto)
#add_compile_options(-L /usr/lib -lssl -lcrypto)
#add_compile_options(-I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib)
project(isabot)


include_directories(headers)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(isabot ${SOURCES})