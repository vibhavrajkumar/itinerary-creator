#include "../cs225/catch/catch.hpp"
#include "../src/airport.h"

TEST_CASE("Airport::Constructor", "[Airport]") {
  std::string s =
      "507,\"London Heathrow Airport\",\"London\",\"United "
      "Kingdom\",\"LHR\",\"EGLL\",51.4706,-0.461941,83,0,\"E\",\"Europe/"
      "London\",\"airport\",\"OurAirports\"";
  Airport a(s);
  REQUIRE(a.getName() == "London Heathrow Airport");
  REQUIRE(a.getLocation().first == "London");
  REQUIRE(a.getLocation().second == "United Kingdom");
  REQUIRE(a.getId() == "LHR");
  REQUIRE(a.getCoordinates().first == 51.4706);
  REQUIRE(a.getCoordinates().second == -0.461941);

  std::string s2 =
      "26,\"Kugaaruk Airport\",\"Pelly "
      "Bay\",\"Canada\",\"YBB\",\"CYBB\",68.534401";
  REQUIRE_THROWS_AS(Airport(s2), std::runtime_error);
  std::string s3 =
      "26,\"\",\"Pelly "
      "Bay\",\"Canada\",\"YBB\",\"CYBB\",68.534401,-89.808098,56,-7,\"A\","
      "\"America/Edmonton\",\"airport\",\"OurAirports\"";
  REQUIRE_THROWS_AS(Airport(s3), std::runtime_error);
}

TEST_CASE("Airport::getDist", "[Airport]") {
  std::string s =
      "507,\"London Heathrow Airport\",\"London\",\"United "
      "Kingdom\",\"LHR\",\"EGLL\",51.4706,-0.461941,83,0,\"E\",\"Europe/"
      "London\",\"airport\",\"OurAirports\"";
  Airport a(s);
  std::string s2 =
      "26,\"Kugaaruk Airport\",\"Pelly "
      "Bay\",\"Canada\",\"YBB\",\"CYBB\",68.534401,-89.808098,56,-7,\"A\","
      "\"America/Edmonton\",\"airport\",\"OurAirports\"";
  Airport a2(s2);
  REQUIRE(a.getDist(a2) == 4788);
}
