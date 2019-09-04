#include "xtea_TLM_testbench.hh"

void xtea_TLM_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range){

}

tlm::tlm_sync_enum xtea_TLM_testbench::nb_transport_bw(tlm::tlm_generic_payload & trans, tlm::tlm_phase &  phase, sc_time &  t){
  return tlm::TLM_COMPLETED;
}

void xtea_TLM_testbench::run(){

  sc_time local_time;
  // First transaction (initialization)
  iostruct xtea_packet;
  tlm::tlm_generic_payload payload;	

  //inizializzo tutti i dati e poi li passo a xtea

  /*for (int i = 1; i <= 10000000; i++){
    root_packet.datain = (rand() % 256);
    //cout<<"\tThe square root of "<<root_packet.datain;
    payload.set_data_ptr((unsigned char*) &root_packet);
    payload.set_address(0);
    payload.set_write();
    
    // start write transaction
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      //cout << "\t is: " << root_packet.result << endl;
    }

  }*/

  sc_stop();

}

xtea_TLM_testbench::xtea_TLM_testbench(sc_module_name name)
  : sc_module(name){

    initiator_socket(*this);

    SC_THREAD(run);

  }

//-------------------------------------------

/*xtea_TLM_testbench::xtea_TLM_testbench(sc_module_name name_):sc_module(name_){

  SC_THREAD(run);
  sensitive << clk.pos();

  SC_THREAD(clk_gen);
}

void xtea_TLM_testbench::clk_gen(){
    while( true ){
        clk.write( true );
        wait(PERIOD / 2, sc_core::SC_NS);
        clk.write( false );
        wait(PERIOD / 2, sc_core::SC_NS);

    }
}

void xtea_TLM_testbench::run(){

  sc_uint<32> w0, w1, k0, k1, k2, k3 = 0;

  sc_uint<32> r0, r1;

  w0 = 0x12345678;
  w1 = 0x9abcdeff;
  
  k0 = 0x6a1d78c8;
  k1 = 0x8c86d67f;
  k2 = 0x2a65bfbe;
  k3 = 0xb4bd6e46;

  rst.write(1);
  word1.write(w0);
  word2.write(w1);
  key0.write(k0);
  key1.write(k1);
  key2.write(k2);
  key3.write(k3);
  mode.write(0);
  input_rdy.write(1);

  wait();


  while(output_rdy.read() != 1) wait();
  r0 = result0.read();
  r1 = result1.read();

  cout << "First invocation: \n";
  cout << "   - the encryption of " << std::hex << w0 << " and " << std::hex << w1 << "\n";
  cout << "   - with key " << std::hex << k0 << k1 << k2 << k3 << "\n";
  cout << "is: " << r0 << ", " << r1 <<  "\n\n";
  if((r0 != 0x99bbb92b) || (r1 != 0x3ebd1644))
    printf("Wrong result!\n");

  printf("Second invocation: \n");
  rst.write(1);

  w0 = result0.read();
  w1 = result1.read();
  k0 = 0x6a1d78c8;
  k1 = 0x8c86d67f;
  k2 = 0x2a65bfbe;
  k3 = 0xb4bd6e46;

  word1.write(w0);
  word2.write(w1);
  key0.write(k0);
  key1.write(k1);
  key2.write(k2);
  key3.write(k3);
  mode.write(1);
  input_rdy.write(1);

  wait();

  while(output_rdy.read() != 1) wait();
  r0 = result0.read();
  r1 = result1.read();

  cout << "   - the decryption of " << w0 << " and " << w1 << "\n";
  cout << "   - with key " << std::hex << k0 << k1 << k2 << k3 << "\n";
  cout << "is: " << r0 << ", " << r1 <<  "\n\n";

  if((r0 != 0x12345678) || (r1 != 0x9abcdeff))
    printf("Wrong result!");

  printf("Done!!\n");

  rst.write(0);
  word1.write(0);
  word2.write(0);
  key0.write(0);
  key1.write(0);
  key2.write(0);
  key3.write(0);
  mode.write(0);
  input_rdy.write(0);

  sc_stop();

}*/
