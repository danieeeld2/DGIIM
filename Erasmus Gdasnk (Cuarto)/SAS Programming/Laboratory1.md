# 1. Intro to Statistical Analytics System

###### Daniel Alconchel Vázquez

---

**Exercise 1.** Find library SASHELP and table CARS. Check what is the engine size of A6 3.0 Quattro 4dr.

<img src="./.resources/4.png" title="" alt="4.png" width="672">

**Exercise 2.** Create library mylib assigned to the folder soulutions (create it if it does not exist).

![2.png](./.resources/2.png)

<img src="file:///home/daniel/Git/DGIIM/Erasmus%20Gdasnk%20(Cuarto)/SAS%20Programming/.resources/3.png" title="" alt="3.png" data-align="center">

**Exercise 3.** Check attributes of the variable MODEL from SASHELP.CARS.

The type is *alfanum*.

![1.png](./.resources/1.png)

**Exercise 4.** Read table sashelp.cars and create new table CarsVat, which contains variables from sashelp.cars and new variable InvoiceBrutto=1.23*Invoice.

```sas
data mylib.CarsVat;
set sashelp.cars;
InvoiceBrutto=1.23*Invoice;
run;
```

![5.png](./.resources/5.png)

**Exercise 5.** In mylib library create table PEOPLE with variables NAME,  HEIGHT and WEIGHT. Add some example datalines. Then create data set  BMITABLE, which contains variables from table PEOPLE and new variable  BMI (bmi = weight/((height/100) ∗ ∗2);). PUT in log:

- all variables and all observations (PDV vectors) from table BMITABLE.

- variables NAME and BMI

```sas
DATA mylib.PEOPLE;
	INPUT Name$ Height Weight;
	DATALINES;
	Daniel 184 92
	Laura 165 52
	Marta 157 47
run;
```

![6.png](./.resources/6.png)

![7.png](./.resources/7.png)

```sas
data mylib.BMITABLE;
set mylib.people;
bmi=(weight/(height/100)**2);
run;
```

![8.png](./.resources/8.png)

![9.png](./.resources/9.png)


