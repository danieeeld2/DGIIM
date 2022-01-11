SELECT codpie
FROM ventas
WHERE codpie IN (
	SELECT codpie
	FROM pieza
	WHERE color LIKE '%ojo')
GROUP BY TO_CHAR(fecha,'YYYY'), codpie
HAVING COUNT(*)>=2;
