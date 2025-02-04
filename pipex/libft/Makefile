NAME	= libft.a

SRCS	= ${FD} ${IS} ${TO} ${STR} ${MEM} ${LIST} ${PRINTF}

FD		= fd/ft_putchar_fd.c fd/ft_putstr_fd.c fd/ft_putendl_fd.c fd/ft_putnbr_fd.c

IS		= is/ft_isalpha.c is/ft_isdigit.c is/ft_isalnum.c is/ft_isascii.c is/ft_isprint.c

TO		= to/ft_toupper.c to/ft_tolower.c to/ft_atoi.c to/ft_atol.c to/ft_itoa.c

STR		= str/ft_strlen.c str/ft_strlcpy.c str/ft_strlcat.c str/ft_strchr.c str/ft_strrchr.c \
		str/ft_strncmp.c str/ft_strnstr.c str/ft_strmapi.c str/ft_striteri.c str/ft_substr.c \
		str/ft_strjoin.c str/ft_strtrim.c str/ft_strdup.c str/ft_split.c

MEM		= mem/ft_memset.c mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memchr.c mem/ft_memcmp.c \
		mem/ft_bzero.c mem/ft_calloc.c

LIST	= list/ft_lstnew.c list/ft_lstadd_front.c list/ft_lstsize.c list/ft_lstlast.c \
		list/ft_lstadd_back.c list/ft_lstdelone.c list/ft_lstclear.c list/ft_lstiter.c \
		list/ft_lstmap.c

PRINTF	= printf/ft_printf.c printf/ft_putchar.c printf/ft_putnbr.c printf/ft_putnbru.c \
		printf/ft_putstr.c printf/ft_hex.c printf/ft_putptr.c

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
	$(eval current_file := $(shell find . -type f -name "*.o" | wc -l))
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

clean:
			@rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re