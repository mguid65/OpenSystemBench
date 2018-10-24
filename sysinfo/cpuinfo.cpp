#include "cpuinfo.h"

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

  // clock speed
  unsigned long pos = m_model_name.find("@")+2;
  m_clock_speed += m_model_name.substr(pos, m_model_name.length());
  m_model_name.erase(pos-2, 10);
  // threads
  //uint32_t num_threads = std::thread::hardware_concurrency();
  m_num_threads += to_string(std::thread::hardware_concurrency());

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

const string CPUInfo::speed() {
  return m_clock_speed;
}

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

const string CPUInfo::frequencies(){
  // frequencies
  struct timezone tz;
  struct timeval start, stop;
  uint64_t cycles[2];
  long ms;
  unsigned long mhz;
  memset(&tz, 0, sizeof(tz));
  gettimeofday(&start, &tz);
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[0])); // read timestamp counter ito edx:eax and put in it cycles
  gettimeofday(&start, &tz);
  usleep(250000);
  gettimeofday(&stop, &tz);
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (cycles[1]));
  gettimeofday(&stop, &tz);
  ms = ((stop.tv_sec - start.tv_sec)*1000000) + (stop.tv_usec - start.tv_usec);
  mhz = static_cast<unsigned long>((cycles[1] - cycles[0]) / static_cast<unsigned long>(ms));
  m_frequencies += to_string(mhz) + " MHz";
  return m_frequencies;
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


