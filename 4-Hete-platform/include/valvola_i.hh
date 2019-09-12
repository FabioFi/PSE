#ifndef VALVOLA_IFACE_HH
#define VALVOLA_IFACE_HH

#include <systemc-ams>

SCA_TDF_MODULE(valvola_iface){
public:
  sca_tdf::sca_de::sca_in <int> flag_controller;
  sca_tdf::sca_de::sca_in <double> threshold_controller;

  sca_tdf::sca_out <int> flag_valvola;
  sca_tdf::sca_out <double> threshold_valvola;

  valvola_iface(sc_core::sc_module_name name);

  ~valvola_iface();

  void set_attribute();
  void processing();

};

#endif
