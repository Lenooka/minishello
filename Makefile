NAME = minishell
CC = cc
SRCS = heredoc_utils.c cute_utils.c strcompr.c replace_var.c replace_var2.c str_arr_utils.c quotes_utils.c  libft_bonus.c echo.c built_ex.c export_empty.c export.c heredocheck.c comand_list_init.c envlist_init.c exit_status.c minishell_var_init.c execution_start.c syntax_checks_utils.c syntax_checks.c syntex_error.c other_syntax_checks.c utils.c exstart_utils.c parser_start.c split_token_utils.c split_token.c  heredoc.c signals.c frees.c builtin_extras.c redirections.c inoutredir.c pwd.c exe_cutie.c cd.c exit.c  env.c unset.c list_utilslibftbonus.c more_free.c isbuilt.c char_checks.c minishell.c 
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf
OBJ_DIR = obj
LIBFT_PATH = ./LIBFTall/
LIBFT_LIB = $(LIBFT_PATH)libft.a
LFLAGS = -L$(LIBFT_PATH) -lft -lreadline
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiling...$(RESET)"


$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(GREEN)Linking Minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) 
	@echo "$(GREEN)Minishell compiled successfully!$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)Cleaning...$(RESET)"
	@make clean -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(RED)Fcleaning...$(RESET)"
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re LIBFTall