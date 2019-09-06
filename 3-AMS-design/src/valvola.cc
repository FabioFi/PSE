#include "valvola.hh"


void valvola::processing(){
  STATUS=IDLE;
  switch (STATUS) {
    case IDLE:
      if(in_flag.read()==1){
        STATUS=OPEN;
      }else if(in_flag.read()==2){
        STATUS=CLOSE;
      }
      aperto = (aperto>in_treshold.read() || aperto<0)?in_treshold.read():aperto + 0;
      d_a.write(aperto);
      break;
    case OPEN:
      if(in_flag.read()==0){
        STATUS=IDLE;
      }else if(in_flag.read()==2){
        STATUS=CLOSE;
      }
      aperto = (aperto>in_treshold.read() || aperto<0)?in_treshold.read():aperto + 0.25;
      d_a.write(aperto);
      break;
    case CLOSE:
      if(in_flag.read()==0){
        STATUS=IDLE;
      }else if(in_flag.read()==1){
        STATUS=OPEN;
      }
      aperto = (aperto>in_treshold.read() || (aperto-0.25)<0)?in_treshold.read():aperto - 0.25;
      d_a.write(aperto);
      break;
  }
}
