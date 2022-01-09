SELECT codpro
FROM proveedor
WHERE 3<=(SELECT COUNT(*) FROM ventas WHERE ventas.codpro=proveedor.codpro);
