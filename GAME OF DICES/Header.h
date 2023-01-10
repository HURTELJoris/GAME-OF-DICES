#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
typedef struct {
	char nom[20];
	int score;
} Joueur;

void affichageScore(Joueur j);
void annonce();
int menu(int choix);
int rejouer();
void afficherRegles();
int nbJoueurs();
void saisieNomsJoueurs(Joueur* j, int nbj);
void lancementDesDes(int* tirage);
int calculPoints(Joueur* j, int* t);
void jeu();
