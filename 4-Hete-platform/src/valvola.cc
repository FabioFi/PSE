#include "valvola.hh"

valvola::valvola(sc_core::sc_module_name name):
  flag("flag"), max_threshold("max_threshold"), apertura("apertura"){
}

void valvola::set_attributes(){
  flag.set_rate(1);
  max_threshold.set_rate(1);
  apertura.set_rate(1);
}

void valvola::processing(){

  current_state = VALVOLA_INIT;

  switch (current_state) {

    case VALVOLA_INIT:
      if (flag == 0){
        current_state = IDLE;
      } else if (flag == 1){
        current_state = OPEN;
      } else if (flag == 2){
        current_state = CLOSE;
      }
      break;

    case IDLE:
      apertura.write(val_ape);
      if (val_ape > max_threshold){
        val_ape = val_ape - 0.25;
      }
      current_state = VALVOLA_INIT;
      break;

    case OPEN:
      if (val_ape >= max_threshold){
        val_ape = val_ape - 0.25;
        current_state = VALVOLA_INIT;
      } else if (val_ape < max_threshold && ((val_ape + 0.25) < max_threshold)){
        val_ape = val_ape + 0.25;
      }
      apertura.write(val_ape);
      break;

      case CLOSE:
      if (val_ape <= 0){
        current_state = VALVOLA_INIT;
      } else if (val_ape > max_threshold){
        val_ape = val_ape - 0.25;
      } else if (val_ape > 0 && ((val_ape - 0.25) > 0)){
        val_ape = (val_ape - 0.25);
      }
      apertura.write(val_ape);
      break;
  }
}
