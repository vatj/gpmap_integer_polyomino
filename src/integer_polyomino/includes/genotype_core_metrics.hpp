#pragma once

#include "integer_model.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

// struct Shape_Metrics
// {
//   Phenotype_ID pID;
//   uint32_t robustness;
//
//   Shape_Metrics(Phenotype_ID pID);
//
//   void robust_pID(std::vector <Phenotype_ID> pIDs);
// };

typedef struct Shape_Metrics Shape_Metrics;

struct Genotype_Metrics
{
  uint8_t n_genes;
  int8_t low_colour, high_colour;

  Genotype ref_genotype, original;
  std::vector <Phenotype_ID> ref_pIDs;
  std::map <Phenotype_ID, uint16_t> pID_counter;

  Phenotype_ID rare_pID = {0, 0}, unbound_pID = {255, 0};
  uint8_t max_size = 0;

  double number_of_neighbours;
  double strict_robustness = 0, intersection_robustness = 0;
  double union_evolvability = 0, complex_diversity = 0;
  double robust_evolvability = 0, complex_evolvability = 0;
  double rare = 0, unbound = 0, neutral_weight=0;

  // std::vector <Shape_Metrics> shapes;
  std::set <Phenotype_ID> diversity;

  Genotype_Metrics(uint8_t ngenes, int8_t low_colour, int8_t high_colour);

  void set_reference(Genotype& mutant, Genotype& genotype,
    std::vector<Phenotype_ID> pIDs, double neutral);

  void clear();

  void analyse_pIDs(std::vector <Phenotype_ID>& pIDs);

  void save_to_file(std::ofstream& fout);

  py::dict to_dict();
};

typedef struct Genotype_Metrics Genotype_Metrics;

struct Set_Metrics
{
  uint8_t n_genes, max_size;
  int8_t low_colour, high_colour;
  uint32_t analysed, complex_diversity;

  std::vector <Phenotype_ID> ref_pIDs;
  std::vector <Genotype> originals;
  std::map <Genotype, std::vector<Phenotype_ID>> misclassified;

  std::vector <double> strict_robustnesses, intersection_robustnesses;
  std::vector <double> complex_evolvabilities, robust_evolvabilities;
  std::vector <double> union_evolvabilities;
  std::vector<double> rares, unbounds;
  std::vector <double> neutral_weightings;
  std::vector <Genotype_Metrics> genome_metrics;
  std::vector <uint32_t> diversity_tracker;

  std::set <Phenotype_ID> diversity;

  Set_Metrics(uint8_t n_genes, int8_t low_colour, int8_t high_colour);

  void add_genotype_metrics(Genotype_Metrics& gmetrics);

  void save_to_file(std::ofstream& set_out, std::ofstream& genome_out);

  void clear();
};

typedef struct Set_Metrics Set_Metrics;
