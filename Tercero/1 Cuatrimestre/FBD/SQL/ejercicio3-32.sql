SELECT codpro, codpie, AVG(cantidad)
FROM ventas
WHERE codpie='P1'
GROUP BY codpro,codpie;
