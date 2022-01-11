SELECT codpro
FROM ventas
GROUP BY codpro,codpie,codpj
HAVING COUNT(*)>=3;
