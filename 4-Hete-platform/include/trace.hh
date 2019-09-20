#ifndef TRACE_HH
#define TRACE_HH

#define PERIOD 10

SC_MODULE(main_RTL){

  //sc_signal< sc_dt::sc_logic > clock;
  sc_signal<bool> clk;

  void clk_gen()
  {
    while( true )
    {
      /*clock.write( sc_dt::SC_LOGIC_1 );
      wait( PERIOD / 2, sc_core::SC_NS );
      clock.write( sc_dt::SC_LOGIC_0 );
      wait( PERIOD / 2, sc_core::SC_NS );*/
      clk.write( true ); //sc_dt::SC_LOGIC_1
      wait( PERIOD / 2, sc_core::SC_NS );
      clk.write( false ); //sc_dt::SC_LOGIC_0
      wait( PERIOD / 2, sc_core::SC_NS );
    }
  }

  //sc_signal < bool >        reset_signal;
  sc_signal < bool >        rst;

  /*sc_signal<bool >  	p_In_enable;
  sc_signal<sc_uint<8> > n1_int;
  sc_signal<sc_uint<8> > n2_int;
  sc_signal<sc_uint<8> > n1_mantix;
  sc_signal<sc_uint<8> > n2_mantix;
  sc_signal<bool >  	p_Out_enable;
  sc_signal<sc_uint<8> > result_portAI;
  sc_signal<sc_uint<8> > result_portAF;
  sc_signal<sc_uint<8> > result_portBI;
  sc_signal<sc_uint<8> > result_portBF;*/

  sca_tdf::sca_signal< int > m_flag;
  sca_tdf::sca_signal< double > m_threshold;
  sca_tdf::sca_signal< double > m_apertura;
  sc_signal< double > m_livello_acqua;
  sc_signal<int> m_flag_tlm;
  sc_signal<double> m_threshold_tlm;

  sc_signal<sc_uint<1> > input_rdy;
  sc_signal<sc_uint<32> > word1;
  sc_signal<sc_uint<32> > word2;
  sc_signal<sc_uint<32> > key0;
  sc_signal<sc_uint<32> > key1;
  sc_signal<sc_uint<32> > key2;
  sc_signal<sc_uint<32> > key3;
  sc_signal<sc_uint<1> > mode;
  sc_signal<sc_uint<32> > result0;
  sc_signal<sc_uint<32> > result1;
  sc_signal<sc_uint<1> > output_rdy;

  //Definition
  xtea_LT_testbench     i_src_LT; // source module
  xtea_LT               LT_xtea;
  //fixedPoint_RTL_transactor		i_fixedPoint_RTL_transactor;
  xtea_RTL_transactor   transactor; // xtea transactor
  //fixedPoint_RTL			i_fixedPoint_RTL;
  xtea_RTL              i_xtea_RTL; // xtea RTL module
  valvola               valv;
  serbatoio             serb;
  ValvolaTransactor     valvtr;
  SerbatoioTransactor   serbtr;
  valvola_iface         valvi;
  //xtea_LT_testbench		  tb;	       // source module

  SC_CTOR(main_RTL):
    valv("valv"),
    serb("serb"),
    valvtr("valvtr"),
    serbtr("serbtr"),
    valvi("valvi"),
    i_src_LT("i_src_LT"),
    //i_fixedPoint_RTL("i_fixedPoint_RTL"),
    //i_fixedPoint_RTL_transactor("i_fixedPoint_RTL_transactor")*/
    //tb("tb"),
    i_xtea_RTL("i_xtea_RTL"),
    transactor("transactor"),
    LT_xtea("LT_xtea")
  {

    SC_THREAD(clk_gen);

    i_src_LT.initiator_socket_valvola(valvtr.target_socket);
    //tb.initiator_socket(transactor.target_socket); */
    i_src_LT.initiator_socket(LT_xtea.target_socket);

    valvtr.flag_valvola(m_flag_tlm);
    valvtr.threshold_valvola(m_threshold_tlm);

    valvi.flag_controller(m_flag_tlm);
    valvi.threshold_controller(m_threshold_tlm);
    valvi.flag_valvola(m_flag);
    valvi.threshold_valvola(m_threshold);

    valv.flag(m_flag);
    valv.max_threshold(m_threshold);
    valv.apertura(m_apertura);

    serb.in(m_apertura);
    serb.out(m_livello_acqua);

    serbtr.livello_acqua_in(m_livello_acqua);

    i_src_LT.initiator_socket_serbatoio(serbtr.target_socket);
    i_src_LT.initiator_socket_rtl(transactor.target_socket);
    //i_src_LT.initiator_socket_rtl(i_fixedPoint_RTL_transactor.target_socket);

    // RTL design <-> Transactor binding (RTL interfaces)
    i_xtea_RTL.input_rdy(input_rdy);
    i_xtea_RTL.word1(word1);
    i_xtea_RTL.word2(word2);
    i_xtea_RTL.key0(key0);
    i_xtea_RTL.key1(key1);
    i_xtea_RTL.key2(key2);
    i_xtea_RTL.key3(key3);
    i_xtea_RTL.mode(mode);
    i_xtea_RTL.result0(result0);
    i_xtea_RTL.result1(result1);
    i_xtea_RTL.output_rdy(output_rdy);
    i_xtea_RTL.clk(clk); //(clock)
    i_xtea_RTL.rst(rst);

    /*i_fixedPoint_RTL.clk(clock);
    i_fixedPoint_RTL.reset(reset_signal);
    i_fixedPoint_RTL.number_isready(p_In_enable);
    i_fixedPoint_RTL.number_portAI(n1_int);
    i_fixedPoint_RTL.number_portAF(n1_mantix);
    i_fixedPoint_RTL.number_portBI(n2_int);
    i_fixedPoint_RTL.number_portBF(n2_mantix);
    i_fixedPoint_RTL.result_portAI(result_portAI);
    i_fixedPoint_RTL.result_portAF(result_portAF);
    i_fixedPoint_RTL.result_portBI(result_portBI);
    i_fixedPoint_RTL.result_portBF(result_portBF);
    i_fixedPoint_RTL.result_isready(p_Out_enable);

    i_fixedPoint_RTL_transactor.clk(clock);
    i_fixedPoint_RTL_transactor.reset_to_RTL(reset_signal);
    i_fixedPoint_RTL_transactor.p_In_enable(p_Out_enable);
    i_fixedPoint_RTL_transactor.result_portAI(result_portAI);
    i_fixedPoint_RTL_transactor.result_portAF(result_portAF);
    i_fixedPoint_RTL_transactor.result_portBI(result_portBI);
    i_fixedPoint_RTL_transactor.result_portBF(result_portBF);
    i_fixedPoint_RTL_transactor.p_Out_enable(p_In_enable);
    i_fixedPoint_RTL_transactor.number_portAI(n1_int);
    i_fixedPoint_RTL_transactor.number_portAF(n1_mantix);
    i_fixedPoint_RTL_transactor.number_portBI(n2_int);
    i_fixedPoint_RTL_transactor.number_portBF(n2_mantix);*/
    transactor.input_rdy(input_rdy);
    transactor.word1(word1);
    transactor.word2(word2);
    transactor.key0(key0);
    transactor.key1(key1);
    transactor.key2(key2);
    transactor.key3(key3);
    transactor.mode(mode);
    transactor.result0(result0);
    transactor.result1(result1);
    transactor.output_rdy(output_rdy);
    transactor.clk(clk); //(clock)
    transactor.rst(rst);

  }

};

#endif
