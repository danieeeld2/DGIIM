SELECT codpro
FROM proveedor p
WHERE NOT EXISTS (
	(SELECT DISTINCT codpie FROM ventas WHERE codpro='S3')
	MINUS
	(SELECT DISTINCT codpie FROM ventas v WHERE v.codpro=p.codpro)) 
AND codpro!='S3';
