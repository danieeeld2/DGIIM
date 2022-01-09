SELECT codpro, ROUND(AVG(cantidad),4), TO_CHAR(fecha,'YYYY')
FROM ventas
GROUP BY codpro, TO_CHAR(fecha,'YYYY')
ORDER BY codpro DESC;
