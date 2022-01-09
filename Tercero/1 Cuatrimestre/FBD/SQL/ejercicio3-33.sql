SELECT codpie, codpj, SUM(cantidad)
FROM ventas
GROUP BY codpie, codpj
ORDER BY codpj DESC;
