// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="xtea,hls_ip_2019_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7z020-clg400-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=7.656000,HLS_SYN_LAT=66,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=628,HLS_SYN_LUT=1606,HLS_VERSION=2019_1}" *)

module xtea (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        word0,
        word1,
        key0,
        key1,
        key2,
        key3,
        mode,
        result0,
        result0_ap_vld,
        result1,
        result1_ap_vld
);

parameter    ap_ST_fsm_state1 = 6'd1;
parameter    ap_ST_fsm_state2 = 6'd2;
parameter    ap_ST_fsm_state3 = 6'd4;
parameter    ap_ST_fsm_state4 = 6'd8;
parameter    ap_ST_fsm_state5 = 6'd16;
parameter    ap_ST_fsm_state6 = 6'd32;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] word0;
input  [31:0] word1;
input  [31:0] key0;
input  [31:0] key1;
input  [31:0] key2;
input  [31:0] key3;
input   mode;
output  [31:0] result0;
output   result0_ap_vld;
output  [31:0] result1;
output   result1_ap_vld;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg result0_ap_vld;
reg result1_ap_vld;

(* fsm_encoding = "none" *) reg   [5:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [5:0] i_2_fu_260_p2;
reg   [5:0] i_2_reg_836;
wire    ap_CS_fsm_state2;
wire   [31:0] add_ln55_fu_352_p2;
reg   [31:0] add_ln55_reg_841;
wire   [0:0] icmp_ln44_fu_254_p2;
wire   [31:0] trunc_ln55_fu_358_p1;
reg   [31:0] trunc_ln55_reg_846;
wire   [31:0] add_ln55_1_fu_362_p2;
reg   [31:0] add_ln55_1_reg_851;
wire   [36:0] sum_2_fu_372_p2;
reg   [36:0] sum_2_reg_856;
wire   [31:0] select_ln61_2_fu_450_p3;
reg   [31:0] select_ln61_2_reg_861;
wire   [31:0] v0_fu_462_p2;
wire    ap_CS_fsm_state3;
wire   [31:0] v1_2_fu_516_p2;
wire   [5:0] i_fu_528_p2;
reg   [5:0] i_reg_879;
wire    ap_CS_fsm_state4;
wire   [31:0] add_ln85_fu_634_p2;
reg   [31:0] add_ln85_reg_884;
wire   [0:0] icmp_ln75_fu_522_p2;
wire   [31:0] trunc_ln85_fu_640_p1;
reg   [31:0] trunc_ln85_reg_889;
wire   [31:0] add_ln85_1_fu_644_p2;
reg   [31:0] add_ln85_1_reg_894;
wire   [37:0] sum_fu_654_p2;
reg   [37:0] sum_reg_899;
wire   [31:0] select_ln91_2_fu_714_p3;
reg   [31:0] select_ln91_2_reg_904;
wire   [31:0] v1_fu_726_p2;
wire    ap_CS_fsm_state5;
wire   [31:0] v0_2_fu_780_p2;
reg   [36:0] sum_0_reg_146;
wire   [0:0] mode_read_read_fu_90_p2;
reg   [5:0] i_0_reg_157;
reg   [31:0] v0_0_reg_168;
reg   [31:0] v1_0_reg_178;
reg   [37:0] sum_1_reg_188;
reg   [5:0] i_1_reg_199;
reg   [31:0] v0_1_reg_210;
reg   [31:0] v1_1_reg_220;
reg   [31:0] v0_3_reg_230;
reg   [31:0] v1_3_reg_242;
wire    ap_CS_fsm_state6;
wire   [1:0] trunc_ln44_fu_266_p1;
wire   [0:0] icmp_ln47_fu_270_p2;
wire   [0:0] icmp_ln49_fu_276_p2;
wire   [0:0] xor_ln47_fu_288_p2;
wire   [0:0] and_ln49_fu_294_p2;
wire   [0:0] icmp_ln51_fu_282_p2;
wire   [0:0] or_ln49_fu_306_p2;
wire   [31:0] select_ln49_fu_300_p3;
wire   [31:0] select_ln49_1_fu_312_p3;
wire   [26:0] lshr_ln2_fu_332_p4;
wire   [31:0] shl_ln55_fu_326_p2;
wire   [31:0] zext_ln55_fu_342_p1;
wire   [31:0] xor_ln55_fu_346_p2;
wire   [31:0] select_ln49_2_fu_318_p3;
wire   [12:0] trunc_ln57_fu_368_p1;
wire   [12:0] add_ln57_1_fu_378_p2;
wire   [1:0] tmp_4_fu_384_p4;
wire   [12:0] and_ln1_fu_394_p3;
wire   [0:0] icmp_ln59_fu_402_p2;
wire   [0:0] icmp_ln61_fu_408_p2;
wire   [0:0] xor_ln59_fu_420_p2;
wire   [0:0] and_ln61_fu_426_p2;
wire   [0:0] icmp_ln63_fu_414_p2;
wire   [0:0] or_ln61_fu_438_p2;
wire   [31:0] select_ln61_fu_432_p3;
wire   [31:0] select_ln61_1_fu_444_p3;
wire   [31:0] xor_ln55_1_fu_458_p2;
wire   [26:0] lshr_ln3_fu_474_p4;
wire   [31:0] shl_ln67_fu_468_p2;
wire   [31:0] zext_ln67_fu_484_p1;
wire   [31:0] xor_ln67_fu_488_p2;
wire   [31:0] add_ln67_2_fu_500_p2;
wire   [31:0] add_ln67_1_fu_505_p2;
wire   [31:0] add_ln67_fu_494_p2;
wire   [31:0] xor_ln67_1_fu_510_p2;
wire   [1:0] tmp_fu_534_p4;
wire   [12:0] and_ln_fu_544_p3;
wire   [0:0] icmp_ln77_fu_552_p2;
wire   [0:0] icmp_ln79_fu_558_p2;
wire   [0:0] xor_ln77_fu_570_p2;
wire   [0:0] and_ln79_fu_576_p2;
wire   [0:0] icmp_ln81_fu_564_p2;
wire   [0:0] or_ln79_fu_588_p2;
wire   [31:0] select_ln79_fu_582_p3;
wire   [31:0] select_ln79_1_fu_594_p3;
wire   [26:0] lshr_ln_fu_614_p4;
wire   [31:0] shl_ln85_fu_608_p2;
wire   [31:0] zext_ln85_fu_624_p1;
wire   [31:0] xor_ln85_fu_628_p2;
wire   [31:0] select_ln79_2_fu_600_p3;
wire   [1:0] trunc_ln87_fu_650_p1;
wire   [1:0] add_ln87_1_fu_660_p2;
wire   [0:0] icmp_ln89_fu_666_p2;
wire   [0:0] icmp_ln91_fu_672_p2;
wire   [0:0] xor_ln89_fu_684_p2;
wire   [0:0] and_ln91_fu_690_p2;
wire   [0:0] icmp_ln93_fu_678_p2;
wire   [0:0] or_ln91_fu_702_p2;
wire   [31:0] select_ln91_fu_696_p3;
wire   [31:0] select_ln91_1_fu_708_p3;
wire   [31:0] xor_ln85_1_fu_722_p2;
wire   [26:0] lshr_ln1_fu_738_p4;
wire   [31:0] shl_ln97_fu_732_p2;
wire   [31:0] zext_ln97_fu_748_p1;
wire   [31:0] xor_ln97_fu_752_p2;
wire   [31:0] add_ln97_2_fu_764_p2;
wire   [31:0] add_ln97_1_fu_769_p2;
wire   [31:0] add_ln97_fu_758_p2;
wire   [31:0] xor_ln97_1_fu_774_p2;
reg   [5:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 6'd1;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((mode_read_read_fu_90_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        i_0_reg_157 <= 6'd0;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        i_0_reg_157 <= i_2_reg_836;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1) & (mode_read_read_fu_90_p2 == 1'd1))) begin
        i_1_reg_199 <= 6'd0;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        i_1_reg_199 <= i_reg_879;
    end
end

always @ (posedge ap_clk) begin
    if (((mode_read_read_fu_90_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_0_reg_146 <= 37'd0;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        sum_0_reg_146 <= sum_2_reg_856;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1) & (mode_read_read_fu_90_p2 == 1'd1))) begin
        sum_1_reg_188 <= 38'd3337565984;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        sum_1_reg_188 <= sum_reg_899;
    end
end

always @ (posedge ap_clk) begin
    if (((mode_read_read_fu_90_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        v0_0_reg_168 <= word0;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        v0_0_reg_168 <= v0_fu_462_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1) & (mode_read_read_fu_90_p2 == 1'd1))) begin
        v0_1_reg_210 <= word0;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        v0_1_reg_210 <= v0_2_fu_780_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln44_fu_254_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        v0_3_reg_230 <= v0_0_reg_168;
    end else if (((icmp_ln75_fu_522_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        v0_3_reg_230 <= v0_1_reg_210;
    end
end

always @ (posedge ap_clk) begin
    if (((mode_read_read_fu_90_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        v1_0_reg_178 <= word1;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        v1_0_reg_178 <= v1_2_fu_516_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1) & (mode_read_read_fu_90_p2 == 1'd1))) begin
        v1_1_reg_220 <= word1;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        v1_1_reg_220 <= v1_fu_726_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln44_fu_254_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        v1_3_reg_242 <= v1_0_reg_178;
    end else if (((icmp_ln75_fu_522_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        v1_3_reg_242 <= v1_1_reg_220;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln44_fu_254_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        add_ln55_1_reg_851 <= add_ln55_1_fu_362_p2;
        add_ln55_reg_841 <= add_ln55_fu_352_p2;
        select_ln61_2_reg_861 <= select_ln61_2_fu_450_p3;
        sum_2_reg_856 <= sum_2_fu_372_p2;
        trunc_ln55_reg_846 <= trunc_ln55_fu_358_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln75_fu_522_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state4))) begin
        add_ln85_1_reg_894 <= add_ln85_1_fu_644_p2;
        add_ln85_reg_884 <= add_ln85_fu_634_p2;
        select_ln91_2_reg_904 <= select_ln91_2_fu_714_p3;
        sum_reg_899 <= sum_fu_654_p2;
        trunc_ln85_reg_889 <= trunc_ln85_fu_640_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        i_2_reg_836 <= i_2_fu_260_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        i_reg_879 <= i_fu_528_p2;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        result0_ap_vld = 1'b1;
    end else begin
        result0_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        result1_ap_vld = 1'b1;
    end else begin
        result1_ap_vld = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1) & (mode_read_read_fu_90_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else if (((mode_read_read_fu_90_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln44_fu_254_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state2;
        end
        ap_ST_fsm_state4 : begin
            if (((icmp_ln75_fu_522_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln55_1_fu_362_p2 = (select_ln49_2_fu_318_p3 + trunc_ln55_fu_358_p1);

assign add_ln55_fu_352_p2 = (xor_ln55_fu_346_p2 + v1_0_reg_178);

assign add_ln57_1_fu_378_p2 = ($signed(13'd6585) + $signed(trunc_ln57_fu_368_p1));

assign add_ln67_1_fu_505_p2 = (add_ln67_2_fu_500_p2 + trunc_ln55_reg_846);

assign add_ln67_2_fu_500_p2 = ($signed(32'd2654435769) + $signed(select_ln61_2_reg_861));

assign add_ln67_fu_494_p2 = (v0_fu_462_p2 + xor_ln67_fu_488_p2);

assign add_ln85_1_fu_644_p2 = (select_ln79_2_fu_600_p3 + trunc_ln85_fu_640_p1);

assign add_ln85_fu_634_p2 = (xor_ln85_fu_628_p2 + v0_1_reg_210);

assign add_ln87_1_fu_660_p2 = ($signed(2'd3) + $signed(trunc_ln87_fu_650_p1));

assign add_ln97_1_fu_769_p2 = (add_ln97_2_fu_764_p2 + trunc_ln85_reg_889);

assign add_ln97_2_fu_764_p2 = (32'd1640531527 + select_ln91_2_reg_904);

assign add_ln97_fu_758_p2 = (v1_fu_726_p2 + xor_ln97_fu_752_p2);

assign and_ln1_fu_394_p3 = {{tmp_4_fu_384_p4}, {11'd0}};

assign and_ln49_fu_294_p2 = (xor_ln47_fu_288_p2 & icmp_ln49_fu_276_p2);

assign and_ln61_fu_426_p2 = (xor_ln59_fu_420_p2 & icmp_ln61_fu_408_p2);

assign and_ln79_fu_576_p2 = (xor_ln77_fu_570_p2 & icmp_ln79_fu_558_p2);

assign and_ln91_fu_690_p2 = (xor_ln89_fu_684_p2 & icmp_ln91_fu_672_p2);

assign and_ln_fu_544_p3 = {{tmp_fu_534_p4}, {11'd0}};

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign i_2_fu_260_p2 = (i_0_reg_157 + 6'd1);

assign i_fu_528_p2 = (i_1_reg_199 + 6'd1);

assign icmp_ln44_fu_254_p2 = ((i_0_reg_157 == 6'd32) ? 1'b1 : 1'b0);

assign icmp_ln47_fu_270_p2 = ((trunc_ln44_fu_266_p1 == 2'd0) ? 1'b1 : 1'b0);

assign icmp_ln49_fu_276_p2 = ((trunc_ln44_fu_266_p1 == 2'd1) ? 1'b1 : 1'b0);

assign icmp_ln51_fu_282_p2 = ((trunc_ln44_fu_266_p1 == 2'd2) ? 1'b1 : 1'b0);

assign icmp_ln59_fu_402_p2 = ((and_ln1_fu_394_p3 == 13'd0) ? 1'b1 : 1'b0);

assign icmp_ln61_fu_408_p2 = ((and_ln1_fu_394_p3 == 13'd2048) ? 1'b1 : 1'b0);

assign icmp_ln63_fu_414_p2 = ((and_ln1_fu_394_p3 == 13'd4096) ? 1'b1 : 1'b0);

assign icmp_ln75_fu_522_p2 = ((i_1_reg_199 == 6'd32) ? 1'b1 : 1'b0);

assign icmp_ln77_fu_552_p2 = ((and_ln_fu_544_p3 == 13'd0) ? 1'b1 : 1'b0);

assign icmp_ln79_fu_558_p2 = ((and_ln_fu_544_p3 == 13'd2048) ? 1'b1 : 1'b0);

assign icmp_ln81_fu_564_p2 = ((and_ln_fu_544_p3 == 13'd4096) ? 1'b1 : 1'b0);

assign icmp_ln89_fu_666_p2 = ((add_ln87_1_fu_660_p2 == 2'd0) ? 1'b1 : 1'b0);

assign icmp_ln91_fu_672_p2 = ((add_ln87_1_fu_660_p2 == 2'd1) ? 1'b1 : 1'b0);

assign icmp_ln93_fu_678_p2 = ((add_ln87_1_fu_660_p2 == 2'd2) ? 1'b1 : 1'b0);

assign lshr_ln1_fu_738_p4 = {{v1_fu_726_p2[31:5]}};

assign lshr_ln2_fu_332_p4 = {{v1_0_reg_178[31:5]}};

assign lshr_ln3_fu_474_p4 = {{v0_fu_462_p2[31:5]}};

assign lshr_ln_fu_614_p4 = {{v0_1_reg_210[31:5]}};

assign mode_read_read_fu_90_p2 = mode;

assign or_ln49_fu_306_p2 = (icmp_ln47_fu_270_p2 | and_ln49_fu_294_p2);

assign or_ln61_fu_438_p2 = (icmp_ln59_fu_402_p2 | and_ln61_fu_426_p2);

assign or_ln79_fu_588_p2 = (icmp_ln77_fu_552_p2 | and_ln79_fu_576_p2);

assign or_ln91_fu_702_p2 = (icmp_ln89_fu_666_p2 | and_ln91_fu_690_p2);

assign result0 = v0_3_reg_230;

assign result1 = v1_3_reg_242;

assign select_ln49_1_fu_312_p3 = ((icmp_ln51_fu_282_p2[0:0] === 1'b1) ? key2 : key3);

assign select_ln49_2_fu_318_p3 = ((or_ln49_fu_306_p2[0:0] === 1'b1) ? select_ln49_fu_300_p3 : select_ln49_1_fu_312_p3);

assign select_ln49_fu_300_p3 = ((and_ln49_fu_294_p2[0:0] === 1'b1) ? key1 : key0);

assign select_ln61_1_fu_444_p3 = ((icmp_ln63_fu_414_p2[0:0] === 1'b1) ? key2 : key3);

assign select_ln61_2_fu_450_p3 = ((or_ln61_fu_438_p2[0:0] === 1'b1) ? select_ln61_fu_432_p3 : select_ln61_1_fu_444_p3);

assign select_ln61_fu_432_p3 = ((and_ln61_fu_426_p2[0:0] === 1'b1) ? key1 : key0);

assign select_ln79_1_fu_594_p3 = ((icmp_ln81_fu_564_p2[0:0] === 1'b1) ? key2 : key3);

assign select_ln79_2_fu_600_p3 = ((or_ln79_fu_588_p2[0:0] === 1'b1) ? select_ln79_fu_582_p3 : select_ln79_1_fu_594_p3);

assign select_ln79_fu_582_p3 = ((and_ln79_fu_576_p2[0:0] === 1'b1) ? key1 : key0);

assign select_ln91_1_fu_708_p3 = ((icmp_ln93_fu_678_p2[0:0] === 1'b1) ? key2 : key3);

assign select_ln91_2_fu_714_p3 = ((or_ln91_fu_702_p2[0:0] === 1'b1) ? select_ln91_fu_696_p3 : select_ln91_1_fu_708_p3);

assign select_ln91_fu_696_p3 = ((and_ln91_fu_690_p2[0:0] === 1'b1) ? key1 : key0);

assign shl_ln55_fu_326_p2 = v1_0_reg_178 << 32'd4;

assign shl_ln67_fu_468_p2 = v0_fu_462_p2 << 32'd4;

assign shl_ln85_fu_608_p2 = v0_1_reg_210 << 32'd4;

assign shl_ln97_fu_732_p2 = v1_fu_726_p2 << 32'd4;

assign sum_2_fu_372_p2 = (37'd2654435769 + sum_0_reg_146);

assign sum_fu_654_p2 = ($signed(38'd272223471175) + $signed(sum_1_reg_188));

assign tmp_4_fu_384_p4 = {{add_ln57_1_fu_378_p2[12:11]}};

assign tmp_fu_534_p4 = {{sum_1_reg_188[12:11]}};

assign trunc_ln44_fu_266_p1 = sum_0_reg_146[1:0];

assign trunc_ln55_fu_358_p1 = sum_0_reg_146[31:0];

assign trunc_ln57_fu_368_p1 = sum_0_reg_146[12:0];

assign trunc_ln85_fu_640_p1 = sum_1_reg_188[31:0];

assign trunc_ln87_fu_650_p1 = sum_1_reg_188[1:0];

assign v0_2_fu_780_p2 = (v0_1_reg_210 - xor_ln97_1_fu_774_p2);

assign v0_fu_462_p2 = (xor_ln55_1_fu_458_p2 + v0_0_reg_168);

assign v1_2_fu_516_p2 = (xor_ln67_1_fu_510_p2 + v1_0_reg_178);

assign v1_fu_726_p2 = (v1_1_reg_220 - xor_ln85_1_fu_722_p2);

assign xor_ln47_fu_288_p2 = (icmp_ln47_fu_270_p2 ^ 1'd1);

assign xor_ln55_1_fu_458_p2 = (add_ln55_reg_841 ^ add_ln55_1_reg_851);

assign xor_ln55_fu_346_p2 = (zext_ln55_fu_342_p1 ^ shl_ln55_fu_326_p2);

assign xor_ln59_fu_420_p2 = (icmp_ln59_fu_402_p2 ^ 1'd1);

assign xor_ln67_1_fu_510_p2 = (add_ln67_fu_494_p2 ^ add_ln67_1_fu_505_p2);

assign xor_ln67_fu_488_p2 = (zext_ln67_fu_484_p1 ^ shl_ln67_fu_468_p2);

assign xor_ln77_fu_570_p2 = (icmp_ln77_fu_552_p2 ^ 1'd1);

assign xor_ln85_1_fu_722_p2 = (add_ln85_reg_884 ^ add_ln85_1_reg_894);

assign xor_ln85_fu_628_p2 = (zext_ln85_fu_624_p1 ^ shl_ln85_fu_608_p2);

assign xor_ln89_fu_684_p2 = (icmp_ln89_fu_666_p2 ^ 1'd1);

assign xor_ln97_1_fu_774_p2 = (add_ln97_fu_758_p2 ^ add_ln97_1_fu_769_p2);

assign xor_ln97_fu_752_p2 = (zext_ln97_fu_748_p1 ^ shl_ln97_fu_732_p2);

assign zext_ln55_fu_342_p1 = lshr_ln2_fu_332_p4;

assign zext_ln67_fu_484_p1 = lshr_ln3_fu_474_p4;

assign zext_ln85_fu_624_p1 = lshr_ln_fu_614_p4;

assign zext_ln97_fu_748_p1 = lshr_ln1_fu_738_p4;

endmodule //xtea
