NAME = Galaxy_simulation.exe
CC = g++
CFLAGS = -std=c++11 -w -Wl,-subsystem,windows

SRCS_NAME = main.cpp star.cpp vector.cpp utils.cpp block.cpp
SRCS_DIR = sources/
SRCS = $(addprefix $(SRCS_DIR),$(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.cpp=.o)
OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR),$(OBJS_NAME))

INCS = -Iincludes -Isdl/i686-w64-mingw32/include/SDL2
LIB = -Lsdl/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2

STG_RED = [91m
GREEN = [32m
STG_GREEN = [92m
STG_CYAN = [96m
STG_BLUE = [94m
GRAY = [90m
RESET = [0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GRAY)[Galaxy]$(STG_CYAN) Complilation de $(NAME)$(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LIB) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir "$(OBJS_DIR)" 2> nul || :
	@echo $(GRAY)[Galaxy]$(GREEN) Complilation de $(STG_GREEN)$(notdir $<)$(RESET)
	@$(CC) $(CFLAGS) $(INCS) $(LIB) -c $< -o $@

clean:
	@echo $(GRAY)[Galaxy]$(STG_RED) Suppression des binaires$(RESET)
	@rmdir /S /Q "$(OBJS_DIR)" 2> nul

fclean: clean
	@echo $(GRAY)[Galaxy]$(STG_RED) Suppression de l'executable$(RESET)
	@del /f /q $(NAME) 2> nul

re: fclean all
