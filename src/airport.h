#pragma once

#include <math.h>
#include <string>

#include "vertex.h"

class Airport : public Vertex {
 public:
  Airport(std::string data);
  int getDist(const Airport& other) const;
  std::string getName() const { return name_; }
  std::pair<std::string, std::string> getLocation() const { return location_; }
  std::string getId() const { return id_; }
  std::pair<double, double> getCoordinates() const { return coordinates_; }
  bool operator!=(const Airport& other) const {
    return !(getId() == other.getId());
  }
 private:
  std::string name_;
  std::pair<std::string, std::string> location_;
  std::string id_;
  std::pair<double, double> coordinates_;
};