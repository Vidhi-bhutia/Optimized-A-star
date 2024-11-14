# A* Route Optimization Program

This program is a command-line application that uses the A* algorithm to find an optimal route between two cities. It takes into account distance, road closures, and varying traffic levels to compute the best path from a starting city to a goal city.

## Features

- Calculates distances between cities using the Haversine formula based on latitude and longitude.
- Applies a traffic multiplier to each road, adjusting for conditions like no traffic, low, medium, or high traffic levels.
- Allows for roads to be marked as closed, which the algorithm will avoid.
- Uses the A* algorithm to compute the optimal route between a start and goal city, leveraging heuristic-based searching.

## Files


- `main.cpp`: Contains the complete code implementing the city route optimization with A* algorithm.

## Installation and Usage

1. **Compilation**: Make sure you have a C++ compiler installed (e.g., g++, clang++).
   
2. **Compile the Program**:
   ```bash
   g++ main.cpp -o route_optimizer
    ```

3. **Run the Program**:
    ```bash
    ./route_optimizer
    ```

## Program Flow

1. **Input Number of Cities**: The user provides the total number of cities to consider.

2. **Enter City Details**: For each city, input:

- Name of the city
- Latitude and Longitude coordinates
3. **Enter Road Information**: For each city pair, enter:

- Distance between the cities
- Whether the road is closed (1 for yes, 0 for no)
- Traffic level (choices are "no," "low," "medium," or "high")
4. **Define Start and Goal Cities**:

- Specify the starting city and the goal city.
5. **Find Optimal Route**:

- The program will use the A* algorithm to compute and display the optimal route.
## Example of Input and Output
**Input**:
    ```bash
    Enter the number of cities: 3
    Enter name of city 1: A
    Enter latitude and longitude for A: 52.52 13.405
    Enter name of city 2: B
    Enter latitude and longitude for B: 48.8566 2.3522
    Enter name of city 3: C
    Enter latitude and longitude for C: 51.1657 10.4515
    Enter distance from A to B: 1050
    Is the road from A to B closed? (1 for yes, 0 for no): 0
    Enter traffic level from A to B (no, low, medium, high): low
    Enter distance from A to C: 600
    Is the road from A to C closed? (1 for yes, 0 for no): 0
    Enter traffic level from A to C (no, low, medium, high): high
    Enter distance from B to C: 400
    Is the road from B to C closed? (1 for yes, 0 for no): 1
    Enter the start city: A
    Enter the goal city: C
    ```

**Output**:
    ```bash
    The optimal route from A to C is: A C
    ```

## Code Structure
1. **City Structure**: Holds each city's name, latitude, and longitude.
2. **Road Structure**: Represents a road with a starting city, ending city, distance, closure status, and traffic multiplier.
3. **Heuristic Calculation**: Uses the Haversine formula to estimate the distance between two geographic points.
4. **A* Algorithm**:
- Initializes cost maps (gValues and fValues) for each city.
- Tracks the best path from the start to the goal using cameFrom.
- Applies the A* search, considering distances, traffic multipliers, and avoiding closed roads.

## Additional Notes
The traffic multiplier is defined as:

- `1.0` for no traffic
- `1.2` for low traffic
- `1.5` for medium traffic
- `2.0` for high traffic

If no path is found, the program outputs `"No path found from <start city> to <goal city>"`.

## Dependencies
This program requires only the standard C++ libraries:

- `<iostream>`
- `<vector>`
- `<queue>`
- `<cmath>`
- `<map>`
- `<string>`
- `<limits>`
- `<algorithm>`