SELECT codpro, SUM(cantidad)
FROM ventas
GROUP BY codpro
ORDER BY SUM(cantidad) DESC;

