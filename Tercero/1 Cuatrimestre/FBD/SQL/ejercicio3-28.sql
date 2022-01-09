SELECT codpie
FROM pieza
WHERE peso IN (SELECT MAX(DISTINCT peso) FROM pieza);
