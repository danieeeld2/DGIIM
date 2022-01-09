SELECT AVG(cantidad), TO_CHAR(fecha,'MM')
FROM ventas
GROUP BY TO_CHAR(fecha,'MM')
ORDER BY TO_CHAR(fecha,'MM') ASC;
