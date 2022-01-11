SELECT codpro
FROM ventas
WHERE codpj IN (
	SELECT codpj
	FROM proyecto
	WHERE ciudad LIKE '%ondres')
AND
	TO_CHAR(fecha,'MM-YYYY')='01-2000'
GROUP BY codpro
HAVING COUNT(*)=(
	SELECT MAX(COUNT(*))
	FROM ventas
	WHERE codpj IN ( 
        	SELECT codpj                                                                   
           	FROM proyecto                                                                     
		WHERE ciudad LIKE '%ondres')    
   	AND
        	TO_CHAR(fecha,'MM-YYYY')='01-2000'
  	GROUP BY codpro);

