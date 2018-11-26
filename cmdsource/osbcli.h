#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

class OSBBenchmarkConfig{
private:
  std::string m_json_str{""}; // the json string necessary for submitting the score
  std::string m_bench_type{""}; // standard or custom
  std::vector<std::string> m_sys_info; // all of the system info relative to m_system_info_label
  std::vector<std::string> m_sys_info_label; // labels for system info
  std::map<std::string, bool> m_run_marker; // marks which algorithm to run
  std::map<std::string, double> m_time; // time for each algorithm
  std::map<std::string, uint64_t> m_time_nano; // time in nano second nessesary for submission
  std::map<std::string, double> m_score; // score for each algorithm
  double m_total_time{0.0}; // total time in double
  uint64_t m_total_time_nano{0}; // total time in nano
  double m_total_score{0.0}; // total score
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

