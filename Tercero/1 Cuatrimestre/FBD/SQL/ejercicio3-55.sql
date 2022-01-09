SELECT DISTINCT codpro
FROM ventas v1
WHERE NOT EXISTS (
	(SELECT DISTINCT codpie FROM ventas v2 WHERE v1.codpro=v2.codpro)
	MINUS
	(SELECT DISTINCT codpie FROM pieza WHERE color LIKE '%ojo'));
