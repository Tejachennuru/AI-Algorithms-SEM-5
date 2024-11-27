#include <iostream>
#include <vector>

class Environment {
private:
    std::vector<std::vector<bool>> grid;
    std::pair<int, int> vacuum_position;
    int score;

public:
    Environment(int rows, int cols, std::vector<std::pair<int, int>> dirt_positions)
        : grid(rows, std::vector<bool>(cols, false)), vacuum_position({0, 0}), score(0) {
        for (const auto& pos : dirt_positions) {
            grid[pos.first][pos.second] = true;
        }
    }

    bool is_dirty(std::pair<int, int> position) {
        return grid[position.first][position.second];
    }

    void clean(std::pair<int, int> position) {
        if (grid[position.first][position.second]) {
            grid[position.first][position.second] = false;
            score++;
        }
    }

    void move_vacuum(const std::string& direction) {
        int x = vacuum_position.first;
        int y = vacuum_position.second;
        if (direction == "UP" && x > 0) {
            vacuum_position.first--;
        } else if (direction == "DOWN" && x < grid.size() - 1) {
            vacuum_position.first++;
        } else if (direction == "LEFT" && y > 0) {
            vacuum_position.second--;
        } else if (direction == "RIGHT" && y < grid[0].size() - 1) {
            vacuum_position.second++;
        }
    }

    std::pair<int, int> get_vacuum_position() {
        return vacuum_position;
    }

    int get_score() {
        return score;
    }

    void display_environment() {
        for (const auto& row : grid) {
            for (bool cell : row) {
                std::cout << (cell ? "D" : ".") << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Vacuum Position: (" << vacuum_position.first << ", " << vacuum_position.second << ")" << std::endl;
        std::cout << "Score: " << score << std::endl;
    }
};

class VacuumCleanerAgent {
private:
    Environment& environment;

public:
    VacuumCleanerAgent(Environment& env) : environment(env) {}

    void perceive_and_act() {
        auto position = environment.get_vacuum_position();
        if (environment.is_dirty(position)) {
            environment.clean(position);
        } else {
            // Simple reflex: move to the next position
            if (position == std::make_pair(0, 0)) {
                environment.move_vacuum("RIGHT");
            } else if (position == std::make_pair(0, 1)) {
                environment.move_vacuum("DOWN");
            } else if (position == std::make_pair(1, 1)) {
                environment.move_vacuum("LEFT");
            } else if (position == std::make_pair(1, 0)) {
                environment.move_vacuum("UP");
            }
        }
    }
};

void run_simulation() {
    std::vector<std::pair<int, int>> dirt_positions = {{0, 0}, {1, 1}};
    Environment environment(2, 2, dirt_positions);
    VacuumCleanerAgent agent(environment);

    for (int i = 0; i < 10; ++i) {  // Run for 10 steps
        agent.perceive_and_act();
        std::cout << "Step " << i + 1 << ":" << std::endl;
        environment.display_environment();
        std::cout << std::endl;
    }
}

int main() {
    run_simulation();
    return 0;
}
