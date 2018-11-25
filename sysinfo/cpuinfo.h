#include <string>

using namespace std;

class CPUInfo {
  public:
    CPUInfo();
    const string vendor();
    const string model();
    const string speed();
    const string threads();
    //const string frequencies();
    const string byte_ordering();
    const string physical_mem();
    const string virtual_mem();
    const string swap_mem();

  private:
    string m_vendor_id{""};
    string m_model_name{""};
    string m_clock_speed{""};
    string m_byte_order{""};
    //string m_frequencies{""};
    string m_num_threads{""};
    string m_physical_mem{""};
    string m_virtual_mem{""};
    string m_swap_mem{""};
};
