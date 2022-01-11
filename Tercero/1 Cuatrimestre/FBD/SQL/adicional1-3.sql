SELECT codpj, AVG(cantidad)
FROM ventas
WHERE TO_NUMBER(TO_CHAR(fecha,'YYYY'))=2000
GROUP BY codpj
HAVING AVG(cantidad)>=150;
