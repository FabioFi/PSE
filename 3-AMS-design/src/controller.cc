#include "controller.hh"

void controller::set_attributes(){
  in.set_delay(1);
  t=0.7;
  i=0;
}

void controller::processing(){
  if(i==7500){
    i=0;
  STATUS=ACTIVE;
  switch (STATUS) {
    case DISABLED:
      STATUS=ACTIVE;
      break;
    case ACTIVE:
      if(in.read()>5 && in.read()<8.8){
        out_treshold.write(t);
        out_flag.write(0);
        STATUS=DISABLED;
      }else if(in.read()<5){
        t=t*1.1;
        out_treshold.write(t);
        out_flag.write(1);
        STATUS=DISABLED;
      }else if(in.read()>8.8){
        t=t*0.7;
        out_treshold.write(t);
        out_flag.write(2);
        STATUS=DISABLED;
      }
      break;
  }
}else{
  i++;
}
}
