#include "xtea_UT_testbench.hh"

void xtea_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{

}

tlm::tlm_sync_enum xtea_UT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  return tlm::TLM_COMPLETED;
}


void xtea_UT_testbench::run()
{

  sc_time local_time;
  iostruct xtea_packet;
  tlm::tlm_generic_payload payload;

for(int y = 0; y < 10000; y++){
  // send one random number - write invocation
  xtea_packet.datain_word1 = 0x12345678;
  xtea_packet.datain_word2 = 0x9abcdeff;
  xtea_packet.datain_key0 = 0x6a1d78c8;
  xtea_packet.datain_key1 = 0x8c86d67f;
  xtea_packet.datain_key2 = 0x2a65bfbe;
  xtea_packet.datain_key3 = 0xb4bd6e46;

  xtea_packet.result0 = 0;
  xtea_packet.result1 = 0;
  xtea_packet.mode = 0; //false (encryption)

  cout << "First invocation: \n";
  cout << " - the encryption of " << std::hex << xtea_packet.datain_word1 << " and " << std::hex << xtea_packet.datain_word2 << endl;
  cout << " - with key " << std::hex << xtea_packet.datain_key0 << xtea_packet.datain_key1 << xtea_packet.datain_key2 << xtea_packet.datain_key3 << "\n";


  payload.set_data_ptr((unsigned char*) &xtea_packet); // set payload data
  payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator
  payload.set_write(); // write transaction

  cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
  initiator_socket->b_transport(payload, local_time); // invoke the transport primitive

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    // check that the protocol has been correctly implemented
    // and print the result

    cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    cout<<"[TB:] Result is: " << std::hex << xtea_packet.result0 << ", " << std::hex << xtea_packet.result1 << endl;
    if((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644))
      printf("Wrong result!\n");
  }

  //-----------------------DECRYPTION-------------------------------------------

  xtea_packet.datain_word1 = xtea_packet.result0;
  xtea_packet.datain_word2 = xtea_packet.result1;
  xtea_packet.result0 = 0;
  xtea_packet.result1 = 0;
  xtea_packet.mode = 1; //true (decryption)

  cout << "Second invocation: \n";
  cout << " - the decryption of " << std::hex << xtea_packet.datain_word1 << " and " << std::hex << xtea_packet.datain_word2 << endl;
  cout << " - with key " << std::hex << xtea_packet.datain_key0 << xtea_packet.datain_key1 << xtea_packet.datain_key2 << xtea_packet.datain_key3 << "\n";

  payload.set_data_ptr((unsigned char*) &xtea_packet); // set payload data
  payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator
  payload.set_write(); // write transaction

  cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
  initiator_socket->b_transport(payload, local_time); // invoke the transport primitive

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    // check that the protocol has been correctly implemented
    // and print the result
    cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    cout<<"[TB:] Result is: " << std::hex << xtea_packet.result0 << ", " << std::hex << xtea_packet.result1 << endl;
    if((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff))
      printf("Wrong result!\n");
  }
}
  printf("Done!!\n");

  sc_stop();

}

// constructor to initialize the TLM socket and the main thread
xtea_UT_testbench::xtea_UT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);
  SC_THREAD(run);

}
