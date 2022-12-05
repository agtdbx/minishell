1 MINISHELL

Mode intéractif
CTRL C -> SIG_INT
	(New line)

CTRL D -> EOF
	(Quitte shell si ligne vide en printant "exit")

CTRL \ -> SIG_QUIT
	(Ne fais rien)


readline("> ")
	retourne ce que tu écris, sans le \n pour entrer


REDIRECTION :(

echo test >1 > 2 >3
	-> créer tous les fichiers mais met le résultat seulement dans 3

<4 < 5 grep test
	-> re lis que le fichier 5

<1 <2 <3 > 5 grep test
	-> grep le fichier 3 et met le résultat dans 5

<4 > 5 grep test | wc -l
	-> met le résultat dans 5 et met rien dans l'entrée standard mais la commande ne bloque pas

ECHO
echo -n VALUE
echo -nnnnnnnnnnnnnnnnnnnnnnnnn VALUE
echo -nnnnnnnnnnnnnnnnnnnnnnnnn -n -n -n -n VALUE
echo -nnnnnnnnnnn -n -n -n -n VALUE -n
	-> print(VALUE -n)


PWD
emplacement : minishell
cd srcs

emplacement : minishell/srcs
echo $PWD
	-> minishell/srcs
echo $OLDPWD
	-> minishell



$?

echo $?
	-> renvois un int dépendant du dernier truc fait
A stocker dans les variables d'environements

quand on fait cat + CTRL C
	-> $? = 130

quand on fait cat + CTRL \
	-> $? = 131

quand on fait cat + CTRL D
	-> $? = 0

quand on fait command invalide
	-> $? = 127



EXIT

exit nb
	nb entre 0 et 255. Overflow si plus mais marche quand même

exit
	-> on quitte le programme et on met $? à 0

exit 55
	-> on quitte le programme et on met $? à 55

exit 55 54 323
	bash: exit: too many arguments
	-> on quitte pas le programme et on met $? à 130

exit p
	bash: exit: p: numeric argument required
	-> on quitte le programme et on met $? à 2

exit p 152 452
	bash: exit: p: numeric argument required
	-> on quitte le programme et on met $? à 2

exit 55 p 323
	bash: exit: too many arguments
	-> on quitte pas le programme et on met $? à 130



cat en mode bloquant
CTRL + D -> quitte sans \n
CTRL + C -> quitte avec ^C\n
CTRL + \ -> quitte avec ^\Quit (core dumped)\n


cat | ls
	-> affiche le résultat de ls et nous permet d'écrire 1 line (cat ne marche pas)

cat | cat | cat | cat | ls
	-> affiche le résultat de ls et nous permet d'écrire 4 lines (cat ne marche pas)



EXPORT

export a =6_b
	-> bash: export: `=6_b': not a valid identifier

export a= 6_b
	-> bash: export: `6_b': not a valid identifier

export 6_a=b
	-> bash: export: `6_a=b': not a valid identifier
(Le nom de la variable ne peut pas commencer par un chiffre)
(Le nom de la variable ne peut pas conteinir de !@#$%^&*()-+= )
	mais on peut var VAR+=VALUE

export a=$a
	-> $a ne contient rien, par protection


penser a faire une big commande du genre
/tmp/../bin/ls


/*
Variables
TEST=coucou

echo $TEST					-> coucou
echo '$TEST'				-> $TEST
echo "$TEST"				-> coucou
echo '"$TEST"'				-> "$TEST"
echo "'$TEST'"				-> 'coucou'
echo "test $TEST test"		-> test coucou test
echo 'test $TEST test'		-> test $TEST test
echo "'test $TEST test'"	-> 'test coucou test'
echo '"test $TEST test"'	-> "test $TEST test"
echo "$TEST t $TEST" 		-> coucou t coucou
echo $TEST$TEST				-> coucoucoucou
echo "test"'test'test"test"	-> testtesttesttest
*/
