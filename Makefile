NAME = divashell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -I inc -I inc/libft $(READLINE_INC)

READLINE_INC= -I/usr/local/opt/readline/include
READLINE_LIB = -L/usr/local/opt/readline/lib -lreadline

SRCDIR = src
OBJDIR = objs

SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/main_utils.c \
	$(SRCDIR)/parsing/check_input.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/memory_clean.c \
	$(SRCDIR)/parsing/parse_utils.c \
	$(SRCDIR)/parsing/cmd_aux.c \
	$(SRCDIR)/parsing/expansions.c \
	$(SRCDIR)/parsing/set_commands.c \
	$(SRCDIR)/parsing/parse_utils2.c \
	$(SRCDIR)/parsing/init_structs.c \
	$(SRCDIR)/parsing/fill_redirs.c \
	$(SRCDIR)/exec/solve_path.c \
	$(SRCDIR)/exec/clean_utils.c \
	$(SRCDIR)/exec/heredocs.c \
	$(SRCDIR)/exec/execute.c \
	$(SRCDIR)/exec/dup_utils.c \
	$(SRCDIR)/exec/redirection.c \
	$(SRCDIR)/exec/signal.c \
	$(SRCDIR)/exec/run_commands.c \
	$(SRCDIR)/exec/restore_fd.c \
	$(SRCDIR)/builtin/builtin.c \
	$(SRCDIR)/builtin/builtin_echo.c \
	$(SRCDIR)/builtin/builtin_cd.c \
	$(SRCDIR)/builtin/builtin_cd_sort.c \
	$(SRCDIR)/builtin/builtin_cd_utils.c \
	$(SRCDIR)/builtin/builtin_pwd.c \
	$(SRCDIR)/builtin/builtin_export.c \
	$(SRCDIR)/builtin/builtin_env.c \
	$(SRCDIR)/builtin/builtin_unset.c \
	$(SRCDIR)/builtin/builtin_exit.c\
	$(SRCDIR)/builtin/builtin_export_utils.c \
	$(SRCDIR)/builtin/builtin_export_utils2.c
#	$(SRCDIR)/mock.c

OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

LIBFT_DIR = inc/libft

LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(OBJDIR) $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "Compilando libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJFILES) $(LIBFT_A)
	@echo "Enlazando $(NAME)..."
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT_A) $(READLINE_LIB) -o $(NAME)
	@echo "Compilación completada!"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Regla CLAVE: crea subcarpetas en objs automáticamente
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "⚙️  Compilando $<..."
	mkdir -p  $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpiando objetos..."
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@echo "Limpiando binarios..."
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
