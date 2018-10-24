#include <string>

using std::string;
/*class CPUID {
  char CPUBrandString[0x40];
  unsigned int CPUInfo[4] = {0,0,0,0};

  __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
  unsigned int nExIds = CPUInfo[0];

  memset(CPUBrandString, 0, sizeof(CPUBrandString));

  for (unsigned int i = 0x80000000; i <= nExIds; ++i){
    __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

    if (i == 0x80000002)
        memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000003)
        memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000004)
        memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
  }
};*/
class CPUInfo{
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
		const string page_file();
  private:
    string m_vendor_id;
    string m_model_name;
    string m_clock_speed;
    string m_byte_order;
    string m_frequencies;
    string m_num_threads;
    string m_physical_mem;
    string m_virtual_mem;
		string m_page_file;
};
