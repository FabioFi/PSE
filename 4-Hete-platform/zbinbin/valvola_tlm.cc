
//DA CANCELLARE


//questo collega il controller TLM a la valvola AMS.
//invece dovrebbe collegare l'RTL alla valvola AMS.


#include "valvola_tlm.hh"

ValvolaTransactor::ValvolaTransactor( sc_module_name name ) :
  sc_module( name ),
  target_socket( "target_socket" ),
  pending_transaction( NULL )
{
  target_socket( *this );
}

void ValvolaTransactor::b_transport(
    tlm::tlm_generic_payload& trans,
    sc_time & t )
{
  //b_transport
  ioDataStruct = *((iostructV*) trans.get_data_ptr());
  transduce();
  trans.set_response_status(tlm::TLM_OK_RESPONSE);
  trans.set_data_ptr((unsigned char*) &ioDataStruct);

}

bool ValvolaTransactor::get_direct_mem_ptr(
    tlm::tlm_generic_payload& trans,
    tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum ValvolaTransactor::nb_transport_fw(
    tlm::tlm_generic_payload& trans,
    tlm::tlm_phase& phase,
    sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int ValvolaTransactor::transport_dbg(
    tlm::tlm_generic_payload& trans)
{
  return 0;
}

void ValvolaTransactor::transduce()
{
  flag_valvola.write(ioDataStruct.flag);
  threshold_valvola.write(ioDataStruct.threshold);
}

void ValvolaTransactor::end_of_elaboration()
{

}

void ValvolaTransactor::reset()
{
}

ValvolaTransactor::~ValvolaTransactor()
{
}
