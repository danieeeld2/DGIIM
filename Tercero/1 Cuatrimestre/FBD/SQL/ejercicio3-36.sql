SELECT v.codpie, p.nompie, SUM(v.cantidad)
FROM ventas v, pieza p
WHERE (v.codpie=p.codpie)
GROUP BY v.codpie, p.nompie
HAVING SUM(v.cantidad) = 	(SELECT MAX(SUM(v2.cantidad))
				FROM ventas v2
				GROUP BY v2.codpie);

