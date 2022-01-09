SELECT DISTINCT codpj
FROM proyecto p
WHERE NOT EXISTS (
	(SELECT DISTINCT codpro FROM ventas)
	MINUS
	(SELECT DISTINCT codpro FROM ventas v2 WHERE codpie='P3' AND v2.codpj=p.codpj));
