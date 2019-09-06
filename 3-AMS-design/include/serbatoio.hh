#ifndef SERBATOIO_HH
#define SERBATOIO_HH

#include "systemc.h"
#include "systemc-ams.h"

SC_MODULE (serbatoio){
public:
  //input ports
  sca_lsf::sca_tdf::sca_source tdf_lsf;
  sca_tdf::sca_in<double>in;
  //out Ports
  sca_lsf::sca_tdf::sca_sink lsf_tdf;
  sca_tdf::sca_out<double> out;

//Local Declaration
  sca_lsf::sca_add add;
  sca_lsf::sca_integ integratore;
  sca_lsf::sca_gain guadagno1;
  sca_lsf::sca_gain guadagno2;

  serbatoio(sc_core::sc_module_name);

  ~serbatoio();

private:
  sca_lsf::sca_signal  sig1, sig2, sig3, sig4, sig5;
};

#endif
