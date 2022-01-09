SELECT codpie 
FROM ventas
WHERE codpro IN (
	SELECT codpro FROM proveedor WHERE ciudad='Madrid');
