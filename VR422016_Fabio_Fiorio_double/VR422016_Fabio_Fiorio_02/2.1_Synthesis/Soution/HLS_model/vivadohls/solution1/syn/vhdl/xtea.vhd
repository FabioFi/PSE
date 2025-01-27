-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
-- Version: 2019.1
-- Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity xtea is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    word0 : IN STD_LOGIC_VECTOR (31 downto 0);
    word1 : IN STD_LOGIC_VECTOR (31 downto 0);
    key0 : IN STD_LOGIC_VECTOR (31 downto 0);
    key1 : IN STD_LOGIC_VECTOR (31 downto 0);
    key2 : IN STD_LOGIC_VECTOR (31 downto 0);
    key3 : IN STD_LOGIC_VECTOR (31 downto 0);
    mode : IN STD_LOGIC;
    result0 : OUT STD_LOGIC_VECTOR (31 downto 0);
    result0_ap_vld : OUT STD_LOGIC;
    result1 : OUT STD_LOGIC_VECTOR (31 downto 0);
    result1_ap_vld : OUT STD_LOGIC );
end;


architecture behav of xtea is 
    attribute CORE_GENERATION_INFO : STRING;
    attribute CORE_GENERATION_INFO of behav : architecture is
    "xtea,hls_ip_2019_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7z020-clg400-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=7.656000,HLS_SYN_LAT=66,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=628,HLS_SYN_LUT=1606,HLS_VERSION=2019_1}";
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (5 downto 0) := "000001";
    constant ap_ST_fsm_state2 : STD_LOGIC_VECTOR (5 downto 0) := "000010";
    constant ap_ST_fsm_state3 : STD_LOGIC_VECTOR (5 downto 0) := "000100";
    constant ap_ST_fsm_state4 : STD_LOGIC_VECTOR (5 downto 0) := "001000";
    constant ap_ST_fsm_state5 : STD_LOGIC_VECTOR (5 downto 0) := "010000";
    constant ap_ST_fsm_state6 : STD_LOGIC_VECTOR (5 downto 0) := "100000";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv32_2 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000010";
    constant ap_const_lv32_3 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000011";
    constant ap_const_lv32_4 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000100";
    constant ap_const_lv37_0 : STD_LOGIC_VECTOR (36 downto 0) := "0000000000000000000000000000000000000";
    constant ap_const_lv6_0 : STD_LOGIC_VECTOR (5 downto 0) := "000000";
    constant ap_const_lv38_C6EF3720 : STD_LOGIC_VECTOR (37 downto 0) := "00000011000110111011110011011100100000";
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_5 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000101";
    constant ap_const_lv6_20 : STD_LOGIC_VECTOR (5 downto 0) := "100000";
    constant ap_const_lv6_1 : STD_LOGIC_VECTOR (5 downto 0) := "000001";
    constant ap_const_lv2_0 : STD_LOGIC_VECTOR (1 downto 0) := "00";
    constant ap_const_lv2_1 : STD_LOGIC_VECTOR (1 downto 0) := "01";
    constant ap_const_lv2_2 : STD_LOGIC_VECTOR (1 downto 0) := "10";
    constant ap_const_lv32_1F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011111";
    constant ap_const_lv37_9E3779B9 : STD_LOGIC_VECTOR (36 downto 0) := "0000010011110001101110111100110111001";
    constant ap_const_lv13_19B9 : STD_LOGIC_VECTOR (12 downto 0) := "1100110111001";
    constant ap_const_lv32_B : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001011";
    constant ap_const_lv32_C : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001100";
    constant ap_const_lv11_0 : STD_LOGIC_VECTOR (10 downto 0) := "00000000000";
    constant ap_const_lv13_0 : STD_LOGIC_VECTOR (12 downto 0) := "0000000000000";
    constant ap_const_lv13_800 : STD_LOGIC_VECTOR (12 downto 0) := "0100000000000";
    constant ap_const_lv13_1000 : STD_LOGIC_VECTOR (12 downto 0) := "1000000000000";
    constant ap_const_lv32_9E3779B9 : STD_LOGIC_VECTOR (31 downto 0) := "10011110001101110111100110111001";
    constant ap_const_lv38_3F61C88647 : STD_LOGIC_VECTOR (37 downto 0) := "11111101100001110010001000011001000111";
    constant ap_const_lv2_3 : STD_LOGIC_VECTOR (1 downto 0) := "11";
    constant ap_const_lv32_61C88647 : STD_LOGIC_VECTOR (31 downto 0) := "01100001110010001000011001000111";
    constant ap_const_boolean_1 : BOOLEAN := true;

    signal ap_CS_fsm : STD_LOGIC_VECTOR (5 downto 0) := "000001";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal i_2_fu_260_p2 : STD_LOGIC_VECTOR (5 downto 0);
    signal i_2_reg_836 : STD_LOGIC_VECTOR (5 downto 0);
    signal ap_CS_fsm_state2 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state2 : signal is "none";
    signal add_ln55_fu_352_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln55_reg_841 : STD_LOGIC_VECTOR (31 downto 0);
    signal icmp_ln44_fu_254_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln55_fu_358_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal trunc_ln55_reg_846 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln55_1_fu_362_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln55_1_reg_851 : STD_LOGIC_VECTOR (31 downto 0);
    signal sum_2_fu_372_p2 : STD_LOGIC_VECTOR (36 downto 0);
    signal sum_2_reg_856 : STD_LOGIC_VECTOR (36 downto 0);
    signal select_ln61_2_fu_450_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln61_2_reg_861 : STD_LOGIC_VECTOR (31 downto 0);
    signal v0_fu_462_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_CS_fsm_state3 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state3 : signal is "none";
    signal v1_2_fu_516_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal i_fu_528_p2 : STD_LOGIC_VECTOR (5 downto 0);
    signal i_reg_879 : STD_LOGIC_VECTOR (5 downto 0);
    signal ap_CS_fsm_state4 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state4 : signal is "none";
    signal add_ln85_fu_634_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln85_reg_884 : STD_LOGIC_VECTOR (31 downto 0);
    signal icmp_ln75_fu_522_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln85_fu_640_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal trunc_ln85_reg_889 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln85_1_fu_644_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln85_1_reg_894 : STD_LOGIC_VECTOR (31 downto 0);
    signal sum_fu_654_p2 : STD_LOGIC_VECTOR (37 downto 0);
    signal sum_reg_899 : STD_LOGIC_VECTOR (37 downto 0);
    signal select_ln91_2_fu_714_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln91_2_reg_904 : STD_LOGIC_VECTOR (31 downto 0);
    signal v1_fu_726_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_CS_fsm_state5 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state5 : signal is "none";
    signal v0_2_fu_780_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal sum_0_reg_146 : STD_LOGIC_VECTOR (36 downto 0);
    signal mode_read_read_fu_90_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal i_0_reg_157 : STD_LOGIC_VECTOR (5 downto 0);
    signal v0_0_reg_168 : STD_LOGIC_VECTOR (31 downto 0);
    signal v1_0_reg_178 : STD_LOGIC_VECTOR (31 downto 0);
    signal sum_1_reg_188 : STD_LOGIC_VECTOR (37 downto 0);
    signal i_1_reg_199 : STD_LOGIC_VECTOR (5 downto 0);
    signal v0_1_reg_210 : STD_LOGIC_VECTOR (31 downto 0);
    signal v1_1_reg_220 : STD_LOGIC_VECTOR (31 downto 0);
    signal v0_3_reg_230 : STD_LOGIC_VECTOR (31 downto 0);
    signal v1_3_reg_242 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_CS_fsm_state6 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state6 : signal is "none";
    signal trunc_ln44_fu_266_p1 : STD_LOGIC_VECTOR (1 downto 0);
    signal icmp_ln47_fu_270_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln49_fu_276_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln47_fu_288_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln49_fu_294_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln51_fu_282_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln49_fu_306_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln49_fu_300_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln49_1_fu_312_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal lshr_ln2_fu_332_p4 : STD_LOGIC_VECTOR (26 downto 0);
    signal shl_ln55_fu_326_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln55_fu_342_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln55_fu_346_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln49_2_fu_318_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal trunc_ln57_fu_368_p1 : STD_LOGIC_VECTOR (12 downto 0);
    signal add_ln57_1_fu_378_p2 : STD_LOGIC_VECTOR (12 downto 0);
    signal tmp_4_fu_384_p4 : STD_LOGIC_VECTOR (1 downto 0);
    signal and_ln1_fu_394_p3 : STD_LOGIC_VECTOR (12 downto 0);
    signal icmp_ln59_fu_402_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln61_fu_408_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln59_fu_420_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln61_fu_426_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln63_fu_414_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln61_fu_438_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln61_fu_432_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln61_1_fu_444_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln55_1_fu_458_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal lshr_ln3_fu_474_p4 : STD_LOGIC_VECTOR (26 downto 0);
    signal shl_ln67_fu_468_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln67_fu_484_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln67_fu_488_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln67_2_fu_500_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln67_1_fu_505_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln67_fu_494_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln67_1_fu_510_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_fu_534_p4 : STD_LOGIC_VECTOR (1 downto 0);
    signal and_ln_fu_544_p3 : STD_LOGIC_VECTOR (12 downto 0);
    signal icmp_ln77_fu_552_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln79_fu_558_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln77_fu_570_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln79_fu_576_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln81_fu_564_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln79_fu_588_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln79_fu_582_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln79_1_fu_594_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal lshr_ln_fu_614_p4 : STD_LOGIC_VECTOR (26 downto 0);
    signal shl_ln85_fu_608_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln85_fu_624_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln85_fu_628_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln79_2_fu_600_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal trunc_ln87_fu_650_p1 : STD_LOGIC_VECTOR (1 downto 0);
    signal add_ln87_1_fu_660_p2 : STD_LOGIC_VECTOR (1 downto 0);
    signal icmp_ln89_fu_666_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln91_fu_672_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal xor_ln89_fu_684_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln91_fu_690_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln93_fu_678_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln91_fu_702_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln91_fu_696_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln91_1_fu_708_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln85_1_fu_722_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal lshr_ln1_fu_738_p4 : STD_LOGIC_VECTOR (26 downto 0);
    signal shl_ln97_fu_732_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln97_fu_748_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln97_fu_752_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln97_2_fu_764_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln97_1_fu_769_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal add_ln97_fu_758_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal xor_ln97_1_fu_774_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_NS_fsm : STD_LOGIC_VECTOR (5 downto 0);


begin




    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_fsm_state1;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    i_0_reg_157_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((mode_read_read_fu_90_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                i_0_reg_157 <= ap_const_lv6_0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state3)) then 
                i_0_reg_157 <= i_2_reg_836;
            end if; 
        end if;
    end process;

    i_1_reg_199_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1) and (mode_read_read_fu_90_p2 = ap_const_lv1_1))) then 
                i_1_reg_199 <= ap_const_lv6_0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state5)) then 
                i_1_reg_199 <= i_reg_879;
            end if; 
        end if;
    end process;

    sum_0_reg_146_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((mode_read_read_fu_90_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                sum_0_reg_146 <= ap_const_lv37_0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state3)) then 
                sum_0_reg_146 <= sum_2_reg_856;
            end if; 
        end if;
    end process;

    sum_1_reg_188_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1) and (mode_read_read_fu_90_p2 = ap_const_lv1_1))) then 
                sum_1_reg_188 <= ap_const_lv38_C6EF3720;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state5)) then 
                sum_1_reg_188 <= sum_reg_899;
            end if; 
        end if;
    end process;

    v0_0_reg_168_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((mode_read_read_fu_90_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                v0_0_reg_168 <= word0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state3)) then 
                v0_0_reg_168 <= v0_fu_462_p2;
            end if; 
        end if;
    end process;

    v0_1_reg_210_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1) and (mode_read_read_fu_90_p2 = ap_const_lv1_1))) then 
                v0_1_reg_210 <= word0;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state5)) then 
                v0_1_reg_210 <= v0_2_fu_780_p2;
            end if; 
        end if;
    end process;

    v0_3_reg_230_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln44_fu_254_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                v0_3_reg_230 <= v0_0_reg_168;
            elsif (((icmp_ln75_fu_522_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state4))) then 
                v0_3_reg_230 <= v0_1_reg_210;
            end if; 
        end if;
    end process;

    v1_0_reg_178_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((mode_read_read_fu_90_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                v1_0_reg_178 <= word1;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state3)) then 
                v1_0_reg_178 <= v1_2_fu_516_p2;
            end if; 
        end if;
    end process;

    v1_1_reg_220_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1) and (mode_read_read_fu_90_p2 = ap_const_lv1_1))) then 
                v1_1_reg_220 <= word1;
            elsif ((ap_const_logic_1 = ap_CS_fsm_state5)) then 
                v1_1_reg_220 <= v1_fu_726_p2;
            end if; 
        end if;
    end process;

    v1_3_reg_242_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln44_fu_254_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                v1_3_reg_242 <= v1_0_reg_178;
            elsif (((icmp_ln75_fu_522_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state4))) then 
                v1_3_reg_242 <= v1_1_reg_220;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln44_fu_254_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state2))) then
                add_ln55_1_reg_851 <= add_ln55_1_fu_362_p2;
                add_ln55_reg_841 <= add_ln55_fu_352_p2;
                select_ln61_2_reg_861 <= select_ln61_2_fu_450_p3;
                sum_2_reg_856 <= sum_2_fu_372_p2;
                trunc_ln55_reg_846 <= trunc_ln55_fu_358_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln75_fu_522_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state4))) then
                add_ln85_1_reg_894 <= add_ln85_1_fu_644_p2;
                add_ln85_reg_884 <= add_ln85_fu_634_p2;
                select_ln91_2_reg_904 <= select_ln91_2_fu_714_p3;
                sum_reg_899 <= sum_fu_654_p2;
                trunc_ln85_reg_889 <= trunc_ln85_fu_640_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state2)) then
                i_2_reg_836 <= i_2_fu_260_p2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_CS_fsm_state4)) then
                i_reg_879 <= i_fu_528_p2;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_start, ap_CS_fsm, ap_CS_fsm_state1, ap_CS_fsm_state2, icmp_ln44_fu_254_p2, ap_CS_fsm_state4, icmp_ln75_fu_522_p2, mode_read_read_fu_90_p2)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1) and (mode_read_read_fu_90_p2 = ap_const_lv1_1))) then
                    ap_NS_fsm <= ap_ST_fsm_state4;
                elsif (((mode_read_read_fu_90_p2 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then
                    ap_NS_fsm <= ap_ST_fsm_state2;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_state2 => 
                if (((icmp_ln44_fu_254_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then
                    ap_NS_fsm <= ap_ST_fsm_state6;
                else
                    ap_NS_fsm <= ap_ST_fsm_state3;
                end if;
            when ap_ST_fsm_state3 => 
                ap_NS_fsm <= ap_ST_fsm_state2;
            when ap_ST_fsm_state4 => 
                if (((icmp_ln75_fu_522_p2 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state4))) then
                    ap_NS_fsm <= ap_ST_fsm_state6;
                else
                    ap_NS_fsm <= ap_ST_fsm_state5;
                end if;
            when ap_ST_fsm_state5 => 
                ap_NS_fsm <= ap_ST_fsm_state4;
            when ap_ST_fsm_state6 => 
                ap_NS_fsm <= ap_ST_fsm_state1;
            when others =>  
                ap_NS_fsm <= "XXXXXX";
        end case;
    end process;
    add_ln55_1_fu_362_p2 <= std_logic_vector(unsigned(select_ln49_2_fu_318_p3) + unsigned(trunc_ln55_fu_358_p1));
    add_ln55_fu_352_p2 <= std_logic_vector(unsigned(xor_ln55_fu_346_p2) + unsigned(v1_0_reg_178));
    add_ln57_1_fu_378_p2 <= std_logic_vector(signed(ap_const_lv13_19B9) + signed(trunc_ln57_fu_368_p1));
    add_ln67_1_fu_505_p2 <= std_logic_vector(unsigned(add_ln67_2_fu_500_p2) + unsigned(trunc_ln55_reg_846));
    add_ln67_2_fu_500_p2 <= std_logic_vector(signed(ap_const_lv32_9E3779B9) + signed(select_ln61_2_reg_861));
    add_ln67_fu_494_p2 <= std_logic_vector(unsigned(v0_fu_462_p2) + unsigned(xor_ln67_fu_488_p2));
    add_ln85_1_fu_644_p2 <= std_logic_vector(unsigned(select_ln79_2_fu_600_p3) + unsigned(trunc_ln85_fu_640_p1));
    add_ln85_fu_634_p2 <= std_logic_vector(unsigned(xor_ln85_fu_628_p2) + unsigned(v0_1_reg_210));
    add_ln87_1_fu_660_p2 <= std_logic_vector(signed(ap_const_lv2_3) + signed(trunc_ln87_fu_650_p1));
    add_ln97_1_fu_769_p2 <= std_logic_vector(unsigned(add_ln97_2_fu_764_p2) + unsigned(trunc_ln85_reg_889));
    add_ln97_2_fu_764_p2 <= std_logic_vector(unsigned(ap_const_lv32_61C88647) + unsigned(select_ln91_2_reg_904));
    add_ln97_fu_758_p2 <= std_logic_vector(unsigned(v1_fu_726_p2) + unsigned(xor_ln97_fu_752_p2));
    and_ln1_fu_394_p3 <= (tmp_4_fu_384_p4 & ap_const_lv11_0);
    and_ln49_fu_294_p2 <= (xor_ln47_fu_288_p2 and icmp_ln49_fu_276_p2);
    and_ln61_fu_426_p2 <= (xor_ln59_fu_420_p2 and icmp_ln61_fu_408_p2);
    and_ln79_fu_576_p2 <= (xor_ln77_fu_570_p2 and icmp_ln79_fu_558_p2);
    and_ln91_fu_690_p2 <= (xor_ln89_fu_684_p2 and icmp_ln91_fu_672_p2);
    and_ln_fu_544_p3 <= (tmp_fu_534_p4 & ap_const_lv11_0);
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state2 <= ap_CS_fsm(1);
    ap_CS_fsm_state3 <= ap_CS_fsm(2);
    ap_CS_fsm_state4 <= ap_CS_fsm(3);
    ap_CS_fsm_state5 <= ap_CS_fsm(4);
    ap_CS_fsm_state6 <= ap_CS_fsm(5);

    ap_done_assign_proc : process(ap_CS_fsm_state6)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_assign_proc : process(ap_start, ap_CS_fsm_state1)
    begin
        if (((ap_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_ready_assign_proc : process(ap_CS_fsm_state6)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;

    i_2_fu_260_p2 <= std_logic_vector(unsigned(i_0_reg_157) + unsigned(ap_const_lv6_1));
    i_fu_528_p2 <= std_logic_vector(unsigned(i_1_reg_199) + unsigned(ap_const_lv6_1));
    icmp_ln44_fu_254_p2 <= "1" when (i_0_reg_157 = ap_const_lv6_20) else "0";
    icmp_ln47_fu_270_p2 <= "1" when (trunc_ln44_fu_266_p1 = ap_const_lv2_0) else "0";
    icmp_ln49_fu_276_p2 <= "1" when (trunc_ln44_fu_266_p1 = ap_const_lv2_1) else "0";
    icmp_ln51_fu_282_p2 <= "1" when (trunc_ln44_fu_266_p1 = ap_const_lv2_2) else "0";
    icmp_ln59_fu_402_p2 <= "1" when (and_ln1_fu_394_p3 = ap_const_lv13_0) else "0";
    icmp_ln61_fu_408_p2 <= "1" when (and_ln1_fu_394_p3 = ap_const_lv13_800) else "0";
    icmp_ln63_fu_414_p2 <= "1" when (and_ln1_fu_394_p3 = ap_const_lv13_1000) else "0";
    icmp_ln75_fu_522_p2 <= "1" when (i_1_reg_199 = ap_const_lv6_20) else "0";
    icmp_ln77_fu_552_p2 <= "1" when (and_ln_fu_544_p3 = ap_const_lv13_0) else "0";
    icmp_ln79_fu_558_p2 <= "1" when (and_ln_fu_544_p3 = ap_const_lv13_800) else "0";
    icmp_ln81_fu_564_p2 <= "1" when (and_ln_fu_544_p3 = ap_const_lv13_1000) else "0";
    icmp_ln89_fu_666_p2 <= "1" when (add_ln87_1_fu_660_p2 = ap_const_lv2_0) else "0";
    icmp_ln91_fu_672_p2 <= "1" when (add_ln87_1_fu_660_p2 = ap_const_lv2_1) else "0";
    icmp_ln93_fu_678_p2 <= "1" when (add_ln87_1_fu_660_p2 = ap_const_lv2_2) else "0";
    lshr_ln1_fu_738_p4 <= v1_fu_726_p2(31 downto 5);
    lshr_ln2_fu_332_p4 <= v1_0_reg_178(31 downto 5);
    lshr_ln3_fu_474_p4 <= v0_fu_462_p2(31 downto 5);
    lshr_ln_fu_614_p4 <= v0_1_reg_210(31 downto 5);
    mode_read_read_fu_90_p2 <= (0=>mode, others=>'-');
    or_ln49_fu_306_p2 <= (icmp_ln47_fu_270_p2 or and_ln49_fu_294_p2);
    or_ln61_fu_438_p2 <= (icmp_ln59_fu_402_p2 or and_ln61_fu_426_p2);
    or_ln79_fu_588_p2 <= (icmp_ln77_fu_552_p2 or and_ln79_fu_576_p2);
    or_ln91_fu_702_p2 <= (icmp_ln89_fu_666_p2 or and_ln91_fu_690_p2);
    result0 <= v0_3_reg_230;

    result0_ap_vld_assign_proc : process(ap_CS_fsm_state6)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
            result0_ap_vld <= ap_const_logic_1;
        else 
            result0_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    result1 <= v1_3_reg_242;

    result1_ap_vld_assign_proc : process(ap_CS_fsm_state6)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state6)) then 
            result1_ap_vld <= ap_const_logic_1;
        else 
            result1_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    select_ln49_1_fu_312_p3 <= 
        key2 when (icmp_ln51_fu_282_p2(0) = '1') else 
        key3;
    select_ln49_2_fu_318_p3 <= 
        select_ln49_fu_300_p3 when (or_ln49_fu_306_p2(0) = '1') else 
        select_ln49_1_fu_312_p3;
    select_ln49_fu_300_p3 <= 
        key1 when (and_ln49_fu_294_p2(0) = '1') else 
        key0;
    select_ln61_1_fu_444_p3 <= 
        key2 when (icmp_ln63_fu_414_p2(0) = '1') else 
        key3;
    select_ln61_2_fu_450_p3 <= 
        select_ln61_fu_432_p3 when (or_ln61_fu_438_p2(0) = '1') else 
        select_ln61_1_fu_444_p3;
    select_ln61_fu_432_p3 <= 
        key1 when (and_ln61_fu_426_p2(0) = '1') else 
        key0;
    select_ln79_1_fu_594_p3 <= 
        key2 when (icmp_ln81_fu_564_p2(0) = '1') else 
        key3;
    select_ln79_2_fu_600_p3 <= 
        select_ln79_fu_582_p3 when (or_ln79_fu_588_p2(0) = '1') else 
        select_ln79_1_fu_594_p3;
    select_ln79_fu_582_p3 <= 
        key1 when (and_ln79_fu_576_p2(0) = '1') else 
        key0;
    select_ln91_1_fu_708_p3 <= 
        key2 when (icmp_ln93_fu_678_p2(0) = '1') else 
        key3;
    select_ln91_2_fu_714_p3 <= 
        select_ln91_fu_696_p3 when (or_ln91_fu_702_p2(0) = '1') else 
        select_ln91_1_fu_708_p3;
    select_ln91_fu_696_p3 <= 
        key1 when (and_ln91_fu_690_p2(0) = '1') else 
        key0;
    shl_ln55_fu_326_p2 <= std_logic_vector(shift_left(unsigned(v1_0_reg_178),to_integer(unsigned('0' & ap_const_lv32_4(31-1 downto 0)))));
    shl_ln67_fu_468_p2 <= std_logic_vector(shift_left(unsigned(v0_fu_462_p2),to_integer(unsigned('0' & ap_const_lv32_4(31-1 downto 0)))));
    shl_ln85_fu_608_p2 <= std_logic_vector(shift_left(unsigned(v0_1_reg_210),to_integer(unsigned('0' & ap_const_lv32_4(31-1 downto 0)))));
    shl_ln97_fu_732_p2 <= std_logic_vector(shift_left(unsigned(v1_fu_726_p2),to_integer(unsigned('0' & ap_const_lv32_4(31-1 downto 0)))));
    sum_2_fu_372_p2 <= std_logic_vector(unsigned(ap_const_lv37_9E3779B9) + unsigned(sum_0_reg_146));
    sum_fu_654_p2 <= std_logic_vector(signed(ap_const_lv38_3F61C88647) + signed(sum_1_reg_188));
    tmp_4_fu_384_p4 <= add_ln57_1_fu_378_p2(12 downto 11);
    tmp_fu_534_p4 <= sum_1_reg_188(12 downto 11);
    trunc_ln44_fu_266_p1 <= sum_0_reg_146(2 - 1 downto 0);
    trunc_ln55_fu_358_p1 <= sum_0_reg_146(32 - 1 downto 0);
    trunc_ln57_fu_368_p1 <= sum_0_reg_146(13 - 1 downto 0);
    trunc_ln85_fu_640_p1 <= sum_1_reg_188(32 - 1 downto 0);
    trunc_ln87_fu_650_p1 <= sum_1_reg_188(2 - 1 downto 0);
    v0_2_fu_780_p2 <= std_logic_vector(unsigned(v0_1_reg_210) - unsigned(xor_ln97_1_fu_774_p2));
    v0_fu_462_p2 <= std_logic_vector(unsigned(xor_ln55_1_fu_458_p2) + unsigned(v0_0_reg_168));
    v1_2_fu_516_p2 <= std_logic_vector(unsigned(xor_ln67_1_fu_510_p2) + unsigned(v1_0_reg_178));
    v1_fu_726_p2 <= std_logic_vector(unsigned(v1_1_reg_220) - unsigned(xor_ln85_1_fu_722_p2));
    xor_ln47_fu_288_p2 <= (icmp_ln47_fu_270_p2 xor ap_const_lv1_1);
    xor_ln55_1_fu_458_p2 <= (add_ln55_reg_841 xor add_ln55_1_reg_851);
    xor_ln55_fu_346_p2 <= (zext_ln55_fu_342_p1 xor shl_ln55_fu_326_p2);
    xor_ln59_fu_420_p2 <= (icmp_ln59_fu_402_p2 xor ap_const_lv1_1);
    xor_ln67_1_fu_510_p2 <= (add_ln67_fu_494_p2 xor add_ln67_1_fu_505_p2);
    xor_ln67_fu_488_p2 <= (zext_ln67_fu_484_p1 xor shl_ln67_fu_468_p2);
    xor_ln77_fu_570_p2 <= (icmp_ln77_fu_552_p2 xor ap_const_lv1_1);
    xor_ln85_1_fu_722_p2 <= (add_ln85_reg_884 xor add_ln85_1_reg_894);
    xor_ln85_fu_628_p2 <= (zext_ln85_fu_624_p1 xor shl_ln85_fu_608_p2);
    xor_ln89_fu_684_p2 <= (icmp_ln89_fu_666_p2 xor ap_const_lv1_1);
    xor_ln97_1_fu_774_p2 <= (add_ln97_fu_758_p2 xor add_ln97_1_fu_769_p2);
    xor_ln97_fu_752_p2 <= (zext_ln97_fu_748_p1 xor shl_ln97_fu_732_p2);
    zext_ln55_fu_342_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(lshr_ln2_fu_332_p4),32));
    zext_ln67_fu_484_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(lshr_ln3_fu_474_p4),32));
    zext_ln85_fu_624_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(lshr_ln_fu_614_p4),32));
    zext_ln97_fu_748_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(lshr_ln1_fu_738_p4),32));
end behav;
