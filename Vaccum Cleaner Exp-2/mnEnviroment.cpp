#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to create the environment
std::vector<std::vector<char>> create_environment() {
    // Randomly choose n and m from the range 8 to 15
    int n = rand() % 8 + 8;  // n is in range [8, 15]
    int m = rand() % 8 + 8;  // m is in range [8, 15]
    
    // Initialize the environment
    std::vector<std::vector<char>> environment(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (static_cast<float>(rand()) / RAND_MAX < 0.05) {  // 5% chance of dirt
                environment[i][j] = 'D';
            } else {
                environment[i][j] = 'C';
            }
        }
    }
    
    return environment;
}

// Function to print the environment
void print_environment(const std::vector<std::vector<char>>& environment) {
    for (const auto& row : environment) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Create the environment
    std::vector<std::vector<char>> environment = create_environment();
    
    // Print the environment
    std::cout << "Environment:" << std::endl;
    print_environment(environment);
    
    return 0;
}
