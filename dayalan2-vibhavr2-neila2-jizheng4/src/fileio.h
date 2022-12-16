#pragma once

#include <vector>
#include <string>
#include <fstream>

// Delimits a string with respect to the delimiter character passed
// into the function, and returns the splitted substrings in a vector
// of strings.
std::vector<std::string> delimit(const std::string& raw, const std::string& delimiter);

class FileIO {
 public:
  FileIO();
  ~FileIO();

  // Closes the current opened file of this FileIO instance.
  void closeFile();

  // Opens a file linked to this FileIO instance.
  void openFile(const std::string& filename);

  // Get a line from the currently opened file.
  std::string getline();

 private:
  std::string filename_;
  std::ifstream ifs_;
};