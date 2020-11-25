// JERARQUÍA DE PROCESOS TIPO 1
for (i=1; i<nprocs; i++) {
    if ((childpid=fork())==-1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
	}
	if (childpid)
		break;
}

// JERARQUÍA DE PROCESOS TIPO 2
for (i=1; i<nprocs; i++) {
	if ((childpid= fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
	}
	if (!childpid)
		break;
}