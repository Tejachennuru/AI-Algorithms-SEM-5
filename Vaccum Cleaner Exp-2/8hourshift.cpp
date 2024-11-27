#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

class Environment {
public:
    Environment(int n, int m) : n(n), m(m) {
        grid = create_environment();
    }

    std::vector<std::vector<char>> create_environment() {
        std::vector<std::vector<char>> grid(n, std::vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (static_cast<float>(rand()) / RAND_MAX < 0.05) {  // 5% chance of dirt
                    grid[i][j] = 'D';
                } else {
                    grid[i][j] = 'C';
                }
            }
        }
        return grid;
    }

    void print_environment() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    bool is_clean() const {
        for (const auto& row : grid) {
            if (std::any_of(row.begin(), row.end(), [](char cell) { return cell == 'D'; })) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::vector<char>>& get_grid() {
        return grid;
    }

private:
    int n, m;
    std::vector<std::vector<char>> grid;
};

class VacuumCleaner {
public:
    VacuumCleaner(Environment& env) : env(env), x(rand() % env.get_grid().size()), y(rand() % env.get_grid()[0].size()), cleaned_cells(0), moves(0) {}

    void move() {
        // Move the vacuum cleaner to a random adjacent cell
        std::vector<std::string> directions = {"up", "down", "left", "right"};
        std::string move = directions[rand() % directions.size()];

        if (move == "up" && x > 0) {
            x -= 1;
        } else if (move == "down" && x < env.get_grid().size() - 1) {
            x += 1;
        } else if (move == "left" && y > 0) {
            y -= 1;
        } else if (move == "right" && y < env.get_grid()[0].size() - 1) {
            y += 1;
        }
        moves += 1;
    }

    void clean() {
        if (env.get_grid()[x][y] == 'D') {
            env.get_grid()[x][y] = 'C';
            cleaned_cells += 1;
        }
    }

    void work_one_hour() {
        for (int i = 0; i < 60; ++i) {  // Assuming each move takes 1 minute
            move();
            clean();
        }
    }

    int get_cleaned_cells() const {
        return cleaned_cells;
    }

    int get_moves() const {
        return moves;
    }

private:
    Environment& env;
    int x, y;
    int cleaned_cells;
    int moves;
};

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    int n = rand() % 8 + 8;
    int m = rand() % 8 + 8;

    Environment environment(n, m);
    VacuumCleaner vacuum_cleaner(environment);

    std::cout << "Initial Environment:" << std::endl;
    environment.print_environment();

    for (int hour = 0; hour < 8; ++hour) {
        vacuum_cleaner.work_one_hour();
        std::cout << "\nEnvironment after " << hour + 1 << " hour(s):" << std::endl;
        environment.print_environment();
        std::cout << "Cleaned cells: " << vacuum_cleaner.get_cleaned_cells() << ", Moves: " << vacuum_cleaner.get_moves() << std::endl;
    }

    std::cout << "\nFinal Environment:" << std::endl;
    environment.print_environment();
    std::cout << "Total cleaned cells: " << vacuum_cleaner.get_cleaned_cells() << ", Total moves: " << vacuum_cleaner.get_moves() << std::endl;
    std::cout << "Environment is clean: " << (environment.is_clean() ? "Yes" : "No") << std::endl;

    return 0;
}
