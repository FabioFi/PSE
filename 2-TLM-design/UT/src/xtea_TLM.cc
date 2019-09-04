#include "xtea_TLM.hh"

xtea_TLM::xtea_TLM(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
  {
    target_socket(*this);
  }

void xtea_TLM::b_transport(tlm::tlm_generic_payload& trans, sc_time& t){

  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    root_function();
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    ioDataStruct.result = tmp_result;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  } 
  else if (trans.is_read()){
    ioDataStruct.result = tmp_result;
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
  }

}

bool xtea_TLM::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data){
  return false;
}

tlm::tlm_sync_enum xtea_TLM::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t){
  return tlm::TLM_COMPLETED;
}

unsigned int xtea_TLM::transport_dbg(tlm::tlm_generic_payload& trans){
  return 0;
}

void xtea_TLM:: root_function(){
  //tmp_result = sqrt((float)ioDataStruct.datain);
  //mettere tutto il codice
}

/* Initialization:
void xtea_TLM:: end_of_elaboration(){

}

void xtea_TLM:: reset(){

}*/


//------------------------------------------------------

/*xtea_TLM::xtea_TLM(sc_core::sc_module_name module_name) :
    sc_module(module_name),
    input_rdy("input_rdy"),
    word1("word1"),
    word2("word2"),
    key0("key0"),
    key1("key1"),
    key2("key2"),
    key3("key3"),
    //key4("key4"),
    mode("mode"),
    result0("result0"),
    result1("result1"),
    output_rdy("output_rdy"),
    rst("rst"),
    clk("clk")
{
  SC_METHOD(datapath);
  sensitive << rst.neg();
  sensitive << clk.pos();

  SC_METHOD(fsm);
  sensitive << STATUS << input_rdy << word1 << word2 << key0 << key1 << key2 << key3 << mode
  << sum << counter << output_rdy;

}

xtea_TLM::~xtea_TLM(){}

void xtea_TLM::datapath(void){
  if(rst.read() == 0){
    STATUS = Reset_ST;
  } else if(clk.read() == 1){
    //cout << clk << "a" << endl;

    STATUS = NEXT_STATUS;

    switch(STATUS){
      case Reset_ST:
        result0.write(0);
        result1.write(0);
        output_rdy.write(0);
      break;

      case ST_0:
        result0.write(0);
        result1.write(0);
        output_rdy.write(0);
        //word1.write(0);
        //word2.write(0);
        //key0.write(0);
        //key1.write(0);
        //key2.write(0);
        //key3.write(0);
        //input_rdy.write(0);
        counter.write(0);
      //  delta.write(0);
        v0.write(0);
        v1.write(0);
        sum.write(0);
        temp0.write(0);
        temp1.write(0);
        delta.write(0x9e3779b9);
      break;

      case ST_1:
        v0.write(word1.read());
        v1.write(word2.read());
      //  if(mode.read() == 1){
        //  sum.write(delta.read() * 32);
        //}
      //  cout << sum.read() <<endl;

      break;

      case ST_2:
      cout << counter.read() << endl;
      cout << "v0: "<< v0.read() << endl;
      cout << "v1: "<< v1.read() << endl;

        if((sum.read() & 3) == 0)
          temp0.write(key0.read());
        else if((sum.read() & 3) == 1)
          temp0.write(key1.read());
        else if((sum.read() & 3) == 2)
          temp0.write(key2.read());
        else temp0.write(key3.read());
      break;

      case ST_3:
        sum.write(delta.read() * 32);
      break;

      case ST_4:
        v0.write(v0.read() + (((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp0.read()))));
        sum.write(sum.read() + delta.read());
      break;

      case ST_5:

        if(((sum.read() >> 11) & 3) == 0)
          temp0.write(key0.read());
        else if(((sum.read() >> 11) & 3) == 1)
          temp0.write(key1.read());
        else if(((sum.read() >> 11) & 3) == 2)
          temp0.write(key2.read());
        else temp0.write(key3.read());

      break;

      case ST_6:

      if(((sum.read() >> 11) & 3) == 0)
        temp0.write(key0.read());
      else if(((sum.read() >> 11) & 3) == 1)
        temp0.write(key1.read());
      else if(((sum.read() >> 11) & 3) == 2)
        temp0.write(key2.read());
      else temp0.write(key3.read());
      break;

      case ST_7:
      v1.write(v1.read() - (((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp0.read()))));
      sum.write(sum.read() - delta.read());

      break;

      case ST_8:
      v1.write(v1.read() + (((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp0.read()))));

//        v1.write(v1.read() + (((v0.read() << 4) ^ (v0.read() >> 5) + v0.read()) ^ (sum.read() + temp0.read())));
        if(counter.read() < 31){
          counter.write(counter.read() + 1);
        }
      break;

      case ST_9:

        if((sum.read() & 3) == 0)
          temp0.write(key0.read());
        else if((sum.read() & 3) == 1)
          temp0.write(key1.read());
        else if((sum.read() & 3) == 2)
          temp0.write(key2.read());
        else temp0.write(key3.read());

      break;


      case ST_10:
      v0.write(v0.read() - (((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp0.read()))));

        if(counter.read() < 31){
          counter.write(counter.read() + 1);
        }

      break;

      case Final_ST:
        result0.write(v0.read());
        result1.write(v1.read());
        output_rdy.write(1);
      break;
    }
  }
}

void xtea_TLM::fsm(void){

  NEXT_STATUS = STATUS;

  switch(STATUS){
    case Reset_ST:
      NEXT_STATUS = ST_0;
    break;

    case ST_0:
      if(input_rdy.read() == 1){
        NEXT_STATUS = ST_1;
      }
      else {
        NEXT_STATUS = ST_0;
      }
    break;

    case ST_1:
      if(mode.read() == 0){
        NEXT_STATUS = ST_2;
      }
      else if(mode.read() == 1){
        NEXT_STATUS = ST_3;
      }
    break;

    case ST_2:
      NEXT_STATUS = ST_4;
    break;

    case ST_3:
      NEXT_STATUS = ST_5;
    break;

    case ST_4:
      NEXT_STATUS = ST_6;
    break;

    case ST_5:
      NEXT_STATUS = ST_7;
    break;

    case ST_6:
      NEXT_STATUS = ST_8;
    break;

    case ST_7:
      NEXT_STATUS = ST_9;
    break;

    case ST_8:
    if(counter.read() < 31){
      NEXT_STATUS = ST_2;
    } else
      NEXT_STATUS = Final_ST;
    break;

    case ST_9:
      NEXT_STATUS = ST_10;
    break;

    case ST_10:
      if(counter.read() < 31){
        NEXT_STATUS = ST_5;
      } else
      NEXT_STATUS = Final_ST;
    break;

    case Final_ST:
  //  cout << "result" <<endl;
      NEXT_STATUS = ST_0;
    break;
  }
}*/
