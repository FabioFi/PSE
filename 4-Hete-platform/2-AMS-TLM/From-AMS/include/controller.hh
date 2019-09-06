#ifndef CONTROLLER_HH
#define CONTROLLER_HH


#include "systemc.h"
#include "systemc-ams.h"

SCA_TDF_MODULE(controller){
public:
  sca_tdf::sca_in<double> in;

  sca_tdf::sca_out<double> out_treshold;
  sca_tdf::sca_out<int> out_flag;

  typedef enum {ACTIVE, DISABLED} STATE_CONTROLLER;

  sc_signal<STATE_CONTROLLER> STATUS;

  double t;

  SCA_CTOR( controller )
    : in("in"), out_treshold("treshold"), out_flag("flag"){}

  void set_attributes();

  void processing();

private:
  int i;


};

#endif
