#include "xtea_LT_testbench.hh"

void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{

}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - nb_transport_bw"<<endl;
  return tlm::TLM_COMPLETED;
}

void xtea_LT_testbench::run()
{

  sc_time local_time = m_qk.get_local_time();

  // First transaction (initialization)
  iostruct xtea_packet;
  tlm::tlm_generic_payload payload;

//  for (int i = 1; i <= 128; i++){
    cout<<sc_simulation_time()<<" - "<<name()<<" - run"<<endl;

    /*xtea_packet.datain = (rand() % 256);
    cout <<"The square xtea of : " << xtea_packet.datain << endl;
    payload.set_data_ptr((unsigned char*) &xtea_packet);
    payload.set_address(0);
    payload.set_write();*/

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

    // update the local time variable to send it to the target
    local_time = m_qk.get_local_time();

    // start write transaction
    cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    payload.set_read();
    initiator_socket->b_transport(payload, local_time);

    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      //cout<< "... is: " << xtea_packet.result << endl;
      cout<<"[TB:] TLM protocol correctly implemented"<<endl;
      cout<<"[TB:] Result is: " << std::hex << xtea_packet.result0 << ", " << std::hex << xtea_packet.result1 << endl;
      if((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644))
        printf("Wrong result!\n");
    }

    // temporal decoupling> get time and check if we have to synchronize with the target
    cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    m_qk.set(local_time);
    if (m_qk.need_sync()) {
      // synchronize simulation time
      cout << "SYNCHRONIZING" << endl;
      m_qk.sync();
      cout << "#####################" << endl;
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

    // update the local time variable to send it to the target
    local_time = m_qk.get_local_time();

    // start write transaction
    cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    payload.set_read();
    initiator_socket->b_transport(payload, local_time);

    if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
      // check that the protocol has been correctly implemented
      // and print the result
      cout<<"[TB:] TLM protocol correctly implemented"<<endl;
      cout<<"[TB:] Result is: " << std::hex << xtea_packet.result0 << ", " << std::hex << xtea_packet.result1 << endl;
      if((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff))
        printf("Wrong result!\n");
    }

    // temporal decoupling> get time and check if we have to synchronize with the target
    cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    m_qk.set(local_time);
    if (m_qk.need_sync()) {
      // synchronize simulation time
      cout << "SYNCHRONIZING" << endl;
      m_qk.sync();
      cout << "#####################" << endl;
    }

    printf("Done!!\n");    

//  }
  sc_stop();

}

xtea_LT_testbench::xtea_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket(*this);

  SC_THREAD(run);

  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}