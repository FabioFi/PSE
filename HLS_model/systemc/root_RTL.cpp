#include "systemc.h"

SC_MODULE(root_RTL)
{

    public:
        sc_in<sc_uint<1> >    number_isready;
        sc_in<sc_uint<32> >   number_port;
        sc_out<sc_uint<32> >  result_port;
        sc_out<sc_uint<1> >   result_isready;
        sc_in<sc_uint<1> > reset;
        sc_in_clk clk;

        typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4} STATES;

        STATES STATUS, NEXT_STATUS;
        sc_signal<sc_uint<32> > Rem;
        sc_signal<sc_uint<32> > Root;
        sc_signal<sc_uint<32> > Number;
        sc_signal<sc_uint<5> >  Counter;

        void elaborate_SQRT(void){
            if (reset.read() == 0)
            {
                STATUS = Reset_ST;
            }
            else if (clk.read() == 1)
            {
                STATUS = NEXT_STATUS;

                switch(STATUS){
                    case Reset_ST:
                        result_port.write(0);
                        result_isready.write(0);
                        break;
                    case ST_0:
                        result_port.write(0);
                        result_isready.write(0);
                        Rem.write(0);
                        Root.write(0);
                        Counter.write(0);
                        break;
                    case ST_1:
                        Number = number_port.read();
                        break;
                    case ST_2:
                        if (Counter.read() < 16)
                        {
                            Rem.write((Rem.read() << 2) + (Number.read() >> 30));
                            Number.write(Number.read() << 2);
                            Root.write(Root.read() << 1);
                        }
                        break;
                    case ST_3:
                        if (Root.read() < Rem.read())
                        {
                            Rem.write(Rem.read() - Root.read() - 1);
                            Root.write(Root.read() + 2);
                        }
                        Counter.write(Counter.read() + 1);
                        break;
                    case ST_4:
                        result_isready.write(1);
                        result_port.write( Root.read() >> 1 );
                        break;
                }
            }
        }


        void elaborate_SQRT_FSM(void)
        {
            NEXT_STATUS = STATUS;

            switch(STATUS)
            {
                case Reset_ST:
                    NEXT_STATUS = ST_0;
                    break;

                case ST_0:
                    if (number_isready.read() == 1)
                    {
                        NEXT_STATUS = ST_1;
                    }
                    else
                    {
                        NEXT_STATUS = ST_0;
                    }
                    break;

                case ST_1:
                    NEXT_STATUS = ST_2;
                    break;

                case ST_2:
                    if (Counter.read() < 16)
                    {
                        NEXT_STATUS = ST_3;
                    }
                    else
                    {
                        NEXT_STATUS = ST_4;
                    }
                    break;

                case ST_3:
                    NEXT_STATUS = ST_2;
                    break;

                case ST_4:
                    NEXT_STATUS = ST_0;
                    break;
            }
        }


        SC_CTOR(root_RTL) :
        	STATUS(ST_0),
			NEXT_STATUS(ST_0)
        {
            SC_METHOD(elaborate_SQRT);
            sensitive << reset;
            sensitive_pos << clk;

            SC_METHOD(elaborate_SQRT_FSM);
            sensitive << number_isready << number_port << Counter;
        }
};


