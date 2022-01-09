SELECT codpj
FROM proyecto
WHERE proyecto.ciudad IN (
	SELECT DISTINCT ciudad FROM pieza);
