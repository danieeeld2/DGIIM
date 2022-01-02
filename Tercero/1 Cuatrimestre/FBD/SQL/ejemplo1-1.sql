CREATE TABLE plantilla(
	dni varchar2(9),
	nombre varchar2(15),
	estadocivil varchar2(10)
		CHECK (estadocivil IN ('soltero', 'casado', 'divorciado', 'viudo')),
	fechalta date,
	PRIMARY KEY(dni));
