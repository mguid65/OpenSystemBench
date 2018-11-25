#include "cpuinfo.h"
#include "windows.h"
#include "psapi.h"
#include <stdio.h>
#include <cpuid.h>
#include <sstream>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

CPUInfo::CPUInfo(){
  // getting cpu brand string
  char brand[0x40];
  unsigned int regs[4] = {0,0,0,0};
  __cpuid(0x80000000, regs[0], regs[1], regs[2], regs[3]);
  unsigned int nExIds = regs[0];
  char vendor[14];
    __cpuid(0, regs[0], regs[1], regs[2], regs[3]);
    memcpy(vendor, &regs[1], 4);
    memcpy(vendor+4, &regs[3], 4);
    memcpy(vendor+8, &regs[2], 4);
    vendor[13] = '\0';
  m_vendor_id += vendor;
  memset(brand, 0, sizeof(brand));
  for (unsigned int i = 0x80000000; i <= nExIds; ++i){
    __cpuid(i, regs[0], regs[1], regs[2], regs[3]);
    if (i == 0x80000002){
      memcpy(brand, regs, sizeof(regs));
        } else if (i == 0x80000003) {
      memcpy(brand + 16, regs, sizeof(regs));
      } else if (i == 0x80000004){
      memcpy(brand + 32, regs, sizeof(regs));
          m_model_name += string(brand);
        }
  }

  int pos;
  if((pos = m_model_name.find("@")) != string::npos) {
    m_model_name.erase(pos, m_model_name.length());
  }

  // threads
  SYSTEM_INFO sys;
  GetSystemInfo(&sys);
  m_num_threads = std::to_string(sys.dwNumberOfProcessors);

  // memory
  MEMORYSTATUSEX memInfo;
  memInfo.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&memInfo);
  DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
  float virtualmem = (float)totalVirtualMem/(1024*1024*1024);
  m_virtual_mem = std::to_string(virtualmem);
  DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
  float phymem = (float)totalPhysMem/(1024*1024*1024);
  m_physical_mem = std::to_string(phymem);
  m_swap_mem = std::to_string(virtualmem-phymem);
}

const string CPUInfo::vendor() {
  return m_vendor_id;
}

const string CPUInfo::model() {
  return m_model_name;
}

const string CPUInfo::swap_mem(){
  return m_swap_mem;
}
const string CPUInfo::physical_mem(){
  return m_physical_mem;
}
const string CPUInfo::virtual_mem(){
  return m_virtual_mem;
}
const string CPUInfo::byte_ordering(){
  unsigned n = 0x76543210;
    char* c = (char*)&n;
    if (*c == 0x10){
      m_byte_order = "Little Endian";
    } else {
      m_byte_order = "Big Endian";
    }
  return m_byte_order;
}
const string CPUInfo::threads(){
  return m_num_threads;
}

const string CPUInfo::speed(){
  // frequencies
  double mhz = 10000;
  // while loop is hack to fix weird underflow
  while(mhz >= 10000) {
      struct timezone tz;
      struct timeval start, stop;
      uint64_t cycles[2];
      long ms;
      memset(&tz, 0, sizeof(tz));
      gettimeofday(&start, &tz);
      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[0])); // read timestamp counter ito edx:eax and put in it cycles
      gettimeofday(&start, &tz);
      usleep(250000);
      gettimeofday(&stop, &tz);
      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[1]));
      gettimeofday(&stop, &tz);
      ms = ((stop.tv_sec - start.tv_sec)*1000000) + (stop.tv_usec - start.tv_usec);
      mhz = labs(static_cast<long>((cycles[1] - cycles[0]) / static_cast<long>(ms)));
  }
  m_clock_speed += to_string(mhz/1000.0);
  m_clock_speed.erase(4, m_clock_speed.length());
  m_clock_speed += " GHz";
  return m_clock_speed;
}
