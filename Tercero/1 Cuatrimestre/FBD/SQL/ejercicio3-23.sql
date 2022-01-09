SELECT codpie
FROM pieza
WHERE peso IN
	(SELECT MAX(peso) FROM pieza);
