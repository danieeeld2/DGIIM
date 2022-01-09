SELECT DISTINCT codpro
FROM ventas 
WHERE codpie IN (
	SELECT DISTINCT codpie
	FROM pieza
	WHERE color LIKE '%ojo');
