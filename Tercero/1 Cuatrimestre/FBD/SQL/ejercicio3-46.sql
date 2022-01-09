SELECT codpro
FROM proveedor p
WHERE NOT EXISTS (
	(SELECT DISTINCT codpie FROM ventas WHERE codpro='S1')
	MINUS
	(SELECT DISTINCT codpie FROM ventas v WHERE v.codpro=p.codpro));
