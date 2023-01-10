#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#define BUT_DU_JEU 10000


void annonce() {
	printf("#################################\n\n");
	printf("          GAME OF DICES \n\n");
	printf("#################################\n\n");
	printf("Cree par : Lepretre Alexandre et Hurtel Joris\n\n");
}
int menu(int choix)
{
	printf("------------- MENU ------------- \n");
	printf("1 - Jouer\n");
	printf("2 - Regles\n");
	printf("3 - Quitter\n");



	do
	{
		printf("\nChoix : ");
		scanf("%d", &choix);
		if (choix < 1 || choix > 3) {
			printf("\nVeuillez entrer un nombre valide, entre 1 et 3 : ");
		}
	} while (choix < 1 || choix > 3);

	return choix;
}
int rejouer()
{
	int choix;
	do
	{
		printf("\nVoulez-vous jouer ? Tapez 1 pour 'oui' et 2 pour 'non' ? : ");
		scanf("%d", &choix);
		printf("\n");

		if (choix < 1 || choix > 2)
		{
			printf("Erreur de saisie, veuillez reessayer!\n\n");
		}

	} while (choix < 1 || choix > 2);

	return choix;
}
void afficherRegles()
{
	printf("\n\n#################################\n");
	printf("            REGLES :\n");
	printf("#################################\n\n");
	printf("Le jeu ce joue entre 2 et 6 joueurs.\n\n");
	printf("Vous devez :\n\n");
	printf(" - Juste appuyer sur la touche '*'.\n\n");

	printf("Calcul des points :\n\n");
	printf(" - Si vous avez un des avec la valeur 1, il vous raporte 100 points.\n");
	printf(" - Si vous avez un des avec la valeur 5, il vous raporte 50 points.\n");
	printf(" - Si vous avez trois des identiques, ils vous raportent 100 fois la valeur du des.\n");
	printf(" - Si vous avez trois des de 1, ils vous raportent 1000 points.\n");
	printf(" - Si vous avez six des identiques, ils vous raportent 1000 fois la valeur du des.\n");
	printf(" - Si vous avez six des de 1, ALLEZ JOUER AU LOTO CAR VOUS VENEZ DE GAGNER LA PARTIE !\n\n");
	printf("Si vous n\'avez pas cette chance, le premier qui arrive a 10000 points gagne la partie.\n");
	printf("Sauf si deux joueurs atteignent ce score. Dans ce cas, celui des deux avec le plus de points gagne !\n\n");
	printf(" - DUREE D\'UNE PARTIE: De 1 a 5 minutes.\n");
	printf(" - ...\n");
	printf(" - Amusez-vous bien !!!\n");
	printf("\n\n");
}
void affichageScore(Joueur j) {
	printf("== Nouveau score de %s : %d ==\n\n", j.nom, j.score);
	printf("#################################\n\n");
}
int nbJoueurs() {
	int nbjoueurs;
	printf("\n\n\n#################################\n\n");
	printf("              JEU :\n\n");
	printf("#################################\n\n");
	printf("\n\nCombien souhaitez vous de joueurs (entre 2 et 6) ? : ");
	do {
		scanf("%d", &nbjoueurs);
		if (nbjoueurs < 2 || nbjoueurs > 6)
		{
			printf("\nVeuillez entrer un nombre de joueurs valide, entre 2 et 6 !: ");
		}
	} while (nbjoueurs < 2 || nbjoueurs > 6);  //tant que le nombre de joueurs impose n'est pas respecte

	return nbjoueurs;
}
//int nbot = 0;
void saisieNomsJoueurs(Joueur* j, int nbj) {
	for (int i = 0; i < nbj; i++) {
		printf("\nNom pour le joueur %d: ", i + 1);
		scanf("%s", j[i].nom);
		//sprintf(j[i].nom, "%d", nbot);
		//nbot++;
		j[i].score = 0;
	}
}
void lancementDesDes(int* tirage) {  //

	printf("\nLancez vos des avec la touche * : ");
	char text;
	int i = 1;

	do
	{

		text = _getch();

		if (text == '*')
		{
			break;
		}

		else if (text != '*')
		{
			printf("\n\n\nErreur de saisie !\n");
			printf("Vous n\'avez pas appuye sur la bonne touche (*)!\n");
			printf("Veuillez reessayer : ");
		}


	} while (i != 0);

	for (int i = 0; i < 6; i++) {
		tirage[i] = rand() % 6 + 1;
	}

}
int calculPoints(Joueur* j, int* t) {
	int comptes[6];

	for (int i = 0; i < 6; i++) { //on initialise le tableau
		comptes[i] = 0;
	}

	for (int i = 0; i < 6; i++) { //compte les repetitions pour chaque chiffre
		if (t[i] == 1) {
			comptes[0]++;
		}
		else if (t[i] == 2) {
			comptes[1]++;
		}
		else if (t[i] == 3) {
			comptes[2]++;
		}
		else if (t[i] == 4) {
			comptes[3]++;
		}
		else if (t[i] == 5) {
			comptes[4]++;
		}
		else if (t[i] == 6) {
			comptes[5]++;
		}
	}

	//comptes[0] = 6;

	int points = 0;
	for (int i = 0; i < 6; i++) { //pour chaque chiffre
		if (comptes[i] == 6) {    //si ce chiffre a ete compte six fois

			if (i == 0) { //si ce chiffre est 1 (six fois 1)
				return 1; //on applique le bareme "1+1+1+1+1+1" => le joueur gagne
			}
			else {   //si c'est un autre chiffre (six fois le chiffre (i+1))
				points += 1000 * (i + 1); //on applique le bareme "6 des identiques"
			}

		}
		else if (comptes[i] >= 3) {    //si ce chiffre a ete compte trois, quatre ou cinq fois

			if (i == 0) { //si ce chiffre est 1 (trois, quatre ou cinq fois 1)
				points += 1000; //on applique le bareme "1+1+1"
				points += (100 * (comptes[i] - 3)); //on applique le bareme "1" aux des restants
			}
			else if (i == 4) {    //si ce chiffre est 5 (trois, quatre ou cinq fois 5)
				points += 100 * (i + 1); //on applique le bareme "3 des identiques"
				points += (50 * (comptes[i] - 3));  //on applique le bareme "5" aux des restants
			}
			else {   //si c'est un autre chiffre (trois, quatre ou cinq fois (i+1))
				points += 100 * (i + 1); //on applique le bareme "3 des identiques"
			}

		}
		else {   //si ce chiffre a ete compte moins de trois fois (c'est-a-dire zero, un ou deux fois)

			if (i == 0) { //si ce chiffre est 1 (zero, un ou deux fois 1)
				points += (100 * (comptes[i])); //on applique le bareme "1"
			}
			else if (i == 4) {    //si ce chiffre est 5 (zero, un ou deux fois 5)
				points += (50 * (comptes[i]));  //on applique le bareme "5"
			}

		}

	}

	if (points == 0) {    //si aucune combinaison du bareme n'a ete trouvee dans le tirage

		points -= 1000; //on affiche -1000 comme resultat du tirage sur l'interface de jeu
		if (j->score >= 1000) {    //si le joueur a un score de plus de 1000 points
			j->score += points;  //on retire mille points au joueur
		}
		else if (j->score > 0) {   //si le joueur a un score de moins de 1000 points mais au moins 1 point
			j->score -= j->score; //on retire tous les points du joueur
		}

	}
	else {
		j->score += points;  //on comptabilise les points de ce tirage au score du joueur
	}

	printf("Total des points du tirage: %d\n\n", points);

	if (j->score >= BUT_DU_JEU) {  //si le joueur a 10000 points ou plus
		return 1;   //il remporte la partie
	}

	return 0;   //sinon on continue le jeu
}
void jeu() {

	annonce();

	int quit = 0;
	while (quit == 0)
	{
		int tempchoixmenu = 0;
		int choixmenu = menu(tempchoixmenu);


		if (choixmenu == 1)
		{
			int tirage[6];

			Joueur* j;

			int nb_joueurs = nbJoueurs();
			if (nb_joueurs == 2) {
				Joueur j[2];
			}
			else if (nb_joueurs == 3) {
				Joueur j[3];
			}
			else if (nb_joueurs == 4) {
				Joueur j[4];
			}
			else if (nb_joueurs == 5) {
				Joueur j[5];
			}
			else if (nb_joueurs == 6) {
				Joueur j[6];
			}
			j = (Joueur*)malloc(6 * sizeof(Joueur));
			saisieNomsJoueurs(j, nb_joueurs);


			Joueur gagnant;
			gagnant.score = 0;


			int replaySame = 0;
			int partie_en_cours = 1;
			int numero_round = 1;


			do
			{
				printf("\n\n\n## NOUVELLE PARTIE ##\n\n\n");
				while (partie_en_cours) {
					printf("## ROUND n%d ##\n\n\n", numero_round);
					for (int i = 0; i < nb_joueurs; i++) {   //un round (un tour par personne)
						printf("<< Au tour de %s: >>\n", j[i].nom);
						lancementDesDes(tirage);
						printf("\n\n\n#################################");
						printf("\n\nJeu obtenu : [%d, %d, %d, %d, %d, %d]\n\n", tirage[0], tirage[1], tirage[2], tirage[3], tirage[4], tirage[5]);

						if (calculPoints(&j[i], tirage)) {    //on calcule les points du joueur actuel selon son tirage de des
							//si calculPoints detecte un gagnant
							partie_en_cours = 0;
							if (j[i].score > gagnant.score) { //si le gagnant a un score plus eleve que le precedent gagnant, il prend sa place sur le trone du gagnant ultime
								strcpy_s(gagnant.nom, j[i].nom);
								gagnant.score = j[i].score;
							}
						}
						affichageScore(j[i]);

						//getchar();  //on attend un appui sur entree
					}
					if (partie_en_cours) {    //s'il n'y a pas de gagnant dans ce round, on passe au round suivant
						printf("## FIN DU ROUND n%d ##\n", numero_round);
						//printf("Appuyez sur entree pour continuer...\n\n");
						//getchar();  //on attend un appui sur entree
						numero_round++;
					}
					else {   //si la partie
						printf("## Victoire de %s !! ##\n## Au bout de %d rounds ##\n## Avec un total de %d ##\n\n", gagnant.nom, numero_round, gagnant.score);
						replaySame = rejouer();
					}
				}

				if (replaySame == 2)
				{
					quit = 1;
					break;
				}


			} while (replaySame == 2);
		}



		else if (choixmenu == 2)
		{
			afficherRegles();
		}


		else if (choixmenu == 3)
		{
			quit = 1;
		}
	}
}