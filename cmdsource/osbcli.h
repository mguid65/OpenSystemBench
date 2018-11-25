#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

class OSBBenchmarkConfig{
private:
  std::string m_json_str{""};
  std::string m_bench_type{""};
  std::vector<std::string> m_sys_info;
  std::vector<std::string> m_sys_info_label;
  std::map<std::string, bool> m_run_marker;
  std::map<std::string, double> m_time;
  std::map<std::string, uint64_t> m_time_nano;
  std::map<std::string, double> m_score;
  double m_total_time{0.0};
  uint64_t m_total_time_nano{0};
  double m_total_score{0.0};
public:
  OSBBenchmarkConfig();
  ~OSBBenchmarkConfig(){};
  void reset();
  void show_main_menu();
  void set_standard_run();
  void run_benchmark();
  void show_custom_menu();
  void show_result_window();
  void show_submit_window();
  void save_previous_run();
  void write_json();
  double convert_time_to_score(double time);
  bool check_dir(const char* path);
  bool m_submit_flag{false};
};

