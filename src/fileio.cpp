#include "fileio.h"

#include <stdexcept>

std::vector<std::string> delimit(const std::string& raw, const std::string& delimiter) {
  std::vector<std::string> ret;
  std::string str = raw;
  while (str.find(delimiter) != std::string::npos) {
    size_t idx = str.find(delimiter);
    ret.push_back(str.substr(0, idx));
    str.erase(0, idx+1);
  }
  ret.push_back(str);
  return ret;
}

FileIO::FileIO() {}

FileIO::~FileIO() {
  closeFile();
}

void FileIO::closeFile() {
  ifs_.close();
}

void FileIO::openFile(const std::string& filename) {
  closeFile();
  filename_ = filename;
  ifs_.open(filename);
  if (!ifs_.is_open()) {
    throw std::runtime_error("Cannot open file.");
  }
}

std::string FileIO::getline() {
  if (ifs_.eof()) {
    throw std::out_of_range("File ended.");
  }
  if (!ifs_.good()) {
    throw std::runtime_error("Error on file read.");
  }
  
  char line[500];
  ifs_.getline(line, 500);
  return line;
}