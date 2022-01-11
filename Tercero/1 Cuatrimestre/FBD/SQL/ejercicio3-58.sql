UPDATE proveedor
SET status=1
WHERE codpro IN (
	SELECT codpro
	FROM proveedor p
	WHERE NOT EXISTS (
		(SELECT codpie FROM ventas v1 WHERE v1.codpro=p.codpro) 
		MINUS
		(SELECT codpie FROM ventas v2 WHERE v2.codpie='P1')));
