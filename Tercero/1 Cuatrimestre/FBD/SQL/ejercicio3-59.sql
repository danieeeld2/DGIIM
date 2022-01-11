SELECT codpie, ciudad
FROM pieza p
WHERE NOT EXISTS (
	SELECT *
	FROM ventas
	WHERE (fecha BETWEEN 
		TO_DATE('01/09/2020','DD/MM/YYYY') AND TO_DATE('30/09/2020','DD/MM/YYYY'))
	AND ventas.codpie=p.codpie)
ORDER BY (
	SELECT SUM(cantidad)
	FROM ventas v2
	GROUP BY codpie
	WHERE v2.codpie=p.codpie) DESC;

