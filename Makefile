NAME		= miniRT
BONUS		= miniRT_BONUS

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS	:= ft
LIBS_TARGET :=            \
	Mandatory/lib/libft/libft.a \

INCS        := Mandatory/include    \
	Mandatory/lib/libft/include   \

SRC_DIR     := Mandatory/src
SRCS        :=	main.c \
				Matrix/matrix.c \
				Matrix/matrix_maker.c \
				Matrix/matrix_inverter.c \
				Matrix/matrix_transformation.c \
				Ray/ray.c \
				Ray/shadow.c \
				Ray/light_shading.c \
				Render/world.c \
				Render/camera.c \
				Render/render.c \
				Render/intersection.c \
				Shape/cylinder_inter.c \
				Shape/shape_inter.c \
				Tuples/color.c \
				Tuples/tuple.c \
				Tuples/tuple_2.c \
				Checker/check.c \
				Checker/validation.c \
				Checker/check_info.c \
				Checker/check_shape.c \
				Init/save.c \
				Init/strto.c \
				Init/save_info.c \
				Init/save_shape.c \
				Init/save_matrix.c \
				Utils/gnl.c \
				Utils/utils.c \
				Utils/string_utils.c\
				Utils/matrix_utils.c \


SRCS        := $(SRCS:%=$(SRC_DIR)/%)
BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# BONUS --------------------------

LIBS_TARGET_BONUS :=            \
	Bonus/lib/libft/libft.a \

INCS_BONUS        := Bonus/include    \
	Bonus/lib/libft/include   \

SRC_DIR_BONUS	:= Bonus/src

SRCS_BONUS     	:=	main.c \
				Tuples/color.c \
				Matrix/matrix.c \
				Matrix/matrix_inverter.c \
				Matrix/matrix_transformation.c \
				Matrix/matrix_maker.c \
				ray/ray.c \
				ray/light_shading.c \
				Render/world.c \
				Render/camera.c \
				ray/shadow.c \
				Shape/cylinder_inter.c \
				Shape/shape_inter.c \
				Utils/utils_to_delete.c \
				Utils/utils.c \
				Render/intersection.c \
				Render/render.c \
				Tuples/tuple.c \
				Tuples/tuple_2.c \
				parsing/check.c\
				parsing/checkInfo.c\
				parsing/checkShape.c\
				parsing/save.c\
				parsing/saveInfo.c\
				parsing/saveShape.c\
				parsing/string_utils.c\
				parsing/gnl.c\
				parsing/strto.c\
				parsing/valid.c\
				pattern/pattern.c

SRCS_BONUS	:= $(SRCS_BONUS:%=$(SRC_DIR_BONUS)/%)
BUILD_DIR_B   := .build_b
OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR_B)/%.o)

CPPFLAGS_BONUS    := $(addprefix -I,$(INCS_BONUS)) -MMD -MP
LDFLAGS_BONUS     := $(addprefix -L,$(dir $(LIBS_TARGET_BONUS)))

# BONUS --------------------------

DEPS        := $(OBJS:.o=.d)
DEPS_B      := $(OBJS_BONUS:.o=.d)

CC          := gcc 
CFLAGS      := -Wall -Wextra -Werror -g
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))


#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux $(LDLIBS) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -Imlx_linux -O3 -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

# BONUS --------------------------
bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS) $(LIBS_TARGET_BONUS)
	$(CC) $(LDFLAGS_BONUS) $(OBJS_BONUS) -Lmlx_linux -lmlx_Linux $(LDLIBS) -Imlx_linux -lXext -lX11 -lm -lz -o $(BONUS)
	$(info CREATED $(BONUS))

$(LIBS_TARGET_BONUS):
	$(MAKE) -C $(@D)

$(BUILD_DIR_B)/%.o: $(SRC_DIR_BONUS)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -Imlx_linux -O3 -c -o $@ $<
	$(info CREATED BONUS $@)

# BONUS --------------------------



clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(OBJS_BONUS) $(DEPS_B)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)
	$(RM) $(BONUS)

re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY:		all clean fclean re bonus
