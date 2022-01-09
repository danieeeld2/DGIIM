SELECT codpie
FROM pieza
WHERE peso > ALL
	(SELECT peso FROM pieza WHERE nompie LIKE 'Tornillo%');
