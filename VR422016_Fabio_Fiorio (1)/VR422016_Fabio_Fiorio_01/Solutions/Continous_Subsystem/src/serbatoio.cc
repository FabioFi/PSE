#include "serbatoio.hh"

serbatoio::serbatoio(sc_core::sc_module_name _name):
  sc_core::sc_module(_name),
  in("in"),
  out("out"),
  guadagno1("guadagno1", 0.6),
  guadagno2("guadagno2", -0.03),
  integratore("integratore"),
  add("add"),
  lsf_tdf("lsf_tdf"),
  tdf_lsf("tdf_lsf"),
  sig1("sig1"),
  sig2("sig2"),
  sig3("sig3"),
  sig4("sig4"),
  sig5("sig5")
  {
    //realizzazione del modulo
    tdf_lsf.inp(in);
    tdf_lsf.y(sig1);

    guadagno1.x(sig1);
    guadagno1.y(sig2);

    guadagno1.set_timestep(1, sc_core::SC_MS);

    add.x1(sig2);
    add.x2(sig5);
    add.y(sig3);

    integratore.x(sig3);
    integratore.y(sig4);

    guadagno2.x(sig4);
    guadagno2.y(sig5);

    lsf_tdf.x(sig4);
    lsf_tdf.outp(out);
  }

  serbatoio::~serbatoio(){

  }
