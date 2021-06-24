#!/bin/bash
#Órdenes para el sistema de colas:
#1. Asigna al trabajo un nombre
#SBATCH --job-name=SumaVectoresC
#2. Asignar el trabajo a una cola (partición) 
#SBATCH --partition=ac 
#2. Asignar el trabajo a un account 
#SBATCH --account=ac

#Obtener información de las variables del entorno del sistema de colas:
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo:$SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"

#CONSTRUCCION DE NOMBRES DE ARCHIVO EJECUTABLES
TARGET="SumaVectoresC"
OMP_PARALLEL="PARALLEL_"
OMP_FOR="FOR_"
OMP_SECTIONS="SECTIONS_"
SECUENCIAL="SECUENCIAL_"

FILENO1=$OMP_PARALLEL$OMP_FOR$TARGET
FILENO2=$OMP_PARALLEL$OMP_SECTIONS$TARGET
FILENO3=$SECUENCIAL$TARGET

DIRECTORY="bin"

#DEFINICION DE LOS TIEMPOS MIN Y MAX
MIN=16384
MAX=67108864

#EJECUCION DE SCRIPT: TIEMPOS FOR
echo -e ">>> EJECUCION DE PROGRAMA CON OMP PARALLEL [FOR] <<<"
for((N=$MIN; N<=$MAX; N=N*2))
do
	srun ./$FILENO1 $N
done

#EJECUCION DE SCRIPT: TIEMPOS SECTIONS
echo -e "\n\n>>> EJECUCION DE PROGRAMA CON OMP PARALLEL [SECTIONS] <<<"
for((N=$MIN; N<=$MAX; N=N*2))
do
	srun ./$FILENO2 $N
done
