#ifndef VALVOLA
#define VALVOLA


#include "systemc.h"
#include "systemc-ams.h"

SCA_TDF_MODULE(valvola){
public:
  //input ports
  //TDF Input ports
  sca_tdf::sca_in<int> in_flag;
  sca_tdf::sca_in<double> in_treshold;

  //TLF Outputs
  sca_tdf::sca_out<double> d_a;

  typedef enum{IDLE, OPEN, CLOSE} STATES;

  sc_signal<STATES> STATUS;

  SCA_CTOR( valvola )
    : in_flag("in_flag"), in_treshold("in_treshold"), d_a("d_a"){}


  void processing();

private:
    sc_core::sc_signal<double> aperto;
};

#endif
