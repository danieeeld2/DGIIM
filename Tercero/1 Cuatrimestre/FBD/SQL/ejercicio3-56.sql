SELECT nompro
FROM proveedor
WHERE codpro IN (
	SELECT DISTINCT v1.codpro
	FROM (
		SELECT codpro, codpie
		FROM ventas NATURAL JOIN (
			SELECT codpie
			FROM pieza
			WHERE color='Rojo')) v1,
	(SELECT codpro, codpie
	FROM ventas NATURAL JOIN (
		SELECT codpie
		FROM pieza
		WHERE color='Rojo')) v2
	WHERE v1.codpro=v2.codpro and v1.codpie!=v2.codpie);

