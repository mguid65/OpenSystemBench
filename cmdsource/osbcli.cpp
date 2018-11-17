#include "../algorithms/headers/algorithm.h"
#include "osbcli.h"
#include "../sysinfo/cpuinfo.cpp"
#include "../headers/submit.h"
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <unistd.h>

using std::cout;
using std::cin;

OSBBenchmarkConfig::OSBBenchmarkConfig(){
  reset();
}

void OSBBenchmarkConfig::reset() {
  vector<string> valid_config = {"1","2","3","4","5","6"};
  for (const auto& conf : valid_config){
    m_run_marker[conf] = false;
  }
}

void OSBBenchmarkConfig::show_result_window(){
  printf("\n--------------------\n");

  printf("\nOSB - Results\n\n");
  cout << std::left;
  cout << "------------------------------------------------------------------" << endl;
  cout << "|" << setw(20) << "Algorithm" << setw(25) << "|Time" << setw(30) 
       << "|Score             |" << endl;
  cout << "------------------------------------------------------------------" << endl;
  for (const auto& elt : m_time) {
    string name{elt.first};
    cout << std::left;
    cout << "|" << setw(20) << name << setw(25)
	 << "|"+to_string(elt.second) << setw(1)
	 << "|" << std::fixed /*<< std::setprecision(6) */
	 << m_score[name] << "       |" << endl;  
  }
  cout << "------------------------------------------------------------------" << endl;

  printf("\n--------------------\n");
  printf("CPU Info:\n");
  printf("--------------------\n");
  CPUInfo cpu;
  cout << "Vendor: " << cpu.vendor() << "\n"
       << "Model: " << cpu.model() << "\n"
       << "Speed: " << cpu.speed() << "\n"
       << "Threads: " << cpu.threads() << "\n"
       << "Byte Order: " << cpu.byte_ordering() << "\n";
  printf("--------------------\n");
  printf("Memory Info Info:\n");
  cout << "Phys. Mem: " << cpu.physical_mem() << "\n"
       << "Virtual Mem: " << cpu.virtual_mem() << "\n"
       << "Swap Mem: " << cpu.swap_mem() << "\n";
  printf("--------------------\n");

  cout << "\nSelect an option: ";
  while (1){
    string opt;
    printf("\n[0] - Exit\n");
    printf("[1] - Start Over\n");
    printf("[2] - Submit\n");
    printf("[3] - Save\n");
    cin >> opt;
    switch (opt[0]){
      case '0': exit(0);
      case '1':
      {
        show_main_menu();
	break;
      }
      case '2':
      {
	if (m_bench_type != "STANDARD"){
	  cout << "[ERROR] Non-Standrd Run" << endl;
	  return;
	}
        show_submit_window();
	break;
      }
      case '3':
      {
	save_previous_run();
        break;
      }
      default:
      {
        cout << "\nInvalid option, please try again.\n";
        cout << "\nSelect an option: ";
        break;
      }
    }
  }
}

bool OSBBenchmarkConfig::check_dir(const char* path){
  struct stat info;
  if(stat( path, &info ) != 0)
    return 0;
  else if(info.st_mode & S_IFDIR)
    return 1;
  else
    return 0;
}

void OSBBenchmarkConfig::save_previous_run(){
  printf("\n--------------------\n");
  printf("\nOSB - Save Results\n");

  printf("\n[0] - Cancel Save Results\n");
  cout << "[1] - Please specify output directory: ";
  string input{""};
  cin >> input;
  if (input == "0") return;
  if (!check_dir(input.c_str())) {
    string make_dir = "mmkdir -p " + input; 
    if(system(make_dir.c_str()) < 0){
      cout << "Error: unable to create output directory.\n";
      return;
    }
  }
  if (input.at(input.size()-1) != '/') input += "/";
  char hostname[512];
  hostname[511] = '\0';
  gethostname(hostname, sizeof(hostname));
  input +=  string(hostname) + ".csv";
  std::ofstream ofs(input);
  ofs << "Algorithm,Time,Score,\n";
  for (const auto& elt : m_time){
    string name{elt.first};
    ofs << name << "," << to_string(m_time[name]) << "," << to_string(m_score[name]) <<",\n";
  }
  ofs.close();
  cout << "Results saved to: " + input << "\n";
}

void OSBBenchmarkConfig::show_submit_window(){
  printf("\n--------------------\n"); 
  printf("\nOSB - Main Menu\n\n");
  string usr{""};
  cout << "Username: " << endl;
  cin >> usr;
  string pw{""};
  cout << "Password: " << endl;
  cin >> pw;
  
  printf("\nSelect an option: ");
  printf("[0] - Exit\n");
  printf("[1] - Cancel\n");
  printf("[2] - Submit\n");

  string opt{""};
  cin >> opt;
  switch(opt[0]){
    case '0': exit(0);
    case '1': return;
    case '2':
    {
      submit sub;
      sub.do_submission(usr.c_str(),pw.c_str(), "json");
      string res = sub.getError();
      if(res != "") {
        cout << res << endl;
      } else {
        string response = sub.getResponse();
	if(response == "200 OK") {
	  sub.cleanup();
	} else {
	  cout << "Response: " << res << endl;
	}
      }
      break;
    }
    default:
    {
      cout << "\nInvalid option, please try again.\n";
      cout << "\nSelect an option: ";
      break;
    }
  }
}

void OSBBenchmarkConfig::show_main_menu(){
  printf("\n--------------------\n");

  string opt;
  bool valid{false};
  
  printf("\nOSB - Main Menu\n\n");
  printf("[0] - Exit\n");
  printf("[1] - Standard Benchmark\n");
  printf("[2] - Custom Benchmark\n");

  printf("\nSelect an option: ");
  while (valid == false){
    cin >> opt;
    switch(opt[0]){
      case '0': exit(0);
      case '1': 
      {
        set_standard_run();
        run_benchmark();
        valid = true;
        break;
      }
      case '2':
      {
        show_custom_menu();
        valid = true;
        break;
      }
      default:{
        cout << "\nInvalid option, please try again.\n";
        cout << "\nSelect an option: ";
        break;
      }
    }
  }
}

void OSBBenchmarkConfig::set_standard_run(){
  m_bench_type = "STANDARD";
  vector<string> valid_config = {"1","2","3","4","5"};
  for (auto& conf : valid_config){
    m_run_marker[conf] = true;
  }
}

void OSBBenchmarkConfig::run_benchmark(){
  printf("\n--------------------\n");
  std::vector<Algorithm> algList;
  cout << "\nRunning " << m_bench_type << " benchmark...\n";

  if (m_run_marker["1"]){ 
    //cout << "\n- NBody Simulation";
    algList.push_back(new NBody());
  }
  if (m_run_marker["2"]){ 
    //cout << "\n- PiDigits";
    algList.push_back(new PiDigits());
  }
  if (m_run_marker["3"]){
    //cout << "\n- Mandelbrot";
    algList.push_back(new Mandelbrot());
  }
  if (m_run_marker["4"]){
    //cout << "\n- Spectral Norms";
    algList.push_back(new SpectralNorm());
  }
  if (m_run_marker["5"]){
     //cout << "\n- Binary Trees";
     algList.push_back(new BinaryTrees());
  }
  if (m_run_marker["6"]){
     cout << "\n- Overclocked\n";
  }

  std::string name;
  for (Algorithm& alg : algList){
    name = alg.getName();
    std::cout << name << "\n";
    cout.flush();
    alg.runAlgorithm();

    m_time[name] = alg.getTime()/1E9;
    m_score[name] = convert_time_to_score(alg.getTime());
    
    cout << m_time[name] << "\n";
    //cout << m_score[name] << "\n";
    cout.flush();
  } 

  cout << "\nDone.\n\n";
  show_result_window();
}

void OSBBenchmarkConfig::show_custom_menu(){
  reset();
  printf("\n--------------------\n");
  m_bench_type = "CUSTOM";

  printf("\n\nOSB - Custom Benchmark Preferences\n");
  printf("[0] - Back\n\n");
  //printf("[7] - Run Benchmark\n\n");
  printf("%s%30s\n", "CPU:", "I/O:");
  printf("[1] - NBody Simulation %25s\n", "[5] - Binary Trees");
  printf("[2] - PiDigits\n");
  printf("[3] - Mandelbrot\n");
  printf("[4] - Spectral Norm\n\n");
  printf("Other Settings:\n");
  printf("[6] - Overclocked\n");

  while (1){
    string inputs;
    printf("\nPlease enter configuration, comma seperated: \n");
    cin >> inputs;
    string token;
    istringstream ss(inputs);
    char delim = ',';
    vector<string> options;
    for (std::string each; std::getline(ss, each, delim); options.push_back(each));
    if (options.size() == 1 && options.at(0) == "0"){
      show_main_menu();
      break;
    } else {
      for (const auto& opt : options){
        //cout << opt << endl;
        m_run_marker[opt] = true;
      }
      break;
    }
  }
  run_benchmark();
}

double OSBBenchmarkConfig::convert_time_to_score(double time){
  m_total_time += time;
  time /= 1E9;
  double score = (.001/time)*10000000;
  m_total_score += score;
  return score;
}


