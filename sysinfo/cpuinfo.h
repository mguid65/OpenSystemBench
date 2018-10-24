#include <algorithm>
#include <iostream>
#include <thread>
#include <string>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>

using namespace std;

class CPUID {

  private:
  uint32_t regs[4];

  public:
  explicit CPUID(unsigned funcId) {
  asm volatile
    ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
      : "a" (funcId));
  }

  const uint32_t &eax() const {return regs[0];}
  const uint32_t &ebx() const {return regs[1];}
  const uint32_t &ecx() const {return regs[2];}
  const uint32_t &edx() const {return regs[3];}

};

class CPUInfo {
  public:
    CPUInfo();
    const string vendor();
    const string model();
    const string speed();
    const string threads();
    const string frequencies();
    const string byte_ordering();
    const string physical_mem();
    const string virtual_mem();
    const string swap_mem();

  private:
    string m_vendor_id{"Vendor: "};
    string m_model_name{"Model: "};
    string m_clock_speed{"Speed: "};
    string m_byte_order{"Byte Order: "};
    string m_frequencies{"Frequencies: "};
    string m_num_threads{"Threads: "};
    string m_physical_mem{"Physical Mem: "};
    string m_virtual_mem{"Virtual Mem: "};
    string m_swap_mem{"Swap Mem: "};
};
