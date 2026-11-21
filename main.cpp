#include <vector>
#include <stdbool.h>
#include <globals.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include alg_battery_fail.h
#include alg_cloudy.h
#include alg_generator.h
#include alg_grid_fail.h
#include alg_no_event.h
#include charge_generator.h

using namespace std;

void main() {
    // creates the socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // specifies address 
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8800);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // binding socket
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    // listen to socket
    listen(serverSocket, 5);
    // accept connection requests
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    // TODO: Receive the JSON file

    // close the socket
    close(serverSocket);
}