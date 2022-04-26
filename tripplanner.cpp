#include "roadmap.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

void readRoadMap(string fileName, RoadMap &roadmap)
{

  string city1, city2, road;
  double distance;

  // Read in the roads data
  ifstream roadsIn(fileName);
  while (roadsIn.good())
  {
    string line;
    getline(roadsIn, line);
    if (roadsIn.good() && line.length() > 0)
    {
      istringstream in(line);
      in >> road >> city1;
      roadmap.addCity(city1);
      while (in >> distance)
      {
        in >> city2;
        // road runs from city1 to city2 in distance miles
        roadmap.addCity(city2);
        roadmap.addRoadSegment(city1, city2, distance, road);
        city1 = city2;
      }
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cerr << "Usage: " << argv[0]
         << " fileName startingCity endingCity" << endl;
    return 1;
  }

  RoadMap roadmap;
  readRoadMap(argv[1], roadmap);

  string startingCityName = argv[2];
  string destinationCityName = argv[3];

  if (startingCityName == destinationCityName)
    cout << "You are already at " << startingCityName << endl;
  else
  {
    RoadMap::Trip trip = roadmap.planTheTrip(startingCityName, destinationCityName);
    for(int i = 0; i < trip.size(); i++)
      cout << "the value of trip is: " << trip.front(i) << '\n';

    if (trip.size() > 1)
    {
      roadmap.printTrip(trip, cout);
    }
    else
    {
      cout << "You can't get from " << startingCityName
           << " to " << destinationCityName << endl;
    }
  }
  return 0;
}
