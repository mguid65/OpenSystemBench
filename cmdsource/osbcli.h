#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

class OSBBenchmarkConfig{
private:
  std::string m_bench_type{""};
  bool m_nbody_simulation{false};
  bool m_pidigits{false};
  bool m_mandelbrot{false};
  bool m_spectral_norm{false};
  bool m_binary_trees{false};
  bool m_overclocked{false};
  std::map<std::string, double> m_time;
  std::map<std::string, double> m_score;
  /*double m_pidigits_time{0.0};
  double m_mandelbrot_time{0.0};
  double m_spectral_norm_time{0.0};
  double m_binary_trees_time{0.0};
  double m_pidigits_score{0.0};
  double m_mandelbrot_score{0.0};
  double m_spectral_norm_score{0.0};
  double m_binary_trees_score{0.0};*/
  double m_total_time{0.0};
  double m_total_score{0.0};
public:
  OSBBenchmarkConfig(){};
  ~OSBBenchmarkConfig(){};
  void reset();
  void show_main_menu();
  void set_standard_run();
  void run_benchmark();
  void show_custom_menu();
  double convert_time_to_score(double time);
};

