NAME = philo

BLUE 	= \033[0;34m
GREEN 	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[38;5;209m
YELLOW	= \033[0;93m
BROWN 	= \033[38;2;184;143;29m
RESET 	= \033[0m

PHILO_SRCS		= main.c setup.c utils.c ft_atol.c actions.c simulation.c monitoring.c

HEADERS  = philo.h

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

%.o:    %.c
	@echo "$(BROWN)Compiling   ${BLUE}→   $(YELLOW)$< $(RESET)"
	@${CC} ${CFLAGS} -c -o $@ $<

PHILO_OBJS	= ${PHILO_SRCS:.c=.o}

all: ${NAME}

${NAME}:	$(PHILO_OBJS) $(HEADERS)
	@${CC} ${PHILO_SRCS} -fsanitize=thread -o ${NAME}
	@echo "\n$(GREEN)Created $(NAME) ✓ $(RESET)\n"

clean:
	${RM} ${PHILO_OBJS}
	@echo "\n${GREEN}Objects cleaned successfully $(RESET)\n"

fclean:		clean
	@${RM} ${NAME} */*.o
	@echo "\n${GREEN}Objects and executables cleaned successfully $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
