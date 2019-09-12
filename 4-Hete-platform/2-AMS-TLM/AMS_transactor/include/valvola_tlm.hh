#ifndef Valvola_TRANSACTOR_HH
#define Valvola_TRANSACTOR_HH


#include <tlm.h>
#include "define_LT.hh"


class ValvolaTransactor :
  public sc_module,
  public virtual tlm::tlm_fw_transport_if<>
{
  public:
    tlm::tlm_target_socket<> target_socket;

    virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& t );
    virtual bool get_direct_mem_ptr(
        tlm::tlm_generic_payload& trans, tlm::tlm_dmi & dmi_data );

    virtual unsigned int transport_dbg( tlm::tlm_generic_payload& trans );

    void end_of_elaboration();
    void reset();

    virtual tlm::tlm_sync_enum nb_transport_fw(
        tlm::tlm_generic_payload& trans,
        tlm::tlm_phase& phase,
        sc_time& t);

    iostructV ioDataStruct;

    tlm::tlm_generic_payload* pending_transaction;

    sc_time timing_annotation;

    void transduce();

    SC_HAS_PROCESS(ValvolaTransactor);

    ValvolaTransactor(sc_module_name name);
    ~ValvolaTransactor();


    sc_out<int> flag_valvola;
    sc_out<double> threshold_valvola;

};


#endif
