#ifdef _WIN32
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
#elif __linux__
#include "cpuinfo.h"
#include <iostream>

CPUInfo::CPUInfo()
{
  // vendor
  CPUID _vendor(0);
  m_vendor_id += string(reinterpret_cast<const char *>(&_vendor.ebx()), 4);
  m_vendor_id += string(reinterpret_cast<const char *>(&_vendor.edx()), 4);
  m_vendor_id += string(reinterpret_cast<const char *>(&_vendor.ecx()), 4);

  // model
  for(uint32_t i=0x80000002; i<0x80000005; ++i) {
    CPUID _model(i);
    m_model_name += string(reinterpret_cast<const char *>(&_model.eax()), 4);
    m_model_name += string(reinterpret_cast<const char *>(&_model.ebx()), 4);
    m_model_name += string(reinterpret_cast<const char *>(&_model.ecx()), 4);
    m_model_name += string(reinterpret_cast<const char *>(&_model.edx()), 4);
  }
  m_model_name.erase(m_model_name.begin(), std::find_if(m_model_name.begin(), m_model_name.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
  // clock speed
  int pos;
  if((pos = m_model_name.find("@")) != string::npos) {
    m_model_name.erase(pos, m_model_name.length());
  }
  // m_clock_speed += m_model_name.substr(pos, m_model_name.length());

  //m_model_name.erase(p, 10);
  // threads
  //uint32_t num_threads = std::thread::hardware_concurrency();
  m_num_threads += to_string(std::thread::hardware_concurrency()); //this number is higher if hardware simultaneous multithreading is enabled

  struct sysinfo memInfo;
  sysinfo (&memInfo);
  unsigned long total_virtual = memInfo.totalram;
  //Add other values in next statement to avoid int overflow on right hand side...
  total_virtual += memInfo.totalswap;
  total_virtual *= memInfo.mem_unit;
  unsigned long total_physical_mem = memInfo.totalram;
  //Multiply in next statement to avoid int overflow on right hand side...
  total_physical_mem *= memInfo.mem_unit;
  unsigned long total_swap_mem = memInfo.totalswap;
  total_swap_mem *= memInfo.mem_unit;
  m_virtual_mem += to_string(static_cast<float>(total_virtual)/(1024*1024*1024)).substr(0,6) + " Gb";
  m_physical_mem += to_string(static_cast<float>(total_physical_mem)/(1024*1024*1024)).substr(0,6) + " Gb";
  m_swap_mem += to_string(static_cast<float>(total_swap_mem)/(1024*1024*1024)).substr(0,6) + " Gb";
}

const string CPUInfo::vendor() {
  return m_vendor_id;
}

const string CPUInfo::model() {
  return m_model_name;
}

/*
const string CPUInfo::speed() {
  return m_clock_speed;
}
*/

const string CPUInfo::threads(){
  return m_num_threads;
}

const string CPUInfo::byte_ordering(){
  // byte ordering
  uint32_t n = 0x76543210;
  char *c =reinterpret_cast<char *>(&n);
  if (*c == 0x10){
    m_byte_order += "Little Endian";
  } else {
    m_byte_order += "Big Endian";
  }
  return m_byte_order;
}

const string CPUInfo::speed(){
  // frequencies
  double mhz = 10000;
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

const string CPUInfo::virtual_mem(){
  return m_virtual_mem;
}

const string CPUInfo::physical_mem(){
  return m_physical_mem;
}

const string CPUInfo::swap_mem(){
  return m_swap_mem;
}
#endif
