#ifndef _VALVOLA_HH_
#define _VALVOLA_HH_

#include "systemc.h"
#include "systemc-ams.h"

enum VALVOLA_STATE {VALVOLA_INIT, IDLE, OPEN, CLOSE };

SCA_TDF_MODULE(valvola){
public:
  sca_tdf::sca_in< int > flag;
  sca_tdf::sca_in< double > max_threshold;
  sca_tdf::sca_out< double > apertura;

  sc_signal< VALVOLA_STATE > current_state;

  void set_attributes();
  void processing();

  SCA_CTOR(valvola);

private:
  sc_signal< double > val_ape;
};

#endif
