#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Class to hold robot information
class Robot
{
private:
    string type, name;
    int posX, posY;

public:
    Robot(const string &type = "", const string &name = "", int posX = 0, int posY = 0)
        : type(type), name(name), posX(posX), posY(posY) {}

    void display() const
    {
        cout << "Type: " << type << ", Name: " << name
             << ", Position: (" << posX << ", " << posY << ")" << endl;
    }

    int getX() const { return posX; }
    int getY() const { return posY; }
};

// Function to read file and store information in dynamic array
void readFile(const string &filename, int &m, int &n, int &steps, Robot *&robots, int &numRobots)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Unable to open file" << endl;
        return;
    }

    string line;

    // Read the M by N line
    if (getline(infile, line))
    {
        cout << "Reading line: " << line << endl; // Debug
        stringstream ss(line);
        string part;
        getline(ss, part, ':'); // Ignore the first part
        ss >> m >> n;           // Read the two integers
    }

    // Read the steps line
    if (getline(infile, line))
    {
        cout << "Reading line: " << line << endl; // Debug
        stringstream ss(line);
        string part;
        getline(ss, part, ':'); // Ignore the first part
        ss >> steps;            // Read the integer
    }

    // Read the robots line
    if (getline(infile, line))
    {
        cout << "Reading line: " << line << endl; // Debug
        stringstream ss(line);
        string part;
        getline(ss, part, ':'); // Ignore the first part
        ss >> numRobots;        // Read the integer
    }

    // Dynamically allocate array for robots
    robots = new Robot[numRobots];

    // Read each robot's information
    int index = 0;
    while (getline(infile, line) && index < numRobots)
    {
        cout << "Reading line: " << line << endl; // Debug
        stringstream ss(line);
        string type, name;
        int posX, posY;
        ss >> type >> name >> posX >> posY;
        robots[index++] = Robot(type, name, posX, posY);
    }

    infile.close();
}

void createBattlefield(int m, int n, Robot *robots, int numRobots)
{
    // Create a 2D array initialized with '.'
    char **battlefield = new char *[m];
    for (int i = 0; i < m; ++i)
    {
        battlefield[i] = new char[n];
        for (int j = 0; j < n; ++j)
        {
            battlefield[i][j] = '.';
        }
    }

    // Place the robots on the battlefield
    for (int i = 0; i < numRobots; ++i)
    {
        int x = robots[i].getX();
        int y = robots[i].getY();
        if (x >= 0 && x < m && y >= 0 && y < n)
        {
            battlefield[x][y] = 'R'; // Using 'R' to denote robots
        }
    }

    // Display the battlefield
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << battlefield[i][j] << ' ';
        }
        cout << endl;
    }

    // Deallocate battlefield
    for (int i = 0; i < m; ++i)
    {
        delete[] battlefield[i];
    }
    delete[] battlefield;
}

int main()
{
    const string filename = "battlefield.txt";
    int m = 0, n = 0, steps = 0, numRobots = 0;
    Robot *robots = nullptr;
    readFile(filename, m, n, steps, robots, numRobots);

    cout << "M by N: " << m << " " << n << endl;
    cout << "Steps: " << steps << endl;
    cout << "Number of robots: " << numRobots << endl;
    for (int i = 0; i < numRobots; ++i)
    {
        robots[i].display();
    }

    createBattlefield(m, n, robots, numRobots);

    // Clean up dynamically allocated robots array
    delete[] robots;

    return 0;
}
