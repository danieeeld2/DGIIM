(SELECT ciudad FROM proveedor WHERE status>2)
		INTERSECT
(SELECT ciudad FROM proveedor WHERE codpro!='P1');

SELECT codpj FROM ventas WHERE codpro='S1';

(SELECT DISTINCT ciudad FROM proveedor)
		UNION
(SELECT DISTINCT ciudad FROM proyecto)
		UNION
(SELECT DISTINCT ciudad FROM pieza);
