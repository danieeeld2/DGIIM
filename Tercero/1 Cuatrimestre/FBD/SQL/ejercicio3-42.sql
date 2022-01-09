SELECT codpro, SUM(cantidad)
FROM ventas
GROUP BY codpro
HAVING SUM(cantidad) > (SELECT SUM(v2.cantidad)
			FROM ventas v2
			WHERE v2.codpro='S3'
			GROUP BY v2.codpro);

