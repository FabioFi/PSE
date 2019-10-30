#include "xtea_AT4.hh"

// transport function invoked by the initiator
tlm::tlm_sync_enum xtea_AT4::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t)
{
  // If there is already a pending transaction, we refuse to
  // serve the request because something went wrong
  if (pending_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  // Phase must be BEGIN_REQ (begin request), otherwise we set an
  // error response and complete the transaction.
  if (phase != tlm::BEGIN_REQ) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return tlm::TLM_COMPLETED;
  }

  cout<<"\t\t[xtea:] Received invocation of the nb_transport_fw primitive"<<endl;
  cout<<"\t\t[xtea:] Activating the IOPROCESS"<<endl;
  pending_transaction = &trans; // download the payload
  ioDataStruct = *((iostruct*) trans.get_data_ptr()); // get the data

  phase = tlm::END_REQ; // pahse is end request now, target accepted to process the data

  // activate the ioprocess process to elaborate data and to
  io_event.notify();

  // return control
  cout<<"\t\t[xtea:] End of the nb_transport_fw primitive"<<endl;
  return tlm::TLM_UPDATED;

}


void xtea_AT4::IOPROCESS()
{

  sc_time timing_annotation;

  while (true) {
    wait(io_event);
    // if I am here, then the initiator has invoked the forward transport primitive to issue a request

    cout<<"\t\t[xtea:] IOPROCESS has been activated"<<endl;

    // Wait 100ns to model the delay required to
    // process the request - simulate advamncement of time

    wait(100, SC_NS);

    if (pending_transaction->is_write()) {
      // write request: elaborate the square xtea and return
      cout<<"\t\t[xtea:] Invoking the xtea_function to calculate the square xtea"<<endl;
      xtea_function();
    }

    // read transaction: return the result to the initiator
    else{
      ioDataStruct.result0 = tmp_result0;
      ioDataStruct.result1 = tmp_result1;

      cout<<"\t\t[xtea:] Returning result: "<<tmp_result0<<endl;
      cout<<"\t\t[xtea:] Returning result: "<<tmp_result1<<endl;
    }

    // transaction went on correctly
    pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);

    // upload data and set phase to begin response
    *((iostruct*) pending_transaction->get_data_ptr()) = ioDataStruct;
    tlm::tlm_phase phase = tlm::BEGIN_RESP;

    cout<<"[TB:] Invoking the nb_transport_bw primitive - write"<<endl;
    target_socket->nb_transport_bw(*pending_transaction, phase, timing_annotation); // transport primitive in the initiator - ends the AT4 protocol

    pending_transaction = NULL;

  }

}

// elaboration function
void xtea_AT4:: xtea_function()
{
  cout<<"\t\t[xtea:] Calculating xtea_function ... "<<endl;
  //ioDataStruct.result = sqrt((float)ioDataStruct.datain);
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

  //ioDataStruct.result0 = tmp_result0;
  //ioDataStruct.result1 = tmp_result1;

}

// constructor
// initialize TLM socket and set ioprocess as a thread
xtea_AT4::xtea_AT4(sc_module_name name_)
: sc_module(name_)
, target_socket("target_socket")
, pending_transaction(NULL)
{

  target_socket(*this);

  SC_THREAD(IOPROCESS);

}


// necessary to be compliant with the standard
// not used here
void xtea_AT4::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{

}

bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  return false;
}

unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload& trans)
{
  return 0;
}
