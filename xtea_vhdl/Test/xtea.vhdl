package XTEA_PACK is
  CONSTANT Reset_ST : INTEGER := 0;
  CONSTANT ST_0 : INTEGER := 1;
  CONSTANT ST_1 : INTEGER := 2;
  CONSTANT ST_2 : INTEGER := 3;
  CONSTANT ST_3 : INTEGER := 4;
  CONSTANT ST_4 : INTEGER := 5;
  CONSTANT ST_5 : INTEGER := 6;
  CONSTANT ST_6 : INTEGER := 7;
  CONSTANT ST_7 : INTEGER := 8;
  CONSTANT ST_8 : INTEGER := 9;
  CONSTANT ST_9 : INTEGER := 10;
  CONSTANT ST_10 : INTEGER := 11;
  CONSTANT Final_ST : INTEGER := 12;
end XTEA_PACK;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;
use WORK.XTEA_PACK.all;

entity XTEA is
	port (
		clk 			: in 	BIT;
		rst 			: in 	BIT;
		word0 		: in 	UNSIGNED (63 downto 0);
    word1 		: in 	UNSIGNED (63 downto 0);
		result0 	: out 	UNSIGNED (31 downto 0);
    result1 	: out 	UNSIGNED (31 downto 0);
		input_ready 	: in 	BIT;
		mode 			: in 	BIT;
		output_ready 	: out 	BIT;
	);
end XTEA;

architecture XTEA of XTEA is
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

			when Reset_ST =>
				NEXT_STATUS <= ST_0;;

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
        if COUNTER = "100000" then
          NEXT_STATUS <= ST_2;
        else
          NEXT_STATUS <= Final_ST;
        end if;

			when ST_9 =>
				NEXT_STATUS <= ST_10;

			when ST_10 =>
      if COUNTER = "100000" then
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
			else if clk = '1'

				STATUS <= NEXT_STATUS;

				case NEXT_STATUS is

					when Reset_ST =>
						result0 <= ZERO;
            result1 <= ZERO;
						output_ready <= '0';

					when ST_0 =>
            COUNTER <= 0;

					when ST_1 =>
            WORD0 <= word0;
            WORD1 <= word1;

					when ST_2 =>
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

					when ST_3 =>
            SUM <= "11000110111011110011011100100000";

					when ST_4 =>
						WORD0 <= WORD0;
            SUM <= SUM + DELTA;

					when ST_5 =>
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

					when ST_6 =>
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

					when ST_7 =>
						WORD1 <= WORD1;
						SUM <= "11000110111011110011011100100000";

					when ST_8 =>
						word1 =  WORD1;
            if COUNTER < '31' then
              COUNTER <= COUNTER + 1;
            end if;

					when ST_9 =>
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

					when ST_10 =>
						word0 <= WORD0;
            if COUNTER < '31' then
              COUNTER <= COUNTER + 1;
            end if;

					when Final_ST =>
						result0 <= WORD0;
            result1 <= WORD1;
            output_ready <= 1;

					when others =>
						result <= ZERO;
				end case;
			end if;
		end process;
end architecture;
