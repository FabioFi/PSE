// /////////////////////////////////////////////////////////////////////////
// C++ code automatically generated by hif2sc
// Part of HIFSuite - Version 2017.05.1-antlia
// Site: www.hifsuite.com - Contact: hifsuite@edalab.it
//
// HIFSuite copyright: EDALab s.r.l. - Networked Embedded Systems
// Site: www.edalab.it - Contact: info@edalab.it
// /////////////////////////////////////////////////////////////////////////


#ifndef M6502_HH
#define M6502_HH

#include <stdint.h>

class m6502
{

public:


    uint8_t hif_cone_when();

    bool rdy_old;
    bool res_n_old;
    bool sob_n_old;
    bool nmi_n_old;
    bool irq_n_old;
    uint8_t datai_old;
    bool clk_old;
    struct m6502_iostruct{
        bool clk;
        uint16_t addr;
        uint8_t datai;
        uint8_t datao;
        bool irq_n;
        bool nmi_n;
        bool sob_n;
        bool res_n;
        bool rdy;
        bool vpab;
        bool sync;
        bool we_n;
        bool oeb;

        m6502_iostruct():
            clk(false),
            addr(uint16_t(0U)),
            datai(uint8_t(0U)),
            datao(uint8_t(0U)),
            irq_n(false),
            nmi_n(false),
            sob_n(false),
            res_n(false),
            rdy(false),
            vpab(false),
            sync(false),
            we_n(false),
            oeb(false)
        {}

        m6502_iostruct( const bool clk_0, const uint16_t addr_0, const uint8_t datai_0,
             const uint8_t datao_0, const bool irq_n_0, const bool nmi_n_0, const
             bool sob_n_0, const bool res_n_0, const bool rdy_0, const bool vpab_0,
             const bool sync_0, const bool we_n_0, const bool oeb_0 ):
            clk(clk_0),
            addr(addr_0),
            datai(datai_0),
            datao(datao_0),
            irq_n(irq_n_0),
            nmi_n(nmi_n_0),
            sob_n(sob_n_0),
            res_n(res_n_0),
            rdy(rdy_0),
            vpab(vpab_0),
            sync(sync_0),
            we_n(we_n_0),
            oeb(oeb_0)
        {}

        ~m6502_iostruct()
        {}

        bool operator == (const m6502_iostruct & other) const
        {
            if (clk != other.clk) return false;
            if (addr != other.addr) return false;
            if (datai != other.datai) return false;
            if (datao != other.datao) return false;
            if (irq_n != other.irq_n) return false;
            if (nmi_n != other.nmi_n) return false;
            if (sob_n != other.sob_n) return false;
            if (res_n != other.res_n) return false;
            if (rdy != other.rdy) return false;
            if (vpab != other.vpab) return false;
            if (sync != other.sync) return false;
            if (we_n != other.we_n) return false;
            if (oeb != other.oeb) return false;
            return true;
        }
    };
    m6502_iostruct hif_a2t_data;
    bool core_sm_psrl_7;
    bool core_sm_psrl_6;
    bool core_sm_psrl_5;
    bool core_sm_psrl_4;
    bool core_sm_psrl_3;
    bool core_sm_psrl_2;
    bool core_sm_psrl_1;
    bool core_sm_psrl_0;
    bool core_alu_dcd_7;
    bool core_alu_dcd_6;
    bool core_alu_dcd_5;
    bool core_alu_dcd_4;
    bool core_alu_dcd_3;
    bool core_alu_dcd_2;
    bool core_alu_dcd_1;
    bool core_alu_dcd_0;
    bool core_alu_bcd_out_7;
    bool core_alu_bcd_out_6;
    bool core_alu_bcd_out_5;
    bool core_alu_bcd_out_4;
    bool core_alu_bcd_out_3;
    bool core_alu_bcd_out_2;
    bool core_alu_bcd_out_1;
    bool core_alu_bcd_out_0;
    bool core_alu_add_out_7;
    bool core_alu_add_out_6;
    bool core_alu_add_out_5;
    bool core_alu_add_out_4;
    bool core_alu_add_out_3;
    bool core_alu_add_out_2;
    bool core_alu_add_out_1;
    bool core_alu_add_out_0;
    bool core_adhmx_pre_y_7;
    bool core_adhmx_pre_y_6;
    bool core_adhmx_pre_y_5;
    bool core_adhmx_pre_y_4;
    bool core_adhmx_pre_y_3;
    bool core_adhmx_pre_y_2;
    bool core_adhmx_pre_y_1;
    bool core_adhmx_pre_y_0;
    bool we_n_out_sig;
    bool vpa;
    bool oen;
    uint8_t core_addrh;
    uint8_t core_addrl;
    uint8_t core_dataol;
    uint8_t core_xregl;
    uint8_t core_yregl;
    uint8_t core_sregl;
    uint8_t core_aregl;
    uint8_t core_dregl;
    uint8_t core_alu_outl;
    uint8_t core_pchl;
    uint8_t core_pcll;
    uint8_t core_psrl;
    uint16_t core_alu_ctl;
    uint8_t core_alu2op;
    uint8_t core_alu_ld;
    uint8_t core_rg_load;
    bool core_sreg_up;
    bool core_sreg_cen;
    uint8_t core_pc_ctl;
    uint8_t core_adl_sel;
    uint8_t core_adh_sel;
    uint8_t core_domux_sel;
    bool core_reset;
    bool core_adhmx_pre_y_partial7;
    bool core_adhmx_pre_y_partial6;
    bool core_adhmx_pre_y_partial5;
    bool core_adhmx_pre_y_partial4;
    bool core_adhmx_pre_y_partial3;
    bool core_adhmx_pre_y_partial2;
    bool core_adhmx_pre_y_partial1;
    bool core_adhmx_pre_y_partial0;
    uint8_t core_drg_ido;
    uint8_t core_drg_idi;
    bool core_drg_ld;
    uint8_t core_srg_dataol;
    uint8_t core_pc_cntih;
    uint8_t core_pc_cntil;
    uint8_t core_pc_hreg;
    uint8_t core_pc_hreg_in;
    uint16_t core_pc_pc;
    uint8_t core_arg_ido;
    uint8_t core_xrg_ido;
    uint8_t core_yrg_ido;
    uint8_t core_adlmx_lreg;
    uint8_t core_adlmx_lrg_ido;
    uint8_t core_alu_jreg;
    uint8_t core_alu_kreg;
    uint8_t core_alu_add_b;
    uint8_t core_alu_log_b_preinv;
    uint8_t core_alu_log_b;
    uint8_t core_alu_log_out;
    bool core_alu_dcd_partial7;
    bool core_alu_dcd_partial6;
    bool core_alu_dcd_partial5;
    bool core_alu_dcd_partial4;
    bool core_alu_dcd_partial3;
    bool core_alu_dcd_partial2;
    bool core_alu_dcd_partial1;
    bool core_alu_dcd_partial0;
    uint8_t core_alu_log_ctl;
    uint8_t core_alu_alu_outl;
    bool core_alu_add_sub;
    bool core_alu_add_cin;
    bool core_alu_add_cout4;
    bool core_alu_add_cout;
    bool core_alu_alu_cout;
    bool core_alu_log_cin;
    bool core_alu_log_cout;
    bool core_alu_bcd_en;
    bool core_alu_bcd_cout;
    uint8_t core_alu_sign_ext;
    bool core_alu_z_flag;
    bool core_alu_n_flag;
    bool core_alu_v_flag;
    bool core_alu_bra_carry;
    uint8_t core_alu_adder_b_sub;
    uint8_t core_alu_adder_sub_v;
    bool core_alu_adder_cout4l;
    bool core_alu_adder_addh_sum_partial3;
    bool core_alu_adder_addh_sum_partial2;
    bool core_alu_adder_addh_sum_partial1;
    bool core_alu_adder_addh_sum_partial0;
    bool core_alu_adder_addh_cry_partial3;
    bool core_alu_adder_addh_cry_partial2;
    bool core_alu_adder_addh_cry_partial1;
    bool core_alu_adder_addh_cry_partial0;
    bool core_alu_adder_addl_sum_partial3;
    bool core_alu_adder_addl_sum_partial2;
    bool core_alu_adder_addl_sum_partial1;
    bool core_alu_adder_addl_sum_partial0;
    bool core_alu_adder_addl_cry_partial3;
    bool core_alu_adder_addl_cry_partial2;
    bool core_alu_adder_addl_cry_partial1;
    bool core_alu_adder_addl_cry_partial0;
    uint8_t core_alu_bcd_b_partial1;
    uint8_t core_alu_bcd_b_partial0;
    bool core_alu_bcd_cout4;
    bool core_alu_bcd_cin4l;
    bool core_alu_bcd_cout8;
    bool core_alu_bcd_gnd;
    bool core_alu_bcd_lo_adj;
    bool core_alu_bcd_hi_adj;
    bool core_alu_bcd_lo_adj_sub;
    bool core_alu_bcd_hi_adj_sub;
    bool core_alu_bcd_addh_sum_partial3_0;
    bool core_alu_bcd_addh_sum_partial2_0;
    bool core_alu_bcd_addh_sum_partial1_0;
    bool core_alu_bcd_addh_sum_partial0_0;
    bool core_alu_bcd_addh_cry_partial3_0;
    bool core_alu_bcd_addh_cry_partial2_0;
    bool core_alu_bcd_addh_cry_partial1_0;
    bool core_alu_bcd_addh_cry_partial0_0;
    bool core_alu_bcd_addl_sum_partial3_0;
    bool core_alu_bcd_addl_sum_partial2_0;
    bool core_alu_bcd_addl_sum_partial1_0;
    bool core_alu_bcd_addl_sum_partial0_0;
    bool core_alu_bcd_addl_cry_partial3_0;
    bool core_alu_bcd_addl_cry_partial2_0;
    bool core_alu_bcd_addl_cry_partial1_0;
    bool core_alu_bcd_addl_cry_partial0_0;
    uint8_t core_alu_jrg_ido;
    uint8_t core_alu_jrg_idi;
    bool core_alu_jrg_ld;
    uint8_t core_alu_krg_ido;
    uint8_t core_sm_opcode;
    uint8_t core_sm_opcode_in;
    bool core_sm_opcode_ld;
    uint8_t core_sm_state;
    uint8_t core_sm_state_in;
    bool core_sm_syncl;
    bool core_sm_wel_n;
    bool core_sm_we_d_n;
    bool core_sm_pc_load;
    bool core_sm_pc_h_load;
    bool core_sm_pc_cen;
    bool core_sm_pc_sel_datai;
    uint8_t core_sm_pc_vec_sel;
    bool core_sm_pcl_alu_ld;
    bool core_sm_sob_n_f;
    bool core_sm_aregd_load;
    bool core_sm_dregi_load;
    bool core_sm_drego_load;
    bool core_sm_sreg_load;
    bool core_sm_xreg_load;
    bool core_sm_yreg_load;
    bool core_sm_lreg_load;
    bool core_sm_jregi_load;
    bool core_sm_jrego_load;
    bool core_sm_kregi_load;
    bool core_sm_z_flag_f;
    bool core_sm_branch_carry_f;
    bool core_sm_adh_alu;
    bool core_sm_adh_dreg;
    bool core_sm_adh_zpg;
    bool core_sm_adh_onepg;
    uint8_t core_sm_domux_001;
    uint8_t core_sm_domux_010;
    uint8_t core_sm_domux_011;
    uint8_t core_sm_domux_100;
    uint8_t core_sm_domux_101;
    uint8_t core_sm_domux_110;
    uint8_t core_sm_domux_111;
    bool core_sm_resetl;
    bool core_sm_interrupt;
    bool core_sm_reset_proc;
    bool core_sm_nmi_proc;
    bool core_sm_irq_proc;
    bool core_sm_irq;
    bool core_sm_irq_pend;
    bool core_sm_nmi_pend;
    bool core_sm_nmi1;
    bool core_sm_nmi2;
    bool core_sm_addr_carry;
    bool core_sm_imp2psr;
    bool core_sm_imp2tx;
    bool core_sm_imp2inc;
    bool core_sm_imm_1_addr;
    bool core_sm_rel_addr;
    bool core_sm_zpg_1_addr;
    bool core_sm_zpx_1_addr;
    bool core_sm_abs_1_addr;
    bool core_sm_abx_1_addr;
    bool core_sm_aby_1_addr;
    bool core_sm_inx_1_addr;
    bool core_sm_iny_1_addr;
    bool core_sm_ind_1_addr;
    bool core_sm_imm_3_addr;
    bool core_sm_zpg_3_addr;
    bool core_sm_zpx_3_addr;
    bool core_sm_abs_3_addr;
    bool core_sm_abx_3_addr;
    bool core_sm_acc_addr;
    bool core_sm_zpg_rmw_addr;
    bool core_sm_zpx_rmw_addr;
    bool core_sm_abs_rmw_addr;
    bool core_sm_abx_rmw_addr;
    bool core_sm_type1_read;
    bool core_sm_type1_calc;
    bool core_sm_type2_read;
    bool core_sm_type2_calc;
    bool core_sm_type2_write;
    bool core_sm_type2_done;
    bool core_sm_type3_read;
    bool core_sm_type3_calc;
    bool core_sm_branch_take;
    bool core_sm_adc_op;
    bool core_sm_lda_op;
    bool core_sm_cmp_op;
    bool core_sm_cpx_op;
    bool core_sm_cpy_op;
    bool core_sm_ora_op;
    bool core_sm_and_op;
    bool core_sm_eor_op;
    bool core_sm_sbc_op;
    bool core_sm_asl_op;
    bool core_sm_lsr_op;
    bool core_sm_rol_op;
    bool core_sm_ror_op;
    bool core_sm_inc_op;
    bool core_sm_dec_op;
    bool core_sm_ldx_op;
    bool core_sm_ldy_op;
    bool core_sm_stx_op;
    bool core_sm_sty_op;
    bool core_sm_bit_op;
    bool core_sm_rmb_op;
    bool core_sm_smb_op;
    bool core_sm_bbx_op;
    bool core_sm_trb_op;
    bool core_sm_tsb_op;
    uint16_t core_sm_alu_ctl_d;
    uint8_t core_sm_alu_ctl_bsel;
    bool core_sm_alu_ctl_carry;
    bool core_sm_alu_ctl_bcd;
    uint8_t core_sm_alu_ctl_mode;
    bool core_sm_log_b_inv;
    uint8_t core_sm_opcd_ido;
    uint8_t core_sm_st_ido;

    void hif_cone_core_addrh();


    void hif_cone_core_addrl();


    void hif_cone_core_alu2op();


    void hif_cone_core_alu_jrg_idi();


    void hif_cone_core_alu_jrg_ld();


    void hif_cone_core_alu_ld();


    void hif_cone_core_alu_outl();


    void hif_cone_core_aregl();


    void hif_cone_core_domux_sel();


    void hif_cone_core_drg_idi();


    void hif_cone_core_drg_ld();


    void hif_cone_core_pc_cntih();


    void hif_cone_core_pc_cntil();


    void hif_cone_core_pc_ctl();


    void hif_cone_core_pc_hreg_in();


    void hif_cone_core_pchl();


    void hif_cone_core_pcll();


    void hif_cone_core_psrl();


    void hif_cone_core_reset();


    void hif_cone_core_rg_load();


    void hif_cone_core_sm_abx_1_addr();


    void hif_cone_core_sm_abx_3_addr();


    void hif_cone_core_sm_abx_rmw_addr();


    void hif_cone_core_sm_aby_1_addr();


    void hif_cone_core_sm_adc_op();


    void hif_cone_core_sm_alu_ctl_d();


    void hif_cone_core_sm_and_op();


    void hif_cone_core_sm_asl_op();


    void hif_cone_core_sm_bit_op();


    void hif_cone_core_sm_cmp_op();


    void hif_cone_core_sm_cpx_op();


    void hif_cone_core_sm_cpy_op();


    void hif_cone_core_sm_dec_op();


    void hif_cone_core_sm_eor_op();


    void hif_cone_core_sm_imp2inc();


    void hif_cone_core_sm_imp2tx();


    void hif_cone_core_sm_inc_op();


    void hif_cone_core_sm_interrupt();


    void hif_cone_core_sm_iny_1_addr();


    void hif_cone_core_sm_irq_pend();


    void hif_cone_core_sm_lda_op();


    void hif_cone_core_sm_ldx_op();


    void hif_cone_core_sm_ldy_op();


    void hif_cone_core_sm_lsr_op();


    void hif_cone_core_sm_opcode();


    void hif_cone_core_sm_opcode_in();


    void hif_cone_core_sm_opcode_ld();


    void hif_cone_core_sm_ora_op();


    void hif_cone_core_sm_rol_op();


    void hif_cone_core_sm_ror_op();


    void hif_cone_core_sm_sbc_op();


    void hif_cone_core_sm_state();


    void hif_cone_core_sm_state_in();


    void hif_cone_core_sm_syncl();


    void hif_cone_core_sm_trb_op();


    void hif_cone_core_sm_tsb_op();


    void hif_cone_core_sm_type1_read();


    void hif_cone_core_sm_type2_read();


    void hif_cone_core_sm_type3_read();


    void hif_cone_core_sm_we_d_n();


    void hif_cone_core_sreg_cen();


    void hif_cone_core_sreg_up();


    void hif_cone_core_sregl();


    void hif_cone_core_xregl();


    void hif_cone_core_yregl();


    void hif_cone_oen();


    void hif_cone_vpa();


    void hif_cone_we_n_out_sig();

    m6502();


    ~m6502();


    bool core_sm_psrl_7_new;
    bool core_sm_psrl_6_new;
    bool core_sm_psrl_5_new;
    bool core_sm_psrl_4_new;
    bool core_sm_psrl_3_new;
    bool core_sm_psrl_2_new;
    bool core_sm_psrl_1_new;
    bool core_sm_psrl_0_new;
    uint8_t core_dataol_new;
    uint16_t core_alu_ctl_new;
    uint8_t core_drg_ido_new;
    uint8_t core_srg_dataol_new;
    uint8_t core_pc_hreg_new;
    uint16_t core_pc_pc_new;
    uint8_t core_arg_ido_new;
    uint8_t core_xrg_ido_new;
    uint8_t core_yrg_ido_new;
    uint8_t core_adlmx_lrg_ido_new;
    bool core_alu_bcd_addl_cry_partial0_0_new;
    uint8_t core_alu_jrg_ido_new;
    uint8_t core_alu_krg_ido_new;
    bool core_sm_wel_n_new;
    bool core_sm_sob_n_f_new;
    bool core_sm_z_flag_f_new;
    bool core_sm_branch_carry_f_new;
    bool core_sm_resetl_new;
    bool core_sm_reset_proc_new;
    bool core_sm_nmi_proc_new;
    bool core_sm_irq_proc_new;
    bool core_sm_irq_new;
    bool core_sm_nmi_pend_new;
    bool core_sm_nmi1_new;
    bool core_sm_nmi2_new;
    bool core_sm_addr_carry_new;
    bool core_sm_type1_calc_new;
    bool core_sm_type2_calc_new;
    bool core_sm_type2_write_new;
    bool core_sm_type2_done_new;
    bool core_sm_type3_calc_new;
    uint8_t core_sm_opcd_ido_new;
    uint8_t core_sm_st_ido_new;
    bool process_in_queue;
    bool flag_core_domx_process_executed;
    bool flag_core_xrg_ido;
    bool flag_core_yrg_ido;
    bool flag_core_srg_dataol;
    bool flag_core_arg_ido;
    bool flag_core_alu_ctl;
    bool flag_core_alu_bcd_addl_cry_partial0_0;
    bool flag_core_alu_jrg_ido;
    bool flag_core_alu_krg_ido;
    bool flag_core_pc_pc;
    bool flag_core_sm_opcd_ido;
    bool flag_core_sm_st_ido;
    bool flag_core_sm_psrl_0;
    bool flag_core_sm_psrl_1;
    bool flag_core_sm_psrl_2;
    bool flag_core_sm_psrl_3;
    bool flag_core_sm_psrl_4;
    bool flag_core_sm_psrl_5;
    bool flag_core_sm_psrl_6;
    bool flag_core_sm_psrl_7;
    bool flag_core_drg_ido;
    bool flag_core_adlmx_lrg_ido;
    bool flag_core_sm_type2_calc;
    bool flag_core_sm_type2_write;
    bool flag_core_dataol;
    bool flag_clk;
    bool flag_core_sm_wel_n;
    bool flag_core_sm_z_flag_f;
    bool flag_core_sm_branch_carry_f;
    bool flag_core_sm_type1_calc;
    bool flag_core_sm_type2_done;
    bool flag_core_sm_type3_calc;
    bool flag_globact_process_4_executed;
    bool flag_core_drg_ff1_core_srg_process_0_core_pc_counter_core_arg_ff1_core_xrg_ff1_core_yrg_ff1_core_adlmx_lrg_ff1_core_alu_jrg_ff1_core_alu_krg_ff1_core_sm_elr_core_sm_misc_core_sm_pipe_core_sm_opcd_ff1_core_sm_st_ff1_executed;
    bool flag_pos_clk;

    void core_domx_process();


    void globact_process();


    void globact_process_0();


    void globact_process_1();


    void globact_process_2();


    void globact_process_3();


    void we_n_update_process();


    void globact_process_4();


    void core_drg_ff1_core_srg_process_0_core_pc_counter_core_arg_ff1_core_xrg_ff1_core_yrg_ff1_core_adlmx_lrg_ff1_core_alu_jrg_ff1_core_alu_krg_ff1_core_sm_elr_core_sm_misc_core_sm_pipe_core_sm_opcd_ff1_core_sm_st_ff1
        ();


    void update_input_queue( bool synch_phase = true );


    void update_event_queue();


    void flag_elaboration();


    void synch_elaboration();


    void simulate( m6502_iostruct * io_exchange, int32_t & cycles_number );


    void start_of_simulation();


    void initialize();


    void finalize();


private:

    m6502( const m6502 & );
    const m6502& operator= ( const m6502 & );


};


#endif
