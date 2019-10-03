#include "controller.hh"
#include "serbatoio.hh"
#include "valvola.hh"


int sc_main(int argc, char* argv[]){
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_MS);


  //local ports
  sca_tdf::sca_signal<double> d_a;
  sca_tdf::sca_signal<double> x;
  sca_tdf::sca_signal<double> out_treshold;
  sca_tdf::sca_signal<int> out_flag;

  //serbatoio module
  serbatoio wtank("serbatoio");
  wtank.in(d_a);
  wtank.out(x);

  //valvola module
  valvola valv("valvola");
  valv.d_a(d_a);
  valv.in_flag(out_flag);
  valv.in_treshold(out_treshold);

  //controller module
  controller ctllr("controller");
  ctllr.out_flag(out_flag);
  ctllr.out_treshold(out_treshold);
  ctllr.in(x);


  //trace_file
  sca_util::sca_trace_file * atf = sca_util::sca_create_vcd_trace_file("trace.vcd");
  sca_util::sca_trace(atf, d_a   , "a");
  sca_util::sca_trace(atf, x   , "x");
  sca_util::sca_trace(atf, out_treshold      , "treshold");
  sca_util::sca_trace(atf, out_flag  , "flag");

  sc_core::sc_start(1000000, sc_core::SC_MS);

  sca_util::sca_close_vcd_trace_file(atf);

  return 0;
}
