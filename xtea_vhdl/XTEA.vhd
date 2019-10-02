library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;

package XTEA_PACK is
	-- States definition
	constant IDLE 				: UNSIGNED(3 downto 0) := "0000";
	constant BUSY_KEY1 			: UNSIGNED(3 downto 0) := "0001";
	constant BUSY_KEY2 			: UNSIGNED(3 downto 0) := "0010";
	constant BUSY_ENC_INPUT 	: UNSIGNED(3 downto 0) := "0011";
	constant BUSY_ENC1 			: UNSIGNED(3 downto 0) := "0100";
	constant BUSY_ENC2 			: UNSIGNED(3 downto 0) := "0101";
	constant BUSY_ENC_OUTPUT1	: UNSIGNED(3 downto 0) := "0110";
	constant BUSY_ENC_OUTPUT2	: UNSIGNED(3 downto 0) := "0111";
	constant BUSY_DEC_INPUT 	: UNSIGNED(3 downto 0) := "1000";
	constant BUSY_DEC1 			: UNSIGNED(3 downto 0) := "1001";
	constant BUSY_DEC2 			: UNSIGNED(3 downto 0) := "1010";
	constant BUSY_DEC_OUTPUT1 	: UNSIGNED(3 downto 0) := "1011";
	constant BUSY_DEC_OUTPUT2 	: UNSIGNED(3 downto 0) := "1100";
end XTEA_PACK;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;
use WORK.XTEA_PACK.all;

entity XTEA is
	port (
		clk 			: in 	BIT;
		rst 			: in 	BIT;
		word 		: in 	UNSIGNED (63 downto 0);
		result 	: out 	UNSIGNED (31 downto 0);
		input_ready 	: in 	BIT;
		mode 			: in 	BIT;
		output_ready 	: out 	BIT
	);
end XTEA;

architecture BEHAVIORAL of XTEA is
	subtype STATUS_T 		is UNSIGNED (3 downto 0);
	subtype INTERNAL32_T 	is UNSIGNED (31 downto 0);

	signal STATUS 		: STATUS_T;
	signal NEXT_STATUS 	: STATUS_T;
	signal KEY0 		: INTERNAL32_T;
	signal KEY1 		: INTERNAL32_T;
	signal KEY2 		: INTERNAL32_T;
	signal KEY3 		: INTERNAL32_T;
	signal WORD0 		: INTERNAL32_T;
	signal WORD1 		: INTERNAL32_T;
	signal COUNTER 		: UNSIGNED(5 downto 0);
	signal SUM 			: INTERNAL32_T;

	-- 0x9e3779b9
	constant DELTA 		: INTERNAL32_T := "10011110001101110111100110111001";
	constant ZERO 		: INTERNAL32_T := "00000000000000000000000000000000";
	constant ONE 		: INTERNAL32_T := "00000000000000000000000000000001";
	constant TWO 		: INTERNAL32_T := "00000000000000000000000000000010";
	constant THREE 		: INTERNAL32_T := "00000000000000000000000000000011";
begin
	-- FSM
	process (STATUS, input_ready)
	begin
		case STATUS is
			when IDLE =>
				if input_ready = '1' then
					NEXT_STATUS <= BUSY_KEY1;
				else
					NEXT_STATUS <= IDLE;
				end if;
			when BUSY_KEY1 =>
				if input_ready = '1' then
					NEXT_STATUS <= BUSY_KEY2;
				else
					NEXT_STATUS <= BUSY_KEY1;
				end if;
			when BUSY_KEY2 =>
				if mode = '0' then
					NEXT_STATUS <= BUSY_ENC_INPUT;
				else
					NEXT_STATUS <= BUSY_DEC_INPUT;
				end if;
			when BUSY_ENC_INPUT =>
				if input_ready = '1' then
					NEXT_STATUS <= BUSY_ENC1;
				else
					NEXT_STATUS <= BUSY_ENC_INPUT;
				end if;
			when BUSY_ENC1 =>
				NEXT_STATUS <= BUSY_ENC2;
			when BUSY_ENC2 =>
				if COUNTER = "100000" then
					NEXT_STATUS <= BUSY_ENC_OUTPUT1;
				else
					NEXT_STATUS <= BUSY_ENC1;
				end if;
			when BUSY_ENC_OUTPUT1 =>
				NEXT_STATUS <= BUSY_ENC_OUTPUT2;
			when BUSY_ENC_OUTPUT2 =>
				NEXT_STATUS <= BUSY_ENC_OUTPUT1;
			when BUSY_DEC_INPUT =>
				if input_ready = '1' then
					NEXT_STATUS <= BUSY_DEC1;
				else
					NEXT_STATUS <= BUSY_DEC_INPUT;
				end if;
			when BUSY_DEC1 =>
				NEXT_STATUS <= BUSY_DEC2;
			when BUSY_DEC2 =>
				if COUNTER = "100000" then
					NEXT_STATUS <= BUSY_DEC_OUTPUT1;
				else
					NEXT_STATUS <= BUSY_DEC1;
				end if;
			when BUSY_DEC_OUTPUT1 =>
				NEXT_STATUS <= BUSY_DEC_OUTPUT2;
			when BUSY_DEC_OUTPUT2 =>
				NEXT_STATUS <= BUSY_DEC_OUTPUT1;
			when others =>
				NEXT_STATUS <= STATUS;
		end case;
	end process;

	-- DATAPATH
	process (clk, rst)
		begin
			if rst = '1' then
				STATUS <= IDLE;
				result <= ZERO;
				output_ready <= '0';
				KEY0 <= ZERO;
				KEY1 <= ZERO;
				KEY2 <= ZERO;
				KEY3 <= ZERO;
				WORD0 <= ZERO;
				WORD1 <= ZERO;
				COUNTER <= "000000";
				SUM <= ZERO;
			else
				STATUS <= NEXT_STATUS;
				case NEXT_STATUS is
					when IDLE =>
						result <= ZERO;
						output_ready <= '0';
					when BUSY_KEY1 =>
						KEY0 <= word(31 downto 0);
						KEY1 <= word(63 downto 32);
					when BUSY_KEY2 =>
						KEY2 <= word(31 downto 0);
						KEY3 <= word(63 downto 32);
					when BUSY_ENC_INPUT =>
						WORD0 <= word(31 downto 0);
						WORD1 <= word(63 downto 32);
					when BUSY_ENC1 =>
						case (SUM and THREE) is
							when ZERO =>
							WORD0 <= WORD0 + ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY0));
							when ONE =>
							WORD0 <= WORD0 + ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY1));
							when TWO =>
							WORD0 <= WORD0 + ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY2));
							when others =>
							WORD0 <= WORD0 + ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY3));
						end case;
						SUM <= SUM + delta;
					when BUSY_ENC2 =>
						case ((SUM srl 11) and THREE) is
							when ZERO =>
							WORD1 <= WORD1 + ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY0));
							when ONE =>
							WORD1 <= WORD1 + ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY1));
							when TWO =>
							WORD1 <= WORD1 + ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY2));
							when others =>
							WORD1 <= WORD1 + ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY3));
						end case;
						COUNTER <= COUNTER + 1;
					when BUSY_ENC_OUTPUT1 =>
						result <= WORD0;
						output_ready <= '1';
					when BUSY_ENC_OUTPUT2 =>
						result <= WORD1;
					when BUSY_DEC_INPUT =>
						WORD0 <= word(31 downto 0);
						WORD1 <= word(63 downto 32);
						SUM <= "11000110111011110011011100100000";
					when BUSY_DEC1 =>
						case ((SUM srl 11) and THREE) is
							when ZERO =>
							WORD1 <= WORD1 - ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY0));
							when ONE =>
							WORD1 <= WORD1 - ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY1));
							when TWO =>
							WORD1 <= WORD1 - ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY2));
							when others =>
							WORD1 <= WORD1 - ((((WORD0 sll 4) xor (WORD0 srl 5)) + WORD0) xor (SUM + KEY3));
						end case;
						SUM <= SUM - delta;
					when BUSY_DEC2 =>
						case (SUM and THREE) is
							when ZERO =>
							WORD0 <= WORD0 - ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY0));
							when ONE =>
							WORD0 <= WORD0 - ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY1));
							when TWO =>
							WORD0 <= WORD0 - ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY2));
							when others =>
							WORD0 <= WORD0 - ((((WORD1 sll 4) xor (WORD1 srl 5)) + WORD1) xor (SUM + KEY3));
						end case;
						COUNTER <= COUNTER + 1;
					when BUSY_DEC_OUTPUT1 =>
						result <= WORD0;
						output_ready <= '1';
					when BUSY_DEC_OUTPUT2=>
						result <= WORD1;
					when others =>
						result <= ZERO;
				end case;
			end if;
		end process;
end architecture;
