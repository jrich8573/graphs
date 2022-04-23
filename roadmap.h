#ifndef ROADMAP_H
#define ROADMAP_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//#include "graph.h"

class RoadMap {
private:

struct City {
	std::string city;
};
struct Highway {
	std::string highway;
	double distance;
};




typedef boost::adjacency_list<boost::listS,       // store edges in lists
							  boost::vecS,        // store vertices in a vector
							  boost::directedS, // a directed graph
							  City,               // vertex data
							  Highway               // edge data
							  >
Graph;

typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::edge_descriptor Edge;
typedef int Vertex;

public:

    /**
     * @brief A trip between two cities, with any number of steps in between.
     * 
     */
    typedef std::vector<Vertex> Trip;

    /**
     * @brief Construct a new Road Map  with not cities and no road segments.
     * 
     */
    RoadMap();

    /**
     * @brief Add a city to the road map.
     * 
     * If the city is already in the map, nothing happens.
     * 
     * @param cityName name of the new city
     */
    void addCity(std::string cityName);

    /**
     * @brief Add a named road segment.
     * 
     * @param city1 name of one of the cities connected by this segment - must have been previously added.
     * @param city2 name of the other city connected by this segment  - must have been previously added.
     * @param distance distance between the two cities along this road
     * @param roadName name of the road
     */
    void addRoadSegment (std::string city1, std::string city2, double distance, std::string roadName);

    /**
     * @brief Plan the shortest trip between two cities.
     * 
     * @param fromCity the starting city
     * @param toCity   the city where we are to finish
     * @return std::vector<std::string>  List of cities visited, from start to finish.
     */
    Trip planTheTrip (std::string fromCity, std::string toCity);

    /**
     * @brief Print the trip in a human-readable format
     * 
     * @param trip 
     */
    void printTrip (const Trip& trip, std::ostream& out) const;

private:
    Graph g;  // contains the roadmap
    std::map<std::string, Vertex> cityNames; // maps each city to a unique vertex

    std::vector<Vertex> findWeightedShortestPath (Vertex start, Vertex finish);

};


#endif
