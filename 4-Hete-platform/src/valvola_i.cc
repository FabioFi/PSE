#include "valvola_i.hh"

valvola_iface::valvola_iface(sc_core::sc_module_name name):
  flag_controller("flag_controller"),
  threshold_controller("threshold_controller"),
  flag_valvola("flag_valvola"),
  threshold_valvola("threshold_valvola")
{
  std::cout << "----------------VALVOLA INTERFACE --------1-----------" << std::endl;
}

  valvola_iface::~valvola_iface()
{
  std::cout << "----------------VALVOLA INTERFACE ---------2----------" << std::endl;
}

void valvola_iface::processing(){
  flag_valvola.write(flag_controller.read());
  threshold_valvola.write(threshold_controller.read());
  //std::cout << "threshold_controller: " << threshold_controller << " - " << "flag_controller: " << flag_controller << std::endl;
}

void valvola_iface::set_attribute(){
  std::cout << "----------------VALVOLA INTERFACE --------4-----------" << std::endl;
}
