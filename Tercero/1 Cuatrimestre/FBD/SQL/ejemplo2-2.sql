INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
	VALUES ('12345678', 'Pepe', 'soltero', SYSDATE);

INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
	VALUES ('87654321','Juan','casado',SYSDATE);

INSERT INTO plantilla (dni,estadocivil) VALUES ('11223344','soltero');

SELECT * FROM plantilla;
