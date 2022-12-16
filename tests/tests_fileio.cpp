#include "../cs225/catch/catch.hpp"

#include "tests_helper.hpp"
#include "../src/fileio.h"

TEST_CASE("FileIO::delimit", "[FileIO]") {
  auto strCompare = [](const std::string& p, const std::string& q) {
    return p.compare(q) == 0;
  };

  std::string raw = "0,1,2,3,4";
  std::vector<std::string> ans = {"0", "1", "2", "3", "4"};
  matchVectorComplex(delimit(raw, ","), ans, strCompare);

  raw = "0000, 0, 10, ,";
  ans = {"0000", " 0", " 10", " ", ""};
  matchVectorComplex(delimit(raw, ","), ans, strCompare);
}

TEST_CASE("FileIO::getline", "[FileIO]") {
  FileIO io;
  REQUIRE_THROWS_AS(io.openFile("???"), std::runtime_error);
  io.openFile("tests/testfile.txt");
  REQUIRE(io.getline() == "First line;   ");
  REQUIRE(io.getline() == "Second___\"'line");
  REQUIRE(io.getline() == "");
  REQUIRE(io.getline() == "   THERE WAS AN EMPTY LINE???");
  REQUIRE(io.getline() == "eof`incoming`");
  REQUIRE_THROWS_AS(io.getline(), std::out_of_range);
}