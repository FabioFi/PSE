#include "valvola_i.hh"

valvola_iface::valvola_iface(sc_core::sc_module_name name):
  flag_controller("flag_controller"),
  threshold_controller("threshold_controller"),
  flag_valvola("flag_valvola"),
  threshold_valvola("threshold_valvola")
{
  //std::cout << "----------------VALVOLA INTERFACE --------1-----------" << std::endl;
}

  valvola_iface::~valvola_iface()
{
}

void valvola_iface::processing(){
  double conv1 = (double) flag_controller.read();
  double conv2 = (double) threshold_controller.read();

  flag_valvola.write(conv1);
  threshold_valvola.write(conv2);
  //std::cout << "[VALVOLA IFACE:]" << std::endl;
  std::cout << "[VALVOLA IFACE:] threshold_valvola: " << flag_controller.read() << " - " << "flag_valvola: " << threshold_controller.read() << std::endl;
}

void valvola_iface::set_attribute(){
}
