#include "xtea_RTL_transactor.hh"

//Mi arriva il valore threshold dal controllore TLM cifrato, lo devo passare all'RTL.

// INTERFACE SIDE:
//****************
xtea_RTL_transactor::xtea_RTL_transactor(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  {

    target_socket(*this);

    SC_THREAD(WRITEPROCESS);
    sensitive_pos<<clk;
    SC_THREAD(READPROCESS);
    sensitive_pos<<clk;

  }

void xtea_RTL_transactor::b_transport(tlm::tlm_generic_payload& trans, sc_time& t){
  cout<<sc_simulation_time()<<" - "<<name()<<" - b_transport"<<endl;
  wait(0, SC_NS);
  tlm::tlm_command trans_command=trans.get_command();

  switch(trans_command){
    case tlm::TLM_WRITE_COMMAND:
      ioDataStruct=*((iostruct*) trans.get_data_ptr());
      trans.set_response_status(tlm::TLM_OK_RESPONSE);
      begin_write.notify();
      cout<<"\t write notified - xtea_RTL_transactor::b_transport"<<endl;
      wait(end_write);
      break;

    case tlm::TLM_READ_COMMAND:
     ioDataStruct = *((iostruct*) trans.get_data_ptr());
     trans.set_response_status(tlm::TLM_OK_RESPONSE);
     begin_read.notify();
     cout<<"\t read notified - xtea_RTL_transactor::b_transport"<<endl;
     wait(end_read);
     *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
     break;

  //  default:
    // break;
  }
  cout<<sc_simulation_time()<<" - "<<name()<<" - b_transport ended"<<endl;
}


void xtea_RTL_transactor::WRITEPROCESS()
{

while (true) {
  wait(begin_write);
  //cout<<sc_simulation_time()<<" - "<<name()<<" - notify received !!!"<<endl;

  // rst.write(0);
  // wait();
  // rst.write(1);

  sc_uint<32> w0, w1, k0, k1, k2, k3 = 0;
  sc_uint<32> r0, r1;
  w0 = ioDataStruct.result0; //0x12345678; //result0.write(ioDataStruct.result0);
  w1 = ioDataStruct.result1; //0x9abcdeff; //result1.write(ioDataStruct.result1);
  k0 = 0x6a1d78c8;
  k1 = 0x8c86d67f;
  k2 = 0x2a65bfbe;
  k3 = 0xb4bd6e46;
  cout << "[RTL transactor:] w0: " /*<< std::hex*/ << w0 << " w1: " /*<< std::hex*/ << w1 << "------------(RTL transactor)" << endl;
  //result0.write(ioDataStruct.n2); //aprire / chiudere / nulla
  //result1.write(ioDataStruct.n1); //threshold
  //word2.write(ioDataStruct.n2); //aprire / chiudere / nulla
  rst.write(1);
  word1.write(w0);
  word2.write(w1);
  key0.write(k0);
  key1.write(k1);
  key2.write(k2);
  key3.write(k3);
  mode.write(1); //decryption (con 0 ho encryption)
  input_rdy.write(1);
  //output_rdy.write(1);

	end_write.notify();
	wait();
  }
}


void xtea_RTL_transactor::READPROCESS()
{
while (true) {
	wait(begin_read);
  cout<<sc_simulation_time()<<" - "<<name()<<" - notify received"<<endl;
    while(output_rdy.read() != 1)
		wait();

  /*res_uint=(result_portBF.read(),result_portBI.read(),result_portAF.read(),result_portAI.read());
  risultato.range(31,16)=res_uint(31,16);
  risultato.range(15,0)=res_uint(15,0);
	ioDataStruct.result=risultato;*/

  //non dovrei fare nulla perchè non aspetto i dati da qualche altra parte
  //ioDataStruct.result0=result0.read();
  //ioDataStruct.result1=result1.read();
	end_read.notify();
  }

}

void xtea_RTL_transactor :: end_of_elaboration(){
  reset();
}

void xtea_RTL_transactor :: reset(){
  /*reset_to_RTL.write(0);
  p_Out_enable.write(0);
  number_portAI.write(0);
  number_portBI.write(0);
  number_portAF.write(0);
  number_portBF.write(0);*/
  cout <<sc_simulation_time()<<" - "<<name()<<" - reset (xtea_RTL_transactor)"<<endl;
  rst.write(0);
  //din_rdy.write(0);
  //output_rdy.write(0);
  //din.write(0);
  //result0.write(0);
  //result1.write(0);

}

bool xtea_RTL_transactor::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}



tlm::tlm_sync_enum xtea_RTL_transactor::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{

  return tlm::TLM_UPDATED;

}



unsigned int xtea_RTL_transactor::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
