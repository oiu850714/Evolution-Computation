#include <bitset>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define INDIVIDUAL_LEN 50

namespace EVO_HW {

class OneMaxPopulation;

class Individual {
  friend class OneMaxPopulation;

public:
  // ctor
  Individual();
  Individual(const Individual &, const Individual &,
             size_t pos); // crossover utility

  size_t fitness() const { return genotype.count(); }

private:
  std::bitset<INDIVIDUAL_LEN> genotype;
  static std::default_random_engine random_engine;
};

class OneMaxPopulation {
public:
  // ctor
  OneMaxPopulation(size_t _population_size = 200);

  virtual void generate_new_generation();
  size_t best_fitness_val();

private:
  std::vector<int> generate_roulette_wheel();

protected:
  auto crossover(const Individual &, const Individual &)
      -> std::pair<Individual, Individual>;

  // can change the way of calculating fitness function
  virtual size_t fitness_function(const Individual &individual) {
    return individual.fitness();
  }
  std::vector<Individual> population;
  size_t population_size;
  std::default_random_engine random_engine;
};

class OneMaxPopulation_1000_fitness : public OneMaxPopulation {
public:
  OneMaxPopulation_1000_fitness(size_t _population_size = 200)
      : OneMaxPopulation(_population_size) {}

  virtual size_t fitness_function(const Individual &individual) override {
    return 1000 + individual.fitness();
  }

  size_t best_fitness_val();
};

class OneMaxPopulation_tournament : public OneMaxPopulation {
public:
  virtual void generate_new_generation() override;
  OneMaxPopulation_tournament(size_t _population_size = 200)
      : OneMaxPopulation(_population_size) {}
};

class OneMaxPopulation_tournament_1000_fitness
    : public OneMaxPopulation_tournament {
public:
  OneMaxPopulation_tournament_1000_fitness(size_t _population_size = 200)
      : OneMaxPopulation_tournament(_population_size) {}

  virtual size_t fitness_function(const Individual &individual) override {
    return 1000 + individual.fitness();
  }

  size_t best_fitness_val();
};

} // namespace EVO_HW