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
  char vendor[13];
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

  // clock speed
	int pos = m_model_name.find("@")+2;
	m_clock_speed = m_model_name.substr(pos, m_model_name.length());
 
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
	m_page_file = std::to_string(virtualmem-phymem);
}
const string CPUInfo::page_file(){
  return m_page_file;
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
const string CPUInfo::frequencies(){
  struct timezone tz;
  struct timeval start, stop;
  uint64_t cycles[2];
  uint32_t ms;
  int mhz;
  memset(&tz, 0, sizeof(tz));
  gettimeofday(&start, &tz);
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[0])); // read timestamp counter ito edx:eax and put in it cycles
  gettimeofday(&start, &tz);
  Sleep(250);
  gettimeofday(&stop, &tz);
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[1]));
  gettimeofday(&stop, &tz);
  ms = ((stop.tv_sec - start.tv_sec)*1000000) + (stop.tv_usec - start.tv_usec);
  mhz = (int) (cycles[1] - cycles[0]) / ms;
  m_frequencies = std::to_string(mhz) + " MHz";
  return m_frequencies;
}
const string CPUInfo::vendor(){
  return m_vendor_id;
}
const string CPUInfo::speed(){
  return m_clock_speed;
} 
const string CPUInfo::model(){
  return m_model_name;
} 
/*
int main(void){

  CPUInfo cpuinfo;

  printf("CPU Vendor: %s\n", cpuinfo.vendor().c_str());
  printf("CPU Model: %s\n", cpuinfo.model().c_str());
  printf("CPU clock speed: %s\n", cpuinfo.speed().c_str());
  printf("Concurrent threads: %s\n", cpuinfo.threads().c_str());
  printf("Byte ordering: %s\n",cpuinfo.byte_ordering().c_str());
	printf("Frequencies: %s\n", cpuinfo.frequencies().c_str());
  printf("Virtual mem: %s Gbs\n", cpuinfo.virtual_mem().c_str());
  printf("Page file: %s Gbs\n", cpuinfo.page_file().c_str());
  printf("Physical mem: %s Gbs\n", cpuinfo.physical_mem().c_str());
  return 0;
}
*/
