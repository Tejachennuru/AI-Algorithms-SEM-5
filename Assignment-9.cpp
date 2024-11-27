#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>

using namespace std;

unordered_map<string, unordered_map<string, int>> graph = {
    {"Arad", {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}},
    {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
    {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
    {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu", 80}}},
    {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
    {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
    {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
    {"Rimnicu", {{"Sibiu", 80}, {"Pitesti", 97}, {"Craiova", 146}}}
};

vector<string> cities = {"Arad", "Zerind", "Timisoara", "Sibiu", "Oradea", "Lugoj", "Fagaras", "Rimnicu"};
const int POPULATION_SIZE = 100;
const int GENERATIONS = 1000;
const double MUTATION_RATE = 0.01;


random_device rd;
mt19937 gen(rd());

int calculateDistance(const vector<string>& tour) {
    int distance = 0;
    for (size_t i = 0; i < tour.size(); ++i) {
        const string& from = tour[i];
        const string& to = tour[(i + 1) % tour.size()];
        if (graph[from].find(to) != graph[from].end()) {
            distance += graph[from][to];
        } else {
            distance += 1000;
        }
    }
    return distance;
}

vector<string> generateRandomTour() {
    vector<string> tour = cities;
    shuffle(tour.begin(), tour.end(), gen);
    return tour;
}

vector<string> tournamentSelection(const vector<vector<string>>& population) {
    uniform_int_distribution<> dis(0, population.size() - 1);
    const vector<string>& candidate1 = population[dis(gen)];
    const vector<string>& candidate2 = population[dis(gen)];
    return (calculateDistance(candidate1) < calculateDistance(candidate2)) ? candidate1 : candidate2;
}

vector<string> orderCrossover(const vector<string>& parent1, const vector<string>& parent2) {
    uniform_int_distribution<> dis(0, parent1.size() - 1);
    int start = dis(gen);
    int end = dis(gen);
    if (start > end) swap(start, end);

    vector<string> child(parent1.size());
    vector<bool> used(parent1.size(), false);

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
        used[find(cities.begin(), cities.end(), parent1[i]) - cities.begin()] = true;
    }

    int j = 0;
    for (int i = 0; i < parent1.size(); ++i) {
        if (i == start) {
            i = end;
            continue;
        }
        while (used[find(cities.begin(), cities.end(), parent2[j]) - cities.begin()]) {
            j++;
        }
        child[i] = parent2[j];
        j++;
    }

    return child;
}

void mutate(vector<string>& tour) {
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) < MUTATION_RATE) {
        uniform_int_distribution<> cityDis(0, tour.size() - 1);
        int i = cityDis(gen);
        int j = cityDis(gen);
        swap(tour[i], tour[j]);
    }
}

vector<string> geneticAlgorithm() {
    vector<vector<string>> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population.push_back(generateRandomTour());
    }

    for (int generation = 0; generation < GENERATIONS; ++generation) {
        vector<vector<string>> newPopulation;

        // Elitism: keep the best individual
        auto bestIndividual = min_element(population.begin(), population.end(),
            [](const vector<string>& a, const vector<string>& b) {
                return calculateDistance(a) < calculateDistance(b);
            });
        newPopulation.push_back(*bestIndividual);

        // Generate new individuals
        while (newPopulation.size() < POPULATION_SIZE) {
            vector<string> parent1 = tournamentSelection(population);
            vector<string> parent2 = tournamentSelection(population);
            vector<string> child = orderCrossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = move(newPopulation);

        if (generation % 100 == 0) {
            int bestDistance = calculateDistance(*bestIndividual);
            cout << "Generation " << generation << ": Best distance = " << bestDistance << endl;
        }
    }

    return *min_element(population.begin(), population.end(),
        [](const vector<string>& a, const vector<string>& b) {
            return calculateDistance(a) < calculateDistance(b);
        });
}

int main() {
    cout << "Starting Genetic Algorithm for TSP with 8 Romanian cities..." << endl;

    auto start = chrono::high_resolution_clock::now();
    vector<string> bestTour = geneticAlgorithm();
    auto end = chrono::high_resolution_clock::now();

    cout << "\nBest tour found:" << endl;
    for (const string& city : bestTour) {
        cout << city << " -> ";
    }
    cout << bestTour[0] << endl;

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    int bestDistance = calculateDistance(bestTour);
    cout << "Total distance: " << bestDistance << endl;

    return 0;
}