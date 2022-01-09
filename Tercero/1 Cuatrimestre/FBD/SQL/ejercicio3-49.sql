SELECT codpro, AVG(cantidad)
FROM ventas
WHERE codpro IN (
	SELECT codpro
	FROM ventas
	WHERE codpie='P3')
GROUP BY codpro;
