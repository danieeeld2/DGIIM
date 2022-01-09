SELECT v.codpro, p.nompro, SUM(v.cantidad)
FROM ventas v, proveedor p
WHERE (v.codpro=p.codpro)
GROUP BY v.codpro, p.nompro
HAVING SUM(v.cantidad)>=1000;
