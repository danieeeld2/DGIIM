SELECT codpro, COUNT(*)
FROM ventas
GROUP BY codpro
HAVING COUNT(*) > 3;
