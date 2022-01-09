SELECT codpro   
FROM ventas
WHERE ventas.codpie IN (
	SELECT codpie
	FROM pieza p JOIN (SELECT * FROM proyecto) pj 
	ON (p.ciudad=pj.ciudad));
