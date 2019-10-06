library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;

package XTEA_PACK is
  CONSTANT Reset_ST : UNSIGNED(3 downto 0) := "0000";
  CONSTANT ST_0 : UNSIGNED(3 downto 0) := "0001";
  CONSTANT ST_1 : UNSIGNED(3 downto 0) := "0010";
  CONSTANT ST_2 : UNSIGNED(3 downto 0) := "0011";
  CONSTANT ST_3 : UNSIGNED(3 downto 0) := "0100";
  CONSTANT ST_4 : UNSIGNED(3 downto 0) := "0101";
  CONSTANT ST_5 : UNSIGNED(3 downto 0) := "0110";
  CONSTANT ST_6 : UNSIGNED(3 downto 0) := "0111";
  CONSTANT ST_7 : UNSIGNED(3 downto 0) := "1000";
  CONSTANT ST_8 : UNSIGNED(3 downto 0) := "1001";
  CONSTANT ST_9 : UNSIGNED(3 downto 0) := "1010";
  CONSTANT ST_10 : UNSIGNED(3 downto 0) := "1011";
  CONSTANT Final_ST : UNSIGNED(3 downto 0) := "1100";
end XTEA_PACK;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;
use WORK.XTEA_PACK.all;

entity XTEA is
	port (
		clk 			: in 	BIT;
		rst 			: in 	BIT;
		word0 		: in 	UNSIGNED (31 downto 0);
    word1 		: in 	UNSIGNED (31 downto 0);
    KEY0 	    : in 	UNSIGNED (31 downto 0);
    KEY1 	    : in 	UNSIGNED (31 downto 0);
    KEY2 	    : in 	UNSIGNED (31 downto 0);
    KEY3 	    : in 	UNSIGNED (31 downto 0);
		input_ready 	: in 	BIT;
		mode 			: in 	BIT;
    result0 	: out 	UNSIGNED (31 downto 0);
    result1 	: out 	UNSIGNED (31 downto 0);
		output_ready 	: out 	BIT
	);
end XTEA;

architecture XTEA of XTEA is
	subtype STATUS_T 		is UNSIGNED (3 downto 0);
	subtype INTERNAL32_T 	is UNSIGNED (31 downto 0);
  subtype INTERNAL64_T is UNSIGNED (63 downto 0);

	signal STATUS 		: STATUS_T;
	signal NEXT_STATUS 	: STATUS_T;
	signal V0 		: INTERNAL32_T;
	signal V1 		: INTERNAL32_T;
	signal COUNTER 		: UNSIGNED(5 downto 0);
	signal SUM 			: INTERNAL64_T;
  signal TEMP0    : INTERNAL32_T;
  signal TEMP1    : INTERNAL32_T;
	signal DELTA 		: INTERNAL32_T := "10011110001101110111100110111001";
	constant ZERO 		: INTERNAL32_T := "00000000000000000000000000000000";
	constant ONE 		: INTERNAL32_T := "00000000000000000000000000000001";
	constant TWO 		: INTERNAL32_T := "00000000000000000000000000000010";
	constant THREE 		: INTERNAL32_T := "00000000000000000000000000000011";

begin
	-- FSM
	process (STATUS, input_ready)
	begin
		case STATUS is

			when Reset_ST =>
				NEXT_STATUS <= ST_0;

			when ST_0 =>
				if input_ready = '1' then
					NEXT_STATUS <= ST_1;
				else
					NEXT_STATUS <= ST_0;
				end if;

			when ST_1 =>
				if mode = '0' then
					NEXT_STATUS <= ST_2;
				else
					NEXT_STATUS <= ST_3;
				end if;

			when ST_2 =>
				NEXT_STATUS <= ST_4;

			when ST_3 =>
				NEXT_STATUS <= ST_5;

			when ST_4 =>
				NEXT_STATUS <= ST_6;

			when ST_5 =>
				NEXT_STATUS <= ST_7;

			when ST_6 =>
				NEXT_STATUS <= ST_8;

			when ST_7 =>
				NEXT_STATUS <= ST_9;

			when ST_8 =>
        if COUNTER < "11111" then
          NEXT_STATUS <= ST_2;
        else
          NEXT_STATUS <= Final_ST;
        end if;

			when ST_9 =>
				NEXT_STATUS <= ST_10;

			when ST_10 =>
      if COUNTER < "11111" then
        NEXT_STATUS <= ST_5;
      else
        NEXT_STATUS <= Final_ST;
      end if;

			when Final_ST =>
				NEXT_STATUS <= ST_0;

			when others =>
				NEXT_STATUS <= STATUS;

		end case;
	end process;

	-- DATAPATH
	process (clk, rst)
		begin
			if rst = '0' then
				STATUS <= Reset_ST;
			elsif clk = '1' then
				STATUS <= NEXT_STATUS;
				case NEXT_STATUS is

					when Reset_ST =>
						result0 <= ZERO;
            result1 <= ZERO;
						output_ready <= '0';

					when ST_0 =>
            COUNTER <= "000000";
            V0 <= ZERO;
            V1 <= ZERO;
            SUM <= "0000000000000000000000000000000000000000000000000000000000000000";
            TEMP0 <= ZERO;
            TEMP1 <= ZERO;
            DELTA <= "10011110001101110111100110111001";

					when ST_1 =>
            V0 <= word0;
            V1 <= word1;

					when ST_2 =>
            if (SUM(31 downto 0) and THREE) = ZERO then
              TEMP0 <= KEY0;
            elsif (SUM(31 downto 0) and THREE) = ONE then
              TEMP0 <= KEY1;
            elsif (SUM(31 downto 0) and THREE) = TWO then
              TEMP0 <= KEY2;
            else
              TEMP0 <= KEY3;
            end if;

					when ST_3 =>
            SUM <= DELTA * 100000;

					when ST_4 =>
						V0 <= V0 + (V1 sll 4 xor (V1 srl 5) + V1 xor SUM(31 downto 0) + TEMP0);
            SUM <= SUM + DELTA;

					when ST_5 =>
            if ((SUM(31 downto 0) srl 11) and THREE) = ZERO then
              TEMP0 <= KEY0;
            elsif ((SUM(31 downto 0) srl 11) and THREE) = ONE then
              TEMP0 <=  KEY1;
            elsif ((SUM(31 downto 0) srl 11) and THREE) = TWO then
              TEMP0 <= KEY2;
            else
              TEMP0 <= KEY3;
            end if;

					when ST_6 =>
            if ((SUM(31 downto 0) srl 11) and THREE) = ZERO then
              TEMP0 <= KEY0;
            elsif ((SUM(31 downto 0) srl 11) and THREE) =  ONE then
              TEMP0 <= KEY1;
            elsif ((SUM(31 downto 0) srl 11) and THREE) =  TWO then
              TEMP0 <= KEY2;
            else
              TEMP0 <= KEY3;
            end if;

					when ST_7 =>
						V1 <= V1 + (V0 sll 4 xor (V0 srl 5) + V0 xor SUM(31 downto 0) + TEMP0);
						SUM <= SUM - DELTA;

					when ST_8 =>
            V1 <= V1 + (V0 sll 4 xor (V0 srl 5) + V0 xor SUM(31 downto 0) + TEMP0);
            if COUNTER < "11111" then
              COUNTER <= COUNTER + 1;
            end if;

					when ST_9 =>
							if (SUM(31 downto 0) and THREE) = ZERO then
                TEMP0 <= KEY0;
							elsif (SUM(31 downto 0) and THREE) = ONE then
                TEMP0 <= KEY1;
							elsif (SUM(31 downto 0) and THREE) = TWO then
                TEMP0 <= KEY2;
							else
                TEMP0 <= KEY3;
						end if;

					when ST_10 =>
						V0 <= V0 + (V1 sll 4 xor (V1 srl 5) + V1 xor SUM(31 downto 0) + TEMP0);
            if COUNTER < "11111" then
              COUNTER <= COUNTER + 1;
            end if;

					when Final_ST =>
						result0 <= V0;
            result1 <= V1;
            output_ready <= '1';

					when others =>
						result0 <= ZERO;
            result0 <= ZERO;
				end case;
			end if;
		end process;
end XTEA;
