#include "globals.h"
#include <arpa/inet.h>
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
#include "headers/alg_grid_fail.hpp"
#include "headers/alg_no_event.hpp"
#include "headers/charge_battery.hpp"
#include "headers/json.hpp"

using namespace std;
using json = nlohmann::json;


double grid_price = 0;
int random_event = 0;

bool forecast = false;


int battery = 0;
int hour = 0;

int non_lecture_demand[12] = {0};
int lecture_demand[12] = {0};

int main(void) {
  std::stringstream ss;

  // creates the socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  // specifies address
  sockaddr_in serverAddress{};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8800);
  inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) < 0) {
    perror("Connection failed");
    return 1;
  }

  char buffer[4096];
  ssize_t bytes_read;
  std::string recv_buffer;

  while ((bytes_read = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
    for (ssize_t k = 0; k < bytes_read; ++k) {
      if (buffer[k] != '\n' && buffer[k] != '\r') {
        recv_buffer += buffer[k];
      }
    }

    // 2. Check if we have a complete JSON object { ... }
    int brace_count = 0;
    bool in_string = false;
    bool started = false;

    for (size_t i = 0; i < recv_buffer.size(); ++i) {
      if (recv_buffer[i] == '"' && (i == 0 || recv_buffer[i - 1] != '\\')) {
        in_string = !in_string;
      }
      if (!in_string) {
        if (recv_buffer[i] == '{') {
          brace_count++;
          started = true;
        } else if (recv_buffer[i] == '}') {
          brace_count--;
        }
      }

      // 3. Once braces match, we have one complete single-line JSON object
      if (started && brace_count == 0) {
        std::string single_line_json = recv_buffer.substr(0, i + 1);
        recv_buffer.erase(0, i + 1);
        i = -1;
        started = false;
        json Doc = json::parse(single_line_json);

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
      grid_price = Doc["grid_cost"];

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

      struct building_return result(0);

      if (random_event == 0) {
        result = NoChange(building_list);
      } else if (random_event == 1) {
        result = cloudy_failure(building_list);
      } else if (random_event == 3) {
        result = battery_failure(building_list);
      } else if (random_event == 4) {
        result = grid_failure(building_list);
      }

      int generator = chargeBattery(forecast, random_event, building_list);


      std::string response_str = "{\n  \"buildings\": [\n";
      for (size_t i = 0; i < result.building_energy_dists.size(); i++) {

        const auto &dist = result.building_energy_dists[i];

        json b = {
          {"solar", dist.solar},
          {"battery", dist.battery},
          {"grid", dist.grid}
        };
        
        response_str += "    " + b.dump();
        
        if (i < result.building_energy_dists.size() - 1) {
          response_str += ",";
          response_str += "\n";
        }
        
        battery -= dist.battery;
      }

      response_str += "],\n";
      response_str += "  \"generator\": " + json(generator).dump() + "\n";
      response_str += "}\n";

      // sends json back
      send(clientSocket, response_str.c_str(), response_str.size(), 0);

      hour++;
      battery += generator;
    }

    ss.clear();
  }}

  close(clientSocket);
  return 0;
}
