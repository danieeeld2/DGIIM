SELECT DISTINCT codpro
FROM ventas v1
WHERE NOT EXISTS (
	(SELECT DISTINCT codpie FROM pieza WHERE color LIKE '%ojo')
	MINUS
	(SELECT DISTINCT codpie FROM ventas v2 WHERE v2.codpro=v1.codpro));
