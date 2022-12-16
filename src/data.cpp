#include "data.h"

#include "fileio.h"

Data& Data::instance() {
  static Data* instance_ = new Data();
  return *instance_;
}

Data::Data() {
  // Load vertices
  FileIO io;
  std::cout << "Loading airport data..." << std::endl;
  int total = 0, cleansed = 0;
  try {
    io.openFile("data/airports.dat");

    while (true) {
      std::string line = io.getline();
      try {
        Airport airport(line);
        graph_.addNode(airport);
      } catch (std::runtime_error exception) {
        cleansed++;
      }
      total++;
    }
  } catch (std::out_of_range exception) {
    // Reached eof, do nothing
  } catch (std::runtime_error runtimeException) {
    std::cout << "Error! Reading airports data failed!" << std::endl;
  }
  std::cout << "Airport data loaded. Total: " << total
            << ", Cleansed: " << cleansed << ", Valid Data Percentage: "
            << std::trunc((total - cleansed) * 1.0 / total * 10000) / 100.0 << "%"
            << std::endl;
  io.closeFile();

  // Load Edges
  std::cout << "Loading routes data..." << std::endl;
  total = 0; cleansed = 0;
  try {
    io.openFile("data/routes.dat");
    while (true) {
      std::string line = io.getline();
      try {
        std::vector<std::string> info = delimit(line, ",");
        auto airport1 = graph_.getNode(info.at(2));
        auto airport2 = graph_.getNode(info.at(4));
        graph_.addEdge(info.at(2), info.at(4), airport1.getDist(airport2));
      } catch (std::exception exception) {
        cleansed++;
      }
      total++;
    }
  } catch (std::out_of_range exception) {
    // Reached eof, do nothing
  } catch (std::runtime_error runtimeException) {
    std::cout << "Error! Reading routes data failed!" << std::endl;
  }
  std::cout << "Routes data loaded. Total: " << total
            << ", Cleansed: " << cleansed << ", Valid Data Percentage: "
            << std::trunc((total - cleansed) * 1.0 / total * 10000) / 100.0 << "%"
            << std::endl;
  io.closeFile();
}