#Nom du programme
NAME	= pipex

# Repertoires sous-parties
DIR_LIBFT = libft

# Obj des sous parties
OBJ_LIBFT = $(DIR_LIBFT)/libft.a

# Sources et obj main Makefile
SRCS	= src/pipex.c src/pipex_utils.c src/pipex_stack.c
OBJS	= ${SRCS:.c=.o}

# Sources et obj bonus
SRCS_BONUS	= src/bonus/pipex_bonus.c src/bonus/pipex_utils_bonus.c src/bonus/pipex_stack_bonus.c
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

# Compilation
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -Iinc

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

bonus:		${OBJS_BONUS} ${OBJ_LIBFT}
			@${CC} ${FLAGS} ${OBJS_BONUS} ${OBJ_LIBFT} -o ${NAME}
			@echo "\n✅ Compilation terminée pour : ${NAME} avec bonus !\n"

clean:
			@rm -f ${OBJS} ${OBJS_BONUS}
			@${MAKE} -C ${DIR_LIBFT} clean --no-print-directory
			@echo "✅ (clean) Suppression des fichiers .o !"

fclean:		clean
			@rm -f ${NAME}
			@${MAKE} -C ${DIR_LIBFT} fclean --no-print-directory
			@echo "✅ (fclean) Suppression de l'Archive !"

re:			fclean all

.PHONY:		all clean fclean re