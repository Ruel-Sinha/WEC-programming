#include <vector>
#include <stdbool.h>
#include <globals.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include<alg_battery_fail.hpp>
#include<alg_cloudy.hpp>
#include<alg_generator_fail.hpp>
#include<alg_grid_fail.hpp>
#include<alg_no_event.hpp>
#include<charge_generator.hpp>
#include<json.hpp>

using namespace std;
using json = nlohmann::json;

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
    // TODO: Receive the JSON file into Data
    json Doc{json::parse(Data)};
    // sets random_event
    if (Doc["random_event"] == "none") {
        random_event = 0;
    }
    else if (Doc["random_event"] == "cloudy_weather") {
        random_event = 1;
    }
    else if (Doc["random_event"] == "generator_failure") {
        random_event = 2;
    }
    else if (Doc["random_event"] == "battery_failure") {
        random_event = 3;
    }
    else if (Doc["random_event"] == "grid_failure") {
        random_event = 4;
    }
    else {
        throw runtime_error("Random Event does not match anything");
    }
    // sets forecast
    if (Doc["forecast"] == "cloudy") {
        forecast = true;
    }
    else if (Doc["forecast"] == "not cloudy") {
        forecast = false;
    }
    else{
        throw runtime_error("Weather Forecast does not match anything");
    }
    // sets grid_price
    grid_price = Doc["grid_price"];
    // TODO: populate building_vector

    // close the socket
    close(serverSocket);
}