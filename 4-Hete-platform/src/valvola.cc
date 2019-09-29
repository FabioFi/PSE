#include "valvola.hh"

//prima di fare il calcolo fare /1000 per riportare il valore corretto

valvola::valvola(sc_core::sc_module_name name):
  flag("flag"), max_threshold("max_threshold"), apertura("apertura"){
}

void valvola::set_attributes(){
  flag.set_rate(1);
  max_threshold.set_rate(1);
  apertura.set_rate(1);
}

void valvola::processing(){

  // std::cout << "[VALVOLA:] " << flag << " - " << max_threshold /*<< " - " << apertura*/ << std::endl;

  double flag_correct = flag / 100000.0;
  double max_threshold_correct = max_threshold / 100000.0;
  int flag_round = (int) flag_correct;

  std::cout << "[VALVOLA:] " << max_threshold_correct << " - " << flag_correct << " - " /*<< apertura*/ << flag_round  << std::endl;


  current_state = VALVOLA_INIT;

  switch (current_state) {

    case VALVOLA_INIT:
      if (flag_round == 0){
        current_state = IDLE;
      } else if (flag_round == 1){
        current_state = OPEN;
      } else if (flag_round == 2){
        current_state = CLOSE;
      }
      break;

    case IDLE:
      apertura.write(val_ape);
      if (val_ape > max_threshold_correct){
        val_ape = val_ape - 0.25;
      }
      current_state = VALVOLA_INIT;
      break;

    case OPEN:
      if (val_ape >= max_threshold_correct){
        val_ape = val_ape - 0.25;
        current_state = VALVOLA_INIT;
      } else if (val_ape < max_threshold_correct && ((val_ape + 0.25) < max_threshold_correct)){
        val_ape = val_ape + 0.25;
      }
      apertura.write(val_ape);
      break;

      case CLOSE:
      if (val_ape <= 0){
        current_state = VALVOLA_INIT;
      } else if (val_ape > max_threshold_correct){
        val_ape = val_ape - 0.25;
      } else if (val_ape > 0 && ((val_ape - 0.25) > 0)){
        val_ape = (val_ape - 0.25);
      }
      apertura.write(val_ape);
      break;
  }
}
