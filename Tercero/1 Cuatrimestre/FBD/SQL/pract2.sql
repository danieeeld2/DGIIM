INSERT INTO proveedor VALUES ('S1','Jose Fernandez',2,'Madrid');
INSERT INTO proveedor VALUES ('S2','Manuel Vidal',1,'Londres');
INSERT INTO proveedor VALUES ('S3','Luisa Gomez',3,'Lisboa');
INSERT INTO proveedor VALUES ('S4','Pedro Sanchez',4,'Paris');
INSERT INTO proveedor VALUES ('S5','Maria Reyes',5,'Roma');

SELECT * FROM proveedor;

INSERT INTO pieza VALUES ('P1','Tuerca','Gris',2.5,'Madrid');
INSERT INTO pieza VALUES ('P2','Tornillo','Rojo',1.25,'Paris');
INSERT INTO pieza VALUES ('P3','Arandela','Blanco',3,'Londres');
INSERT INTO pieza VALUES ('P4','Clavo','Gris',5.5,'Lisboa');
INSERT INTO pieza VALUES ('P5','Alcayata','Blanco',10,'Roma');

SELECT * FROM pieza;

INSERT INTO proyecto VALUES ('J1','Proyecto 1','Londres');
INSERT INTO proyecto VALUES ('J2','Proyecto 2','Londres');
INSERT INTO proyecto VALUES ('J3','Proyecto 3','Paris');
INSERT INTO proyecto VALUES ('J4','Proyecto 4','Roma');

SELECT * FROM proyecto;

INSERT INTO ventas SELECT * FROM opc.ventas;

SELECT * FROM ventas;
