#include "GameServer.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

static int MAX_PORT = pow(2, 16); 

int main (int argc, char *argv[])
{
    GameServer * gameServer;
    int port;

    if (argc < 2)
    {
        cout << "[Main] No port supplied on startup.\n\r";
        exit (EXIT_FAILURE);
    }

    port = atoi(argv[1]);

    if (port < 0 || port > MAX_PORT)
    {
        cout << "[Main] Port must be a positive value and less than " << MAX_PORT << "\n\r";
        exit (EXIT_FAILURE); 
    }

    cout << "Starting GameServer on port " << port << "\n\r";

    gameServer = new GameServer(port);

    gameServer->Start();

    delete gameServer;
    gameServer = NULL;

    exit(EXIT_SUCCESS);
}