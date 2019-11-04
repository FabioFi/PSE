#include "serbatoio_TLM.hh"
#define TRACING

SerbatoioTransactor::SerbatoioTransactor( sc_module_name name ) :
  sc_module( name ),
  target_socket( "target_socket" ),
  pending_transaction( NULL )
{
  target_socket( *this );

  #ifdef TRACING
    SC_THREAD( _trace );
    log = fopen("logs/execution.log", "w");
  #endif
}

void SerbatoioTransactor::b_transport(tlm::tlm_generic_payload& trans, sc_time & t )
{
  //b_transport
  ioDataStruct = *((iostructT*) trans.get_data_ptr());
  transduce();
  trans.set_response_status(tlm::TLM_OK_RESPONSE);
  *((iostructT*) trans.get_data_ptr()) = ioDataStruct;

}

bool SerbatoioTransactor::get_direct_mem_ptr(
    tlm::tlm_generic_payload& trans,
    tlm::tlm_dmi& dmi_data)
{
  return false;
}

tlm::tlm_sync_enum SerbatoioTransactor::nb_transport_fw(
    tlm::tlm_generic_payload& trans,
    tlm::tlm_phase& phase,
    sc_time& t)
{
  return tlm::TLM_COMPLETED;
}

unsigned int SerbatoioTransactor::transport_dbg(
    tlm::tlm_generic_payload& trans)
{
  return 0;
}

void SerbatoioTransactor::transduce()
{
  ioDataStruct.livello_acqua = livello_acqua_in.read();
}

void SerbatoioTransactor::end_of_elaboration()
{

}

void SerbatoioTransactor::reset()
{
}

SerbatoioTransactor::~SerbatoioTransactor()
{


#ifdef TRACING
  if( log != NULL ) fclose(log);
#endif
}

#ifdef TRACING
void SerbatoioTransactor::_trace()
{
  while(true)
  {
    wait(1, sc_core::SC_MS);
    fprintf( log, "%f %f\n", sc_time_stamp().to_seconds(), livello_acqua_in.read() );
  }
}
#endif
