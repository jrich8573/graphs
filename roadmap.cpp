#include "roadmap.h"
#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

/**
 * @brief Construct a new Road Map  with not cities and no road segments.
 *
 */
RoadMap::RoadMap()
{
}

/**
 * @brief Add a city to the road map.
 *
 * If the city is already in the map, nothing happens.
 *
 * @param cityName name of the new city
 */
void RoadMap::addCity(std::string cityName){
  auto pos = cityNames.find(cityName);
  if (pos == cityNames.end()){
    // Never seen this city before. Create a vertex for it.
    Vertex v = add_vertex(g);
    g[v].city = cityName;
    cityNames[cityName] = v;
  }
}

/**
 * @brief Add a named road segment.
 *
 * @param city1 name of one of the cities connected by this segment.
 * @param city2 name of the other city connected by this segment.
 * @param distance distance between the two cities along this road
 * @param roadName name of the road
 */
void RoadMap::addRoadSegment(std::string city1, std::string city2, double distance, std::string roadName){
  Vertex v1 = cityNames[city1];
  Vertex v2 = cityNames[city2];
  Edge e = add_edge(v1, v2, g).first;
  g[e].highway = roadName;
  g[e].distance = distance;
  e = add_edge(v2, v1, g).first;
  g[e].highway = roadName;
  g[e].distance = distance;
}

typedef int Vertex;
typedef std::vector<Vertex> Trip;
Trip RoadMap::planTheTrip(std::string fromCity, std::string toCity){

  std::vector<Trip> citiesVisited;

  for (std::string elem : citiesVisited){
     if(std::find(citiesVisited.begin(), citiesVisited.end(), fromCity) != citiesVisited.end()){
       auto pos  = citiesVisited.push_back(fromCity);
     }else{
       auto pos = citiesVisited.push_back(toCity);
    }
  }




return citiesVisited;
}




/**
 * @brief Print the trip in a human-readable format
 *
 * @param trip
 */
void RoadMap::printTrip(const RoadMap::Trip &trip, std::ostream &out) const{
  if (trip.size() > 1){
    string lastRoadTaken;
    Vertex prior = -1;
    double tripLength = 0.0;
    for (Vertex v : trip){
      if (prior >= 0){
        Edge e = edge(prior, v, g).first;
        tripLength += g[e].distance;
        string road = g[e].highway;
        if (lastRoadTaken != road){
          if (lastRoadTaken == "")
            cout << "From " << g[prior].city;
          else{
            cout << "to " << g[prior].city << endl;
            cout << "From " << g[prior].city;
          }
          cout << " take " << road << " ";
          lastRoadTaken = road;
        }
      }
      prior = v;
    }
    string destinationCityName = g[trip[trip.size() - 1]].city;
    cout << "to " << destinationCityName << endl;
    cout << "Trip length: " << tripLength << endl;
  }
}