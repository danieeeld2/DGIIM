SELECT codpj
FROM ventas 
WHERE codpro IN (
	SELECT DISTINCT codpro
	FROM proveedor
	WHERE ciudad LIKE '%ondres')
GROUP BY codpro,codpj
HAVING COUNT(*)=3;
