#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

// Structure to represent each city with its coordinates (latitude and longitude)
struct City
{
    string name;
    double latitude, longitude;
};

// Structure to represent a road between two cities with distance and traffic multiplier
struct Road
{
    string from, to;
    double distance;
    bool isClosed;
    double trafficMultiplier;
};

// Function to calculate heuristic using Haversine formula (distance between two lat/long points)
double calculateHeuristic(double lat1, double lon1, double lat2, double lon2)
{
    const double R = 6371.0; // Earth radius in kilometers
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double calcHeuristic = R * c;
    return calcHeuristic; // Return the distance in kilometers
}

// A* algorithm to find the optimal route
vector<string> aStarAlgorithm(const vector<City> &cities, const vector<Road> &roads, const string &startCity, const string &goalCity)
{
    map<string, double> gValues;  // Holds the actual cost from the start city to each city
    map<string, double> fValues;  // Holds the estimated cost (g + h)
    map<string, string> cameFrom; // Keeps track of the optimal path
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> openList;

    // Initialize g and f values
    for (const auto &city : cities)
    {
        gValues[city.name] = numeric_limits<double>::infinity();
        fValues[city.name] = numeric_limits<double>::infinity();
    }

    gValues[startCity] = 0.0;
    fValues[startCity] = calculateHeuristic(cities[0].latitude, cities[0].longitude, cities[1].latitude, cities[1].longitude);
    openList.push({fValues[startCity], startCity});

    while (!openList.empty())
    {
        string currentCity = openList.top().second;
        openList.pop();

        // If we reached the goal city, reconstruct the path
        if (currentCity == goalCity)
        {
            vector<string> optimalRoute;
            while (cameFrom.find(currentCity) != cameFrom.end())
            {
                optimalRoute.push_back(currentCity);
                currentCity = cameFrom[currentCity];
            }
            optimalRoute.push_back(startCity);
            reverse(optimalRoute.begin(), optimalRoute.end());
            return optimalRoute;
        }

        // Check neighbors (other cities directly connected)
        for (const auto &road : roads)
        {
            if ((road.from == currentCity || road.to == currentCity) && !road.isClosed)
            {
                string neighbor = (road.from == currentCity) ? road.to : road.from;
                double tentativeG = gValues[currentCity] + road.distance * road.trafficMultiplier;

                if (tentativeG < gValues[neighbor])
                {
                    cameFrom[neighbor] = currentCity;
                    gValues[neighbor] = tentativeG;
                    fValues[neighbor] = gValues[neighbor] + calculateHeuristic(cities[0].latitude, cities[0].longitude, cities[1].latitude, cities[1].longitude);
                    openList.push({fValues[neighbor], neighbor});
                }
            }
        }
    }

    return {}; // Return empty if no path is found
}

int main()
{
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    vector<City> cities(numCities);
    map<string, City> cityMap;

    // Input city names and coordinates
    for (int i = 0; i < numCities; ++i)
    {
        cout << "Enter name of city " << i + 1 << ": ";
        cin >> cities[i].name;
        cout << "Enter latitude and longitude for " << cities[i].name << ": ";
        cin >> cities[i].latitude >> cities[i].longitude;
        cityMap[cities[i].name] = cities[i];
    }

    vector<Road> roads;

    // Input road data (distances, traffic, and closures)
    for (int i = 0; i < numCities; ++i)
    {
        for (int j = i + 1; j < numCities; ++j)
        {
            double distance;
            cout << "Enter distance from " << cities[i].name << " to " << cities[j].name << ": ";
            cin >> distance;
            bool isClosed;
            cout << "Is the road from " << cities[i].name << " to " << cities[j].name << " closed? (1 for yes, 0 for no): ";
            cin >> isClosed;

            if (!isClosed)
            {
                string trafficLevel;
                cout << "Enter traffic level from " << cities[i].name << " to " << cities[j].name << " (no, low, medium, high): ";
                cin >> trafficLevel;
                double trafficMultiplier = (trafficLevel == "no") ? 1.0 : (trafficLevel == "low")  ? 1.2
                                                                      : (trafficLevel == "medium") ? 1.5
                                                                                                   : 2.0;

                roads.push_back({cities[i].name, cities[j].name, distance, isClosed, trafficMultiplier});
            }
        }
    }

    string startCity, goalCity;
    cout << "Enter the start city: ";
    cin >> startCity;
    cout << "Enter the goal city: ";
    cin >> goalCity;

    // Find the optimal route using A* algorithm
    vector<string> optimalRoute = aStarAlgorithm(cities, roads, startCity, goalCity);

    if (!optimalRoute.empty())
    {
        cout << "The optimal route from " << startCity << " to " << goalCity << " is: ";
        for (const string &city : optimalRoute)
        {
            cout << city << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found from " << startCity << " to " << goalCity << endl;
    }

    return 0;
}
