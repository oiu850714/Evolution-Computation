#include "OneMaxPopulation.h"
#include <iostream>

int main() {
  EVO_HW::OneMaxPopulation_tournament population(200);
  for (int i = 0; i < 100; i++) {
    population.generate_new_generation();
    std::cout << population.best_fitness_val();
    std::cout << (i == 99 ? "\n" : ",");
  }
}