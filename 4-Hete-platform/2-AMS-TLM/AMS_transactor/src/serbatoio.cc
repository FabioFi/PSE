#include "serbatoio.hh"

serbatoio::serbatoio(sc_core::sc_module_name name):
  sc_core::sc_module(name),
  valvola_apertura("valvola_apertura"),
  livello_acqua("livello_acqua"),
  apertura("apertura"),
  livello_acqua_out("livello_acqua_out"),
  integratore("integratore"),
  guadagno1("guadagno1", 0.6),
  guadagno2("guadagno2", 0.03),
  sub1("sub1"),
  sig1("sig1"),
  sig2("sig2"),
  sig3("sig3")
{
  apertura.inp(in);
  apertura.y(valvola_apertura);

  guadagno1.x(valvola_apertura);
  guadagno1.y(sig1);
  guadagno1.set_timestep(1, sc_core::SC_MS );

  sub1.x1(sig1);
  sub1.x2(sig3);
  sub1.y(sig2);

  integratore.x(sig2);
  integratore.y(livello_acqua);

  guadagno2.x(livello_acqua);
  guadagno2.y(sig3);

  livello_acqua_out.x(livello_acqua);
  livello_acqua_out.outp(out);
}
