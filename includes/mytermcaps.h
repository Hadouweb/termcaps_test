#ifndef TERMCAPS_H
# define TERMCAPS_H

#include "libft.h"
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>

/* efface l'ecran */
#define TERM_CLEAR printf ("%c[H%c[J",27,27)

/* efface la ligne ou se trouve le curseur */
#define TERM_CLEAR_LINE printf ("%c[J",27)

/* place le curseur en haut a gauche */
#define TERM_CURSOR_HOME printf ("%c[H",27)

/* place le curseur a la position x,y (en ht/gche = 1,1)*/
#define TERM_CURSOR_GOTO(x,y) printf ("%c[%d;%dH",27,(y),(x))

/* sauve la position du curseur */
#define TERM_CURSOR_SAVE printf ("%c7",27)

/* positionne le curseur a la dernière position sauvée */
#define TERM_CURSOR_RESTORE printf ("%c8",27)

/* monte le curseur d'une ligne */
#define TERM_CURSOR_UP printf ("%cA",27)

/* passe en vidéo inverse */
#define TERM_FONT_REVERSE printf("%c[5m",27)

/* passe en bold ou surbrillance suivant le terminal */
#define TERM_FONT_BOLD printf("%c[1m",27)

/* annule l'effet de BOLD ou REVERSE */
#define TERM_FONT_NORMAL printf("%c[m",27)

#endif