SELECT codpie
FROM ventas
WHERE TO_CHAR(fecha,'YYYY')='2021'
GROUP BY codpie
HAVING COUNT(*)=1;
