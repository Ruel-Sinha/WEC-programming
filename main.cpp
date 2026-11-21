#include "globals.h"
#include <cstdio>
#include <netinet/in.h>
#include <sstream>
#include <stdbool.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#include "headers/alg_battery_fail.hpp"
#include "headers/alg_cloudy.hpp"
#include "headers/alg_generator_fail.hpp"
#include "headers/alg_grid_fail.hpp"
#include "headers/alg_no_event.hpp"
#include "headers/charge_battery.hpp"
#include "headers/json.hpp"

using namespace std;
using json = nlohmann::json;


grid_price = 0;
random_event = 0;

forecast = false;


battery = 0;
hour = 0;

non_lecture_demand[12] = {0};
lecture_demand[12] = {0};


int main(void) {
  std::stringstream ss;

  // creates the socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  int opt = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // specifies address
  sockaddr_in serverAddress{};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8800);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // binding socket
  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  // listen to socket
  listen(serverSocket, 5);

  // accept connection requests
  int clientSocket = accept(serverSocket, nullptr, nullptr);

  char buffer[4096];
  ssize_t bytes_read;
  while ((bytes_read = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
    ss.write(buffer, bytes_read);
  }

  json Doc;
  while (ss >> Doc) {
    if (Doc["random_event"] == "none") {
      random_event = 0;
    } else if (Doc["random_event"] == "cloudy_weather") {
      random_event = 1;
    } else if (Doc["random_event"] == "generator_failure") {
      random_event = 2;
    } else if (Doc["random_event"] == "battery_failure") {
      random_event = 3;
    } else if (Doc["random_event"] == "grid_failure") {
      random_event = 4;
    } else {
      throw runtime_error("Random Event does not match anything");
    }

    // sets forecast
    if (Doc["forecast"] == "cloudy") {
      forecast = true;
    } else if (Doc["forecast"] == "not cloudy") {
      forecast = false;
    } else {
      throw runtime_error("Weather Forecast does not match anything");
    }

    // sets grid_price
    grid_price = Doc["grid_price"];

    // populating building_vector
    struct building_vector building_list(0);
    for (size_t i = 0; i < Doc["loads"].size(); i++) {
      struct building building1;
      if (Doc["loads"][i]["type"] == "lecture_hall") {
        building1 = {true, Doc["loads"][i]["load"]};
      } else {
        building1 = {false, Doc["loads"][i]["load"]};
      }
      building_list.buildings.push_back(building1);
    }

    building_return result(building_list.buildings.size());
    for (auto &dist : result.building_energy_dists) {
      dist.solar = 0;
      dist.battery = 0;
      dist.grid = 0;
    }

    json response;
    response["buildings"] = json::array();

    for (const auto &dist : result.building_energy_dists) {
      response["buildings"].push_back({{"solar", dist.solar},
                                       {"battery", dist.battery},
                                       {"grid", dist.grid}});
    }

    response["generator"] = 0;

    // sends json back
    std::string response_str = response.dump() + "\n";
    send(clientSocket, response_str.c_str(), response_str.size(), 0);
  }

  close(clientSocket);
  close(serverSocket);
  return 0;
}
