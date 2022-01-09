SELECT DISTINCT codpie
FROM ventas
WHERE ventas.codpj IN (
	SELECT codpj
	FROM proyecto
	WHERE proyecto.ciudad = 'Londres');
