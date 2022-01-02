INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
	VALUES ('87654321','Juan','casado',SYSDATE);

UPDATE plantilla
SET fechaalta = fechaalta+1
WHERE nombre = 'Juan';
