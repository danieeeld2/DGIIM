SELECT codpie, nompie, media
FROM pieza NATURAL JOIN (SELECT codpie, AVG(cantidad) as media
		FROM ventas
		GROUP BY codpie);
