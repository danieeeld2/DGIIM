SELECT codpie
FROM ventas v1
WHERE TO_CHAR(fecha,'MM-YYYY')='03-2018' AND NOT EXISTS (
	SELECT codpie
	FROM ventas v2
	WHERE v1.codpie=v2.codpie AND v2.fecha>=TO_DATE('04-2010','MM-YYYY'));

