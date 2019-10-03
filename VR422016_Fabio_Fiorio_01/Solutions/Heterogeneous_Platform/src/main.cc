#include "valvola.hh"
#include "serbatoio.hh"
#include "xtea_LT_testbench.hh"
#include "define_LT.hh"
#include "serbatoio_TLM.hh"
#include "valvola_i.hh"
//#include "valvola_tlm.hh"
#include "xtea_RTL.hh"
#include "xtea_RTL_transactor.hh"
#include "trace.hh"

// ---

int sc_main(int argc, char * argv[]){

    sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
    main_RTL* topl;

    topl= new main_RTL("topl");

    //trace_file
    sca_util::sca_trace_file * atf = sca_create_vcd_trace_file("trace");
    //sca_util::sca_trace(atf, topl->m_flag, "m_flag");
    //sca_util::sca_trace(atf, topl->m_flag_tlm, "m_flag_tlm");
    //sca_util::sca_trace(atf, topl->m_threshold, "m_threshold");
    //sca_util::sca_trace(atf, topl->m_threshold_tlm, "m_threshold_tlm");
    //sca_util::sca_trace(atf, topl->m_apertura, "m_apertura");
    sca_util::sca_trace(atf, topl->m_livello_acqua, "m_livello_acqua");

    sc_core::sc_start(10000, sc_core::SC_MS);

    sca_util::sca_close_vcd_trace_file(atf);

    return 0;
};
