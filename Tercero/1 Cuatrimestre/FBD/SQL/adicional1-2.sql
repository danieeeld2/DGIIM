SELECT codpie
FROM pieza p1
WHERE color LIKE '%lanco' AND (
	SELECT COUNT(*)
	FROM (
		SELECT codpro
		FROM ventas
		WHERE codpie=p1.codpie
		GROUP BY codpro))>=3;
