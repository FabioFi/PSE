PACKAGE root_pack IS
  CONSTANT SIZE : INTEGER := 32;
  CONSTANT Reset_ST : INTEGER := 0;	
  CONSTANT ST_0 : INTEGER := 1;
  CONSTANT ST_1 : INTEGER := 2;
  CONSTANT ST_2 : INTEGER := 3;
  CONSTANT ST_3 : INTEGER := 4;
  CONSTANT ST_4 : INTEGER := 5;
END root_pack;

LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE WORK.root_pack.ALL;
USE IEEE.NUMERIC_BIT.ALL;

entity root is
	port (	clock, reset   : in  bit;
		number_port    : in  UNSIGNED (SIZE-1 DOWNTO 0);
		number_isready : in  bit;
		result_port    : out UNSIGNED (SIZE-1 DOWNTO 0);
		result_isready : out  bit
	) ;
end root;

architecture root of root is
	subtype status_t is integer range 0 to 5;
	subtype internal_t is UNSIGNED (SIZE-1 DOWNTO 0);
	signal STATUS: status_t;
	signal NEXT_STATUS: status_t;
	signal Root: internal_t;
	signal Number: internal_t;
	signal Counter: internal_t;
	signal Rem_s: internal_t;
	CONSTANT ZERO : internal_t := "00000000000000000000000000000000";
	CONSTANT SEDICI : internal_t := "00000000000000000000000000010000";

begin

process(STATUS, number_isready, number_port, Counter) 
-- elaborate_SQRT
	begin
		case STATUS is
		  when Reset_ST => 
			NEXT_STATUS<=ST_0;
		  when ST_0 => 
			if number_isready = '1' then
			  NEXT_STATUS<=ST_1;
			else 
			  NEXT_STATUS<=ST_0;
			end if;
		  when ST_1   =>
			NEXT_STATUS<=ST_2;
		  when ST_2   =>
			if Counter<16 then
			  NEXT_STATUS<=ST_3;
			else 
			  NEXT_STATUS<=ST_4;
			end if;
		  when ST_3  =>
			NEXT_STATUS<=ST_2;
		  when ST_4  =>
			NEXT_STATUS<=ST_0;
		  when others =>
			NEXT_STATUS<=STATUS;
		end case;
	end process;
	
process(clock, reset) 
-- elaborate_SQRT_FSM
	begin
	  if reset='0' then 
		STATUS<=Reset_ST;
	  elsif clock'event and clock='1' then 
		STATUS<=NEXT_STATUS;
		case NEXT_STATUS is
		  when Reset_ST => 
			result_port <= ZERO;
			result_isready <= '0' ;
		  when ST_0 => 
			result_port <= ZERO;
			result_isready <= '0' ;
			Rem_s<=ZERO;
			Root<=ZERO;
			Counter<=ZERO;
		  when ST_1   =>
                        Number<= number_port; 
		  when ST_2   =>
                        if Counter<SEDICI then
			    Rem_s<=(Rem_s sll 2)+(Number srl 30); 
			    Root<=Root sll 1; 
			    Number<=Number sll 2; 
                        end if;
		  when ST_3  =>
                        if Root<Rem_s then 
			    Rem_s<=Rem_s - Root - 1;
			    Root<= Root +2;
                        end if;
                        Counter<=Counter+1;
		  when ST_4  =>
			result_port <= Root srl 1;
			result_isready <= '1';
		end case;
	  end if;
        end process;
	
end root;
