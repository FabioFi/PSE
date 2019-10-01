#include "systemc.h"

SC_MODULE(xtea_RTL)
{

    public:
        sc_in<sc_uint<1> > input_rdy;
        sc_in<sc_uint<32> > word1;
        sc_in<sc_uint<32> > word2;
        sc_in<sc_uint<32> > key0;
        sc_in<sc_uint<32> > key1;
        sc_in<sc_uint<32> > key2;
        sc_in<sc_uint<32> > key3;
        sc_in<sc_uint<1> > mode;
        sc_out<sc_uint<32> > result0;
        sc_out<sc_uint<32> > result1;
        sc_out<sc_uint<1> > output_rdy;
        sc_in<bool> rst;
        sc_in<bool> clk;

        typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4, ST_5, ST_6, ST_7, ST_8, ST_9, ST_10, Final_ST, Wait_RESULT} STATES;

        sc_signal<STATES> STATUS, NEXT_STATUS;
        sc_signal<sc_uint<6> > counter;
        sc_signal<sc_uint<32> > delta;
        sc_signal<sc_uint<32> > v0;
        sc_signal<sc_uint<32> > v1;
        sc_signal<sc_uint<64> > sum;
        sc_signal<sc_uint<32> > temp0;
        sc_signal<sc_uint<32> > temp1;

        void datapath(void){
            if (rst.read() == 0)
            {
                STATUS = Reset_ST;
            }
            else if (clk.read() == 1)
            {
                STATUS = NEXT_STATUS;

                switch(STATUS){
                    case Reset_ST:
                    result0.write(0);
                    result1.write(0);
                    output_rdy.write(0);
                    break;

                case ST_0:
                    output_rdy.write(0);
                    counter.write(0);
                    v0.write(0);
                    v1.write(0);
                    sum.write(0);
                    temp0.write(0);
                    temp1.write(0);
                    delta.write(0x9e3779b9);
                    break;

                case ST_1:
                    v0.write(word1.read());
                    v1.write(word2.read());
                    //cout << "[RTL:] " << word1.read() << " e " << word2.read() << endl;
                    break;

                case ST_2:
                    // cout << "inizio a criptare - NO" << endl;
                    // cout << counter.read() << endl;
                    // cout << "v0: "<< v0.read() << endl;
                    // cout << "v1: "<< v1.read() << endl;
                    if((sum.read() & 3) == 0)
                    temp0.write(key0.read());
                    else if((sum.read() & 3) == 1)
                    temp0.write(key1.read());
                    else if((sum.read() & 3) == 2)
                    temp0.write(key2.read());
                    else temp0.write(key3.read());
                    break;

                case ST_3:
                    //cout << "inizio a decriptare" << endl;
                    sum.write(delta.read() * 32);
                    break;

                case ST_4:
                    v0.write(v0.read() + (((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp0.read()))));
                    sum.write(sum.read() + delta.read());
                        break;

                case ST_5:
                    if(((sum.read() >> 11) & 3) == 0)
                    temp0.write(key0.read());
                    else if(((sum.read() >> 11) & 3) == 1)
                    temp0.write(key1.read());
                    else if(((sum.read() >> 11) & 3) == 2)
                    temp0.write(key2.read());
                    else temp0.write(key3.read());
                    break;

                case ST_6:
                    if(((sum.read() >> 11) & 3) == 0)
                    temp0.write(key0.read());
                    else if(((sum.read() >> 11) & 3) == 1)
                    temp0.write(key1.read());
                    else if(((sum.read() >> 11) & 3) == 2)
                    temp0.write(key2.read());
                    else temp0.write(key3.read());
                    break;

                case ST_7:
                    //cout << "v0: " << v0.read() << " v1: " << v1.read() << endl;
                    v1.write(v1.read() - (((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp0.read()))));
                    sum.write(sum.read() - delta.read());
                    break;

                case ST_8:
                    v1.write(v1.read() + (((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + temp0.read()))));
                    //v1.write(v1.read() + (((v0.read() << 4) ^ (v0.read() >> 5) + v0.read()) ^ (sum.read() + temp0.read())));
                    if(counter.read() < 31){
                    counter.write(counter.read() + 1);
                    }
                    break;

                case ST_9:
                    if((sum.read() & 3) == 0)
                    temp0.write(key0.read());
                    else if((sum.read() & 3) == 1)
                    temp0.write(key1.read());
                    else if((sum.read() & 3) == 2)
                    temp0.write(key2.read());
                    else temp0.write(key3.read());
                    break;

                case ST_10:
                    v0.write(v0.read() - (((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + temp0.read()))));
                    if(counter.read() < 31){
                        counter.write(counter.read() + 1);
                    }
                    break;

                case Final_ST:
                    result0.write(v0.read());
                    result1.write(v1.read());
                    //cout << "[RTL:] i risultati sono pronti: " << v0.read() << " e " << v1.read() << endl;
                    //output_rdy.write(1);
                    break;
                case Wait_RESULT:
                    //cout << "[RTL:] i risultati sono pronti: " << result0.read() << " e " << result1.read() << endl;
                    output_rdy.write(1);
                    break;
                }
            }
        }


        void fsm(void)
        {
            NEXT_STATUS = STATUS;

            switch(STATUS)
            {
                case Reset_ST:
                NEXT_STATUS = ST_0;
                break;

                case ST_0:
                    if (input_rdy.read() == 1){
                        NEXT_STATUS = ST_1;
                    } else {
                        NEXT_STATUS = ST_0;
                    }
                    break;

                case ST_1:
                    if(mode.read() == 0){
                        NEXT_STATUS = ST_2;
                    }
                    else if(mode.read() == 1){
                        NEXT_STATUS = ST_3;
                    }
                    break;

                case ST_2:
                    NEXT_STATUS = ST_4;
                    break;

                case ST_3:
                    NEXT_STATUS = ST_5;
                    break;

                case ST_4:
                    NEXT_STATUS = ST_6;
                    break;

                case ST_5:
                    NEXT_STATUS = ST_7;
                    break;

                case ST_6:
                    NEXT_STATUS = ST_8;
                    break;

                case ST_7:
                    NEXT_STATUS = ST_9;
                    break;

                case ST_8:
                    if(counter.read() < 31){
                        NEXT_STATUS = ST_2;
                    } else
                        NEXT_STATUS = Final_ST;
                    break;

                case ST_9:
                    NEXT_STATUS = ST_10;
                    break;

                case ST_10:
                    if(counter.read() < 31){
                        NEXT_STATUS = ST_5;
                    } else
                        NEXT_STATUS = Final_ST;
                    break;

                case Final_ST:
                    //  cout << "result" <<endl;
                    //NEXT_STATUS = ST_0;
                    NEXT_STATUS = Wait_RESULT;
                    break;
                    case Wait_RESULT:
                    NEXT_STATUS = ST_0;
                    // if (rst.read() == 0)
                    //   NEXT_STATUS = Wait_RESULT;
                    // else
                    //   NEXT_STATUS = ST_0;
                    break;
            }
        }


        SC_CTOR(xtea_RTL) // :
        	// STATUS(ST_0),
			    // NEXT_STATUS(ST_0)
        {
            SC_METHOD(datapath);
            sensitive << rst;
            sensitive_pos << clk;

            SC_METHOD(fsm);
            sensitive << STATUS << input_rdy << word1 << word2 << counter;
        }
};
