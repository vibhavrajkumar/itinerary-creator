#include "airport.h"

#include <stdexcept>

#include "fileio.h"

// get each line from file and parse through airport constructor to segment into
// members (id, name, coordinates,etc)
Airport::Airport(std::string data) {
  // delimit based on comma
  std::vector<std::string> info = delimit(data, ",");
  // check if all information is present
  if (info.size() < 8) {
    throw std::runtime_error("Missing info on airport data.");
  }
  // loop through the vector and add all the members from the data
  for (size_t i : {1, 2, 3, 4, 6, 7}) {
    if (info.at(i) == "" || info.at(i) == "\"\"" || info.at(i) == "\\N" ||
        (info.at(i).at(0) == '\"' && info.at(i).back() != '\"') ||
        (info.at(i).at(0) != '\"' && info.at(i).back() == '\"')) {
      throw std::runtime_error("Missing info on airport data.");
    }
  }

  // lambda function to trim quotes off each piece of data (dataset has quotes
  // around some points)
  auto trim = [](std::string& s) { return s.substr(1, s.size() - 2); };

  try {
    // trim strings
    name_ = trim(info.at(1));
    location_.first = trim(info.at(2));
    location_.second = trim(info.at(3));
    id_ = trim(info.at(4));
    // convert coordinate strings to double
    coordinates_.first = std::stod(info.at(6));
    coordinates_.second = std::stod(info.at(7));
  } catch (std::invalid_argument e) {
    throw std::runtime_error("Wrong format on airport data.");
  }

  // check that coordinates are valid
  if (coordinates_.first > 90 || coordinates_.first < -90 ||
      coordinates_.second < -180 || coordinates_.second > 180) {
    throw std::runtime_error("Airport not on Earth!");
  }
}

// https://www.geeksforgeeks.org/program-distance-two-points-earth/
int Airport::getDist(const Airport& other) const {
  auto toRadians = [](const double deg) { return deg * M_PI / 180; };
  // convert coordinates to radian values
  double lat1 = toRadians(coordinates_.first);
  double long1 = toRadians(coordinates_.second);
  double lat2 = toRadians(other.getCoordinates().first);
  double long2 = toRadians(other.getCoordinates().second);
  // convert latitude and longitude to kilometers
  return 2 *
         asin(sqrt(pow(sin((lat2 - lat1) / 2), 2) +
                   cos(lat1) * cos(lat2) * pow(sin((long2 - long1) / 2), 2))) *
         6371;
}