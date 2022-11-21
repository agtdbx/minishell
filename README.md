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
