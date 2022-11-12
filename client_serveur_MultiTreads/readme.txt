pour compiler le serveur : gcc -pthread nom_executable serveur.c

puis executer avec ./nom_executable
exemple:

 gcc -pthread serveur serveur.c
 ./serveur
 --------------------   ---------

 pour le client:

 gcc -o nom_executable client.c
 puis executer  ./nom_executable avec

 exemple 
  gcc -o client client.c
  ./client