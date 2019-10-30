#include "xtea_UT.hh"

// constructor
// initialize the TLM socket
// no process, target works with function invocations from the initiator
xtea_UT::xtea_UT(sc_module_name name_)
  : sc_module(name_)
  , target_socket("target_socket")
  , pending_transaction(NULL)
{

  target_socket(*this);

}

void xtea_UT::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  // function invoked by the initiator

  // download data from the payload
  ioDataStruct = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    cout<<"\t\t[xtea:] Received invocation of the b_transport primitive - write"<<endl;
    cout<<"\t\t[xtea:] Invoking the xtea_function to calculate xtea"<<endl;

    // start elaboration
    // compute the functionality
    xtea_function();

    ioDataStruct.result0 = tmp_result0;
    ioDataStruct.result1 = tmp_result1;

    // and load it on the payload
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    cout<<"\t\t[xtea:] Returning result: "<<tmp_result0<<endl;
    cout<<"\t\t[xtea:] Returning result: "<<tmp_result1<<endl;
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  }
  else if (trans.is_read()){
    cout<<"\t\t[xtea:] Received invocation of the b_transport primitive - read"<<endl;

    // return the result
    ioDataStruct.result0 = tmp_result0;
    ioDataStruct.result1 = tmp_result1;

    // and load it on the payload
    *((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    cout<<"\t\t[xtea:] Returning result: "<<tmp_result0<<endl;
    cout<<"\t\t[xtea:] Returning result: "<<tmp_result1<<endl;
  }

}

void xtea_UT:: xtea_function()
{
  cout<<"\t\t[xtea:] Calculating xtea_function ... "<<endl;
  //tmp_result0 = sqrt((float)ioDataStruct.datain);
  tmp_result0 = ioDataStruct.datain_word1;
  tmp_result1 = ioDataStruct.datain_word2;
  sum = 0;
  temp = 0;

  if ( ioDataStruct.mode == 0 ){
    delta = 0x9e3779b9;
    for (i=0; i < 32; i++) {
          if((sum & 3) == 0)
            temp = ioDataStruct.datain_key0;
          else if((sum & 3) == 1)
            temp = ioDataStruct.datain_key1;
          else if ((sum & 3) == 2)
            temp = ioDataStruct.datain_key2;
          else temp = ioDataStruct.datain_key3;

          tmp_result0 += (((tmp_result1 << 4) ^ (tmp_result1 >> 5)) + tmp_result1) ^ (sum + temp);

          sum += delta;

          if(((sum>>11) & 3) == 0)
            temp = ioDataStruct.datain_key0;
          else if(((sum>>11) & 3) == 1)
            temp = ioDataStruct.datain_key1;
          else if (((sum>>11) & 3) == 2)
            temp = ioDataStruct.datain_key2;
          else temp = ioDataStruct.datain_key3;

          tmp_result1 += (((tmp_result0 << 4) ^ (tmp_result0 >> 5)) + tmp_result0) ^ (sum + temp);
        }

  }else if(ioDataStruct.mode == 1 ){

    sum = delta*32;

    for (i=0; i<32; i++) {

      if(((sum>>11) & 3) == 0)
        temp = ioDataStruct.datain_key0;
      else if(((sum>>11) & 3) == 1)
        temp = ioDataStruct.datain_key1;
      else if (((sum>>11) & 3) == 2)
        temp = ioDataStruct.datain_key2;
      else temp = ioDataStruct.datain_key3;

      tmp_result1 -= (((tmp_result0 << 4) ^ (tmp_result0 >> 5)) + tmp_result0) ^ (sum + temp);

      sum -= delta;

      if((sum & 3) == 0)
        temp = ioDataStruct.datain_key0;
      else if((sum & 3) == 1)
        temp = ioDataStruct.datain_key1;
      else if ((sum & 3) == 2)
        temp = ioDataStruct.datain_key2;
      else temp = ioDataStruct.datain_key3;

      tmp_result0 -= (((tmp_result1 << 4) ^ (tmp_result1 >> 5)) + tmp_result1) ^ (sum + temp);

    }
  }

}

// must be implemented to be compliant with the interface
// not significant in this code

bool xtea_UT::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum xtea_UT::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int xtea_UT::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
