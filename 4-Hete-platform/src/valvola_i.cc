#include "valvola_i.hh"

valvola_iface::valvola_iface(sc_core::sc_module_name name):
  flag_controller("flag_controller"),
  threshold_controller("threshold_controller"),
  flag_valvola("flag_valvola"),
  threshold_valvola("threshold_valvola")
{
}

  valvola_iface::~valvola_iface()
{
}

void valvola_iface::processing(){
  double conv1 = (double) flag_controller.read();
  double conv2 = (double) threshold_controller.read();

  double pluto = 0x000012cc8;
  double pippo = 0x00001adb0;

  flag_valvola.write(pippo);
  threshold_valvola.write(pluto);
  std::cout << "[VALVOLA IFACE:] threshold_valvola: " << flag_controller.read() << " - " << "flag_valvola: " << threshold_controller.read() << std::endl;
}

void valvola_iface::set_attribute(){
}
