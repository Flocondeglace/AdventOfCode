#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point
{
    unsigned long x;
    unsigned long y;
    unsigned long z;
};

using Edge = std::pair<long double, std::pair<int, int>>;

void ReadInputs(const std::string &inputFile, std::vector<Point> &oJunctionBoxes)
{
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open())
    {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line))
    {
        Point p;
        sscanf_s(line.c_str(), "%lu,%lu,%lu", &p.x, &p.y, &p.z);
        oJunctionBoxes.push_back(p);
    }

    input.close();
}

bool CompareEdges(const Edge &a, const Edge &b)
{
    return a.first > b.first;
}

bool IsAllInSameCircuit(const std::vector<std::vector<int>> &circuits, int numJunctionBoxes)
{
    for (const auto &circuit : circuits)
    {
        if (circuit.size() == numJunctionBoxes)
        {
            
            std::cout << "All junction boxes are in the same circuit." << std::endl;
            return true;
        }
    }
    return false;
}

void ComputeCircuits(const std::vector<Point> &junctionBoxes, int nbPair, int part, std::vector<std::vector<int>> &oCircuits)
{
    int numJunctionBoxes = junctionBoxes.size();
    std::vector<Edge> edges = {};
    // Compute distances
    for (int i = 0; i < numJunctionBoxes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            long long int dx = (long long int)junctionBoxes[i].x - (long long int)junctionBoxes[j].x;
            long long int dy = (long long int)junctionBoxes[i].y - (long long int)junctionBoxes[j].y;
            long long int dz = (long long int)junctionBoxes[i].z - (long long int)junctionBoxes[j].z;
            long double distance = std::sqrtl((long double)(dx * dx + dy * dy + dz * dz));
            edges.push_back({distance, {i, j}});
        }
    }

    // Sort edges by distance
    std::sort(edges.begin(), edges.end(), CompareEdges);
    
    std::cout << "Total edges: " << edges.size() << std::endl;

    std::vector<int> connectedJunctionBoxes(numJunctionBoxes, -1);

    int pairsFound = 0;
    int circuitFirst, circuitSecond;
    bool firstIn, secondIn;
    Edge edge;
    while (((!IsAllInSameCircuit(oCircuits,numJunctionBoxes) && part==2)||((pairsFound < nbPair) && part == 1)) && !edges.empty())
    {
        std::cout << "Pairs found: " << pairsFound << "\r";
        edge = edges.back();
         
        circuitFirst = connectedJunctionBoxes[edge.second.first];
        circuitSecond = connectedJunctionBoxes[edge.second.second];
        firstIn = circuitFirst != -1;
        secondIn = circuitSecond != -1;
        
        if (firstIn && secondIn)
        {
            if (circuitFirst == circuitSecond)
            {
                edges.pop_back();
                pairsFound++;
                continue;
            } else {
                // Merge circuits
                for (int jb : oCircuits[circuitSecond])
                {
                    connectedJunctionBoxes[jb] = circuitFirst;
                    oCircuits[circuitFirst].push_back(jb);
                }
                oCircuits[circuitSecond].clear();
            }
        } 

        if (!firstIn && !secondIn)
        {
            connectedJunctionBoxes[edge.second.first] = oCircuits.size();
            connectedJunctionBoxes[edge.second.second] = oCircuits.size();
            oCircuits.push_back({edge.second.first, edge.second.second});
            
        } else if (!firstIn)
        {
           connectedJunctionBoxes[edge.second.first] = connectedJunctionBoxes[edge.second.second];
           oCircuits[connectedJunctionBoxes[edge.second.second]].push_back(edge.second.first);
        } else if (!secondIn)
        {
            connectedJunctionBoxes[edge.second.second] = connectedJunctionBoxes[edge.second.first];
            oCircuits[connectedJunctionBoxes[edge.second.first]].push_back(edge.second.second);
        }
        pairsFound++;
        edges.pop_back();
    }
    
    std::cout << "Pairs found: " << pairsFound << std::endl;
    for (int i = 0; i < numJunctionBoxes; i++)
    {
        if (connectedJunctionBoxes[i] == -1)
        {
            oCircuits.push_back({i});
        }
    }

    std::cout << "Circuits size: ";
    for (const auto &circuit : oCircuits)
    {
        std::cout << circuit.size() << " ";
    }
    std::cout << std::endl;

    if (part == 2)
    {
        unsigned long long int result = (long long unsigned)junctionBoxes[edge.second.first].x * (long long unsigned)junctionBoxes[edge.second.second].x;
        std::cout << "Multiplication of X coordinates last junctions connected: " << result << std::endl;
    }
}

void MultiplyThreeLargestCircuitSizes(const std::vector<std::vector<int>> &circuits)
{
    std::vector<unsigned long> sizes;
    for (const std::vector<int> &circuit : circuits)
    {
        if (!circuit.empty())
        {
            sizes.push_back(circuit.size());
        }
    }
    std::sort(sizes.begin(), sizes.end(), std::greater<unsigned long>());
    if (sizes.size() < 3)
    {
        std::cout << "Not enough circuits to compute the product of the three largest sizes." << std::endl;
        return;
    }
    long long product = sizes[0] * sizes[1] * sizes[2];
    std::cout << "Product of the three largest circuit sizes: " << product << std::endl;
}

int main() {
    std::cout << "Advent of Code 2025 - Day 8" << std::endl;

    for (int i = 1; i <= 2; i++)
    {
        std::cout << "------------------ Part " << i << " ------------------" << std::endl;
        
        std::vector<Point> junctionBoxes;
        std::cout << "Input Example:" << std::endl;
        ReadInputs("input_example.txt", junctionBoxes);
        std::vector<std::vector<int>> circuits;
        ComputeCircuits(junctionBoxes, 10, i, circuits);
        if (i == 1) {
            MultiplyThreeLargestCircuitSizes(circuits);
        }

        std::cout << std::endl;

        junctionBoxes.clear();
        circuits.clear();
        std::cout << "Input:" << std::endl;
        ReadInputs("input.txt", junctionBoxes);
        std::cout << "Number of junction boxes: " << junctionBoxes.size() << std::endl;
        ComputeCircuits(junctionBoxes, 1000, i, circuits);
        if (i == 1) {
            MultiplyThreeLargestCircuitSizes(circuits);
        }

        std::cout << std::endl << std::endl;
    }
}