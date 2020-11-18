# isabot

### Usage

isa-bot [-h|--help] [-v|--verbose] -t <bot_access_token>

* -h|--help : Prints out this help end exits.
* -v|--verbose : Prints out log of echoed messages.
* -t <bot_access_token> : Access token for the bot to communicate with discord api server.

Help is printed if no option is used and bot terminates immediately.

### Required to build
Below listed versions are the lowest one the bot was tested on. You can use the newer versions too.

* openssl - 1.0.2k
* g++ - 7.5.0
* cmake - 3.16.3

### List of files
.

├── CMakeLists.txt

├── Makefile

├── README.md

├── headers

│   ├── CustomException.h

│   ├── Options.h

│   ├── SecureSocket.h

│   └── isabot.h

├── manual.pdf

└── src

  ├── CustomException.cpp

    ├── Options.cpp

    ├── SecureSocket.cpp

    ├── isabot.cpp
    └── main.cpp

2 directories, 13 files