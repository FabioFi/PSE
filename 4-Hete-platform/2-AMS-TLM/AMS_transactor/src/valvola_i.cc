#include "valvola_i.hh"

valvola_iface::valvola_iface(sc_core::sc_module_name name):
  flag_controller("flag_controller"),
  threshold_controller("threshold_controller"),
  flag_valvola("flag_valvola"),
  threshold_valvola("threshold_valvola")
{}

  valvola_iface::~valvola_iface()
{}

void valvola_iface::processing(){
  flag_valvola.write(flag_controller.read());
  threshold_valvola.write(threshold_controller.read());
}

void valvola_iface::set_attribute(){

}
