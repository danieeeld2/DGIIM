SELECT DISTINCT codpj
FROM proyecto
WHERE codpj NOT IN (
	SELECT codpj
	FROM ventas, proveedor, pieza
	WHERE ventas.codpro = proveedor.codpro AND pieza.codpie = ventas.codpie
	AND proveedor.ciudad = 'Londres' AND pieza.color = 'Rojo');


