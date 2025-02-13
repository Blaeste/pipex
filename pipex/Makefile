#Nom du programme
NAME	= pipex

# Repertoires sous-parties
DIR_LIBFT = libft

# Obj des sous parties
OBJ_LIBFT = $(DIR_LIBFT)/libft.a

# Sources et obj main Makefile
SRCS	= src/pipex.c src/pipex_utils.c
OBJS	= ${SRCS:.c=.o}

# Compilation
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -Iinc -fsanitize=address -fsanitize=leak -g3

# Regle principale
all:		${OBJ_LIBFT} ${NAME}

.c.o:
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${OBJ_LIBFT}
			@${CC} ${FLAGS} ${OBJS} ${OBJ_LIBFT} -o ${NAME}
			@echo "\n✅ Compilation terminée pour : ${NAME} !\n"

${OBJ_LIBFT}:
			@${MAKE} -C ${DIR_LIBFT} --no-print-directory
			@echo "\n✅ Compilation terminée pour libft !"

clean:
			@rm -f ${OBJS}
			@${MAKE} -C ${DIR_LIBFT} clean --no-print-directory
			@echo "✅ (clean) Suppression des fichiers .o !"

fclean:		clean
			@rm -f ${NAME}
			@${MAKE} -C ${DIR_LIBFT} fclean --no-print-directory
			@echo "✅ (fclean) Suppression de l'Archive !"

re:			fclean all

.PHONY:		all clean fclean re