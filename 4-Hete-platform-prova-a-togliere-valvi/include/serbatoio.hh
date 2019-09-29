#ifndef __SERBATOIO__
#define __SERBATOIO__

#include "systemc-ams.h"
#include "systemc.h"

SC_MODULE(serbatoio)
{
  public:

  sca_lsf::sca_signal valvola_apertura;
  sca_lsf::sca_signal livello_acqua;

  sca_lsf::sca_tdf::sca_source apertura;
  sca_tdf::sca_in< double > in;
  sca_lsf::sca_de::sca_sink livello_acqua_out;
  sc_core::sc_out< double > out;

  sca_lsf::sca_integ integratore;
  sca_lsf::sca_gain guadagno1, guadagno2;
  sca_lsf::sca_sub sub1;

  SC_CTOR( serbatoio );

  private:
  sca_lsf::sca_signal sig1, sig2, sig3;

};

#endif
