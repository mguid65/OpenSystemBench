#include "../algorithms/headers/algorithm.h"
#include "osbcli.h"

using std::cout;
using std::cin;

void OSBBenchmarkConfig::show_main_menu(){
  printf("\n--------------------\n");

  uint32_t opt;
  bool valid{false};
  
  printf("\nOSB - Main Menu\n\n");
  printf("[0] - Exit\n");
  printf("[1] - Standard Benchmark\n");
  printf("[2] - Custom Benchmark\n");

  printf("\n Select an option: ");
  while (valid == false){
    cin >> opt;
    switch(opt){
      case 0: exit(0);
      case 1: 
      {
        set_standard_run();
        run_benchmark();
        valid = true;
        break;
      }
      case 2:
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
  m_nbody_simulation = true;
  m_pidigits = true;
  m_mandelbrot = true;
  m_spectral_norm = true;
  m_binary_trees = true;
  m_overclocked = true;
}

void OSBBenchmarkConfig::run_benchmark(){
  printf("\n--------------------\n");
  std::vector<Algorithm> algList;

  if (m_nbody_simulation){ 
    //cout << "\n- NBody Simulation";
    algList.push_back(new NBody());
  }
  if (m_pidigits){ 
    //cout << "\n- PiDigits";
    algList.push_back(new PiDigits());
  }
  if (m_mandelbrot){
    //cout << "\n- Mandelbrot";
    algList.push_back(new Mandelbrot());
  }
  if (m_spectral_norm){
    //cout << "\n- Spectral Norms";
    algList.push_back(new SpectralNorm());
  }
  if (m_binary_trees){
     //cout << "\n- Binary Trees";
     algList.push_back(new BinaryTrees());
  }
  if (m_overclocked){
     cout << "\n- Overclocked\n";
  }

  std::string name;
  for (Algorithm& alg : algList){
    name = alg.getName();
    std::cout << name << "\n";
    cout.flush();
    alg.runAlgorithm();

    m_time[name] = alg.getTime();
    m_score[name] = convert_time_to_score(m_time[name]);
    m_total_time += m_time[name];
    m_total_score += m_score[name];

    cout << m_time[name]/1E9 << "\n";
    cout.flush();
  } 

  cout << "\n\nRunning " << m_bench_type << " benchmark...\n";
  cout << "Done.\n\n";
  show_main_menu();
}

void OSBBenchmarkConfig::show_custom_menu(){
  printf("\n--------------------\n");
  uint32_t opt;
  bool valid = false;
  m_bench_type = "CUSTOM";

  printf("\n\nOSB - Custom Benchmark Preferences\n");
  printf("[0] - Back\n");
  printf("[7] - Run Benchmark\n\n");
  printf("%s%30s\n", "CPU:", "I/O:");
  printf("[1] - NBody Simulation %25s\n", "[5] - Binary Trees");
  printf("[2] - PiDigits\n");
  printf("[3] - Mandelbrot\n");
  printf("[4] - Spectral Norm\n\n");
  printf("Other Settings:\n");
  printf("[6] - Overclocked\n");

  while (valid == false){
    cout << "\n Select an option: \n";
    //scanf("%d", opt);
    cin >> opt;
    switch(opt){
      case 0:
      {
        show_main_menu();
        break;
      }
      case 1:
      {
        m_nbody_simulation = !m_nbody_simulation;
        if (m_nbody_simulation) cout << "NBody added\n";
        else cout << "NBody removed\n";
        break;
      }
      case 2:
      {
        m_pidigits = !m_pidigits;
        if (m_pidigits) cout << "PiDigits added\n";
        else cout << "PiDigits remived\n";
				break;
			}
      case 3:
      {
        m_mandelbrot = !m_mandelbrot;
        if (m_mandelbrot) cout << "Mandelbrot added\n";
        else cout << "Mandelbrot removed\n";
        break;
      }
      case 4:
      {
        m_spectral_norm = !m_spectral_norm;
        if (m_spectral_norm) cout << "Spectral Norm added\n";
        else cout << "Spectral removed\n";
        break;
      }
      case 5:
      {
        m_binary_trees = !m_binary_trees;
        if (m_binary_trees) cout << "Binary Trees added\n";
        else cout << "Binary Trees removed\n";
        break;
      }
      case 6:
      {
        m_overclocked = !m_overclocked;
        if (m_overclocked) cout << "The system is overclocked\n";
        else cout << "The system is NOT overclocked\n";
        break;
      }
      case 7:
      {
        valid = true;
        run_benchmark();
        break;
      }
      default:
      {
        cout << "Invalid option, please try again.\n";
      }    
    }  
  }
  run_benchmark();
}

double OSBBenchmarkConfig::convert_time_to_score(double time){
  return (.001/time)*10000000;
}


