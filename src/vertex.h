#pragma once

#include <string>

// Base class for Vertex. Since the Graph manages vertices by their ID,
// a function `getId()` is required for the template type. There is a 
// special check in Graph that requires the template type to be a derived
// class of Vertex.
class Vertex {
 public:
  virtual std::string getId() const = 0;
};