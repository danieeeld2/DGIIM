SELECT codpro, SUM(cantidad)
FROM ventas
WHERE codpie='P1' AND 
	TO_NUMBER(TO_CHAR(fecha,'YYYY'))=2021
GROUP BY codpro
HAVING SUM(cantidad) = (SELECT MAX(SUM(v1.cantidad))
			FROM ventas v1
			WHERE codpie='P1' AND
				TO_NUMBER(TO_CHAR(fecha,'YYYY'))=2021
			GROUP BY v1.codpro);
