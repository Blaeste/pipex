NAME	= libftprintf.a

SRCS	= #ft_printf.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

FLAGS	= -Wall -Werror -Wextra

LIB		= ranlib

# Variables progress bar

total_files := $(words ${SRCS})
GREEN = \033[0;32m
NC = \033[0m

# Fonction progress bar

define progress_bar
	$(eval current_file := $(shell echo $$(ls -1 *.o 2>/dev/null | wc -l || echo 0)))
	$(eval percent := $(shell echo $$((100 * $(current_file) / $(total_files)))))
	$(eval progress := $(shell echo $$(($(percent) / 2))))

	@printf "\r[${GREEN}"
	@for i in $$(seq 1 $(progress)); do printf "#"; done
	@if [ $(progress) -lt 50 ]; then \
		for i in $$(seq $(progress) 50); do printf "."; done \
	fi
	@printf "${NC}] [$(percent)%%] Compiling: $(current_file)/$(total_files) 🛠️"
endef

all:		${NAME}

.c.o:
			${progress_bar}
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@ar rc ${NAME} ${OBJS}
			@${LIB} ${NAME}
			${progress_bar}
			@echo "\n✅ Compilation terminee !"

clean:
			@rm -f ${OBJS}
			@echo "✅ (clean) Suppression des fichiers .o !"

fclean:		clean
			@rm -f ${NAME}
			@echo "✅ (fclean) Suppression de l'Archive !"

re:			fclean all

.PHONY:		all clean fclean re