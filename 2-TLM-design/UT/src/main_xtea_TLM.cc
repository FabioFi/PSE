#include "xtea_TLM_testbench.hh"
#include "xtea_TLM.hh"

class sc_main : public sc_module {

  private:

    xtea_TLM m_target;
    xtea_TLM_testbench m_initiator;

  public:

    sc_main(sc_module_name name)
      : sc_module(name)
      , m_target("target")
      , m_initiator("initiator") 
      {
        m_initiator.initiator_socket(m_target.target_socket);
      }

};

int main(int argc, char * argv[]) {

  sc_main top("top");

  sc_start();

  return 0;

}
