#include "OneMaxPopulation.h"
#include <chrono>
#include <iostream>
#include <utility>

namespace EVO_HW {
Individual::Individual() {
  std::uniform_int_distribution<unsigned> u(0, 1);
  for (size_t i = 0; i < INDIVIDUAL_LEN; ++i) {
    genotype[i] = u(random_engine);
  }
}

Individual::Individual(const Individual &first, const Individual &second,
                       size_t pos) {
  for (size_t i = 0; i < pos; ++i) {
    genotype[i] = first.genotype[i];
  }
  for (size_t i = pos; i < INDIVIDUAL_LEN; ++i) {
    genotype[i] = second.genotype[i];
  }
}

std::default_random_engine Individual::random_engine(
    std::chrono::system_clock::now().time_since_epoch().count());

OneMaxPopulation::OneMaxPopulation(size_t _population_size)
    : population(_population_size), population_size(_population_size),
      random_engine(
          std::chrono::system_clock::now().time_since_epoch().count()) {}

void OneMaxPopulation::generate_new_generation() {
  std::vector<Individual> new_generation;
  std::vector<int> roulette_wheel = generate_roulette_wheel();

  std::uniform_int_distribution<unsigned> u(0, roulette_wheel.size() - 1);

  // select parents and generate new individuals
  for (size_t i = 0;
       i < population_size / 2 /* generate two individuals at a time */; ++i) {
    auto wheel_point_1 = u(random_engine), wheel_point_2 = u(random_engine);
    auto parent_index_1 = roulette_wheel[wheel_point_1],
         parent_index_2 = roulette_wheel[wheel_point_2];
    auto new_individuals =
        crossover(population[parent_index_1], population[parent_index_2]);

    new_generation.push_back(new_individuals.first);
    new_generation.push_back(new_individuals.second);
  }

  population = new_generation;
}

std::vector<int> OneMaxPopulation::generate_roulette_wheel() {
  std::vector<int> roulette_wheel;
  for (size_t i = 0; i < population.size(); ++i) {
    auto fitness = fitness_function(population[i]);
    for (size_t j = 0; j < fitness; ++j) {
      roulette_wheel.push_back(i);
    }
  }

  return roulette_wheel;
}

auto OneMaxPopulation::crossover(const Individual &first,
                                 const Individual &second)
    -> std::pair<Individual, Individual> {
  std::uniform_int_distribution<unsigned> u(0, INDIVIDUAL_LEN - 1);
  return {Individual(first, second, u(random_engine)),
          Individual(second, first, u(random_engine))};
}

size_t OneMaxPopulation::best_fitness_val() {
  size_t best_fitness = 0;
  for (const auto &Individual : population) {
    best_fitness = (best_fitness > fitness_function(Individual)
                        ? best_fitness
                        : fitness_function(Individual));
  }

  return best_fitness;
}

void OneMaxPopulation_tournament::generate_new_generation() {
  std::vector<Individual> new_generation;

  std::uniform_int_distribution<unsigned> u(0, population_size - 1);
  for (size_t i = 0;
       i < population_size / 2 /* generate two individuals at a time */; ++i) {
    auto participant_1 = population[u(random_engine)],
         participant_2 = population[u(random_engine)],
         participant_3 = population[u(random_engine)],
         participant_4 = population[u(random_engine)];

    auto parent1 =
        fitness_function(participant_1) > fitness_function(participant_2)
            ? participant_1
            : participant_2;
    auto parent2 =
        fitness_function(participant_3) > fitness_function(participant_4)
            ? participant_3
            : participant_4;

    auto new_individuals = crossover(parent1, parent2);

    new_generation.push_back(new_individuals.first);
    new_generation.push_back(new_individuals.second);
  }

  population = new_generation;
}

size_t OneMaxPopulation_1000_fitness::best_fitness_val() {
  return OneMaxPopulation::best_fitness_val() - 1000;
}

size_t OneMaxPopulation_tournament_1000_fitness::best_fitness_val() {
  return OneMaxPopulation_tournament::best_fitness_val() - 1000;
}

} // namespace EVO_HW