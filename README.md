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
	nb entre 0 et 255. Overflow si plus ou moins mais marche quand même

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

nb entre -9223372036854775807 et 9223372036854775807 compris
	sinon c'est du text



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


/*
|
-> bash: syntax error near unexpected token `|'

$tkt
-> bash: syntax error near unexpected token `|'

$tkt | $tkt
-> rien

$tkt |
-> attend un truc, donc erreur pour nous
*/


=================================================================
								FAIT
=================================================================

$1lol
	-> interprete $1 et print juste lol

$9lol
	-> interprete $9 et print juste lol

$10lol
	-> interprete $1 et print juste 0lol

echo $$lol
	-> doit echo juste lol

lol | |
	-> check de command alors aue erreur pipe prioritaire + leak

>|
	-> 2 messages d'erreur, $? != 2

<lol | |
	-> 2 messages d'erreurs, $? != 2

<lol
	-> leak + $? != 1

>>>
	-> pas de syntax error

><
	-> pas de syntax error

<>
	-> pas de syntax error

echo -n test
	-> marche pas

echo -nnnnnnnnnnnn -n -n test
	-> marche pas

pwd -l
	-> renvois pas erreur option + $? != 2

env -l
	-> leak + renvois pas erreur option + $? != 125

env coucou
	-> renvois pas erreur argument + $? != 127

"" ls
	-> leak

""ec""oui""ho"" lol
	-> leak

"coucou" ls
	-> leak

export -lol
	-> ne revois pas invalid option + $? != 2

export oui
	-> ne revois pas invalid identifier + $? != 1

export COUCOU | ls
	-> COUCOU n'existe pas

export tkt+=oui
	-> leak

export | grep
	-> marche pas + leak

export +=tkt
	-> ne dois pas marcher + leak

export lol-=tkt
	-> ne renvois pas invalid identifier + leak

export name=value
	-> name ne peux pas commencer par 0123456789, ne dois pas contenir `~!@#$%^&*()-[]{};:,./?

<lol | <lol
	-> leak + $? != 0

echo lol | lol | lol
	-> leak

cat | ls
	->	une seule ligne de cat

wc | ls
grep | ls
	->	plus ligne catch mais marche pas

faire 2 boules d'executions
	-> 1 pour lancer les fork
	-> 2 pour faire les waitpid

cat | ls
>^C
	-> $? != 0

export COUCOU | ls
	-> COUCOU n'existe pas

cd
	-> leak + marche pas car pas a faire dans un fork

cd | ls
	->	ne dois pas marcher car pipe et donc il est dans un fork

unset name
	-> name ne peux pas commencer par 0123456789, ne dois pas contenir `~!@#$%^&*()-[]{};:,./?

mkdir lol
./lol
	-> leak + fork non quitter car execve retourne -1 + $? != 126

export lol="echo <lol"
$lol
	-> print pas <lol

exit 1 2
	-> $? != 1

haha
	-> $? != 127

env -l | <mdr
	-> $? != 0

Split pas les espaces entre ""

''
	-> y'a pas command not found

""
	-> y'a pas command not found

" "
	-> cmd not found + $? != 127

export lol="echo lol"
"$lol"
	-> 'echo lol' cmd not found + $? != 127

=================================================================
								EN COURS
=================================================================
AUGUSTE

NICOLAS

Bon courage

=================================================================
								A FAIRE
=================================================================

<<'<lol'
	-> limiter <lol

mkdir haha
./haha
	-> $? != 1

mkdir haha
chmod 000 haha
cd haha
	-> pas le bon message d'erreur + $? != 2 + leak

pwd lol
	-> pwd doit s'executer

env lol
	-> $? != 2

export lol=haha -lol
	-> mauvais message : invalid identifier $? != 1

export lol++=coucou
	-> invalid identifier + $? != 1

export lol
export lol+=coucou
	-> segfault

env | ls
	-> pipe error a enlever (Pas obliger)

unset 3 haha 3
	-> 2 messages + haha unset

<<""
	-> doit quitter au \n

ls | haha | ls
	-> segfault

haha | ls | haha
	-> $? != 127
