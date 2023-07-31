NAME = philo

# # # # # # # # # # # # # # # # # # # #
#			    DEFINES				  #
# # # # # # # # # # # # # # # # # # # #

# enable(1) when debugging
DEBUGGING = 0

ifndef $(TESTING)
TESTING := $(DEBUGGING)
endif

ifdef $(ASAN)
	ifeq ($(ASAN), 1)
		TSAN := 0
	endif
endif

ifdef $(TSAN)
	ifeq ($(TSAN), 1)
		ASAN := 1
	endif
endif

DONORM := 0

ifndef $(TSAN)
TSAN := 0
endif
ifndef $(ASAN)
ASAN := 0
endif

# you can do concatenation of variables.. cool
ifeq ($(DEBUGGING)$(TSAN)$(ASAN), 100)
	TSAN := 1
endif
# for when, for some reason, you would compile with ASAN=1 TSAN=1 together
ifeq ($(DEBUGGING)$(TSAN)$(ASAN), 111)
	override ASAN := 0
endif

CSI_RESET := "\033[0m"
CSI_RED   := "\033[1;31m"
CSI_GREEN   := "\033[1;32m"

# # # # # # # # # # # # # # # # # # # #
#			 SOURCE_FILES			  #
# # # # # # # # # # # # # # # # # # # #

SOURCE_DIR			:= source_files/
SOURCE_FILES 		:= \
						utils/strtoll.c \
						utils/validate_input.c \
						utils/debug.c \
						utils/print_wrappers.c \
						utils/output.c \
						utils/alloc_wrap.c \
						utils/time.c \
						utils/writer.c \
						utils/ft_nbrtostr.c \
						utils/message_queue.c \
						forks.c \
						philosophers_actions.c \
						event_output.c \
						init.c \
						observer.c \
						philosophers.c \
						simulation.c \
						cleanup.c \
						monitoring.c \
						main.c
SOURCE_FILES		:= $(addprefix $(SOURCE_DIR), $(SOURCE_FILES))

ifeq ($(TESTING), 0)
	SOURCE_FILES	+= tests/not_testing.c
endif

ifeq ($(TESTING), 1)
	SOURCE_FILES 	+= tests/root.c \
						tests/validate_input/tests.c \
						tests/validate_input/validate_input.c \
						tests/create_forks/tests.c \
						tests/create_forks/create_forks.c \
						tests/alloc_wrap/tests.c \
						tests/alloc_wrap/alloc_wrap.c \
						tests/time/tests.c \
						tests/time/time.c \
						tests/logging.c
endif

OBJECT_DIR := object_files/
# Variable with object files put in an object_files subdirectory
OBJ := $(addprefix $(OBJECT_DIR), $(SOURCE_FILES:.c=.o))


# # # # # # # # # # # # # # # # # # # #
#				HEADERS				  #
# # # # # # # # # # # # # # # # # # # #

HEADER_DIR 			:= include/
HEADERS_FILES 		:= \
						status.h \
						philosophers.h \
						datastructures.h \
						strtoll.h \
						helpers.h \
						validate_input.h \
						cleanup.h \
						philo_time.h \
						forks.h \
						message_queue.h \
						writer.h \
						debug.h

HEADERS 			:= $(addprefix $(HEADER_DIR), $(HEADERS_FILES))

TEST_HEADER_DIR 	:= tests/include/
TEST_H_FILES 		:= \
						testing.h \
						t_validate_input.h \
						t_create_forks.h \
						t_alloc_wrap.h \
						t_time.h

TEST_HEADERS		:= $(addprefix $(TEST_HEADER_DIR), $(TEST_H_FILES))

ifeq ($(TESTING), 1)
HEADERS 			+= $(TEST_HEADERS)
endif


# # # # # # # # # # # # # # # # # # # #
#			  FLAGS ETC				  #
# # # # # # # # # # # # # # # # # # # #

# Override some default/implicit MAKE variables
# Extra flags to give to the C compiler
CFLAGS := -Wall -Werror -Wextra -pthread
ifeq ($(DEBUGGING), 1)
	CFLAGS += -g -pedantic -O0
endif
ifeq ($(ASAN), 1)
	CFLAGS += -fsanitize=address
endif
ifeq ($(TSAN), 1)
	CFLAGS += -fsanitize=thread
endif

CPPFLAGS := -I $(HEADER_DIR) -I $(TEST_HEADER_DIR)

# # # # # # # # # # # # # # # # # # # #
#				  NORM  			  #
# # # # # # # # # # # # # # # # # # # #

NORM_OUTPUT := 0
ifeq ($(MAKELEVEL), 0)
	ifeq ($(DONORM), 1)
		RUN_NORM := $(shell norminette | grep "Error[:!]" > normfile.txt)
		NORM_OUTPUT := $(shell cat normfile.txt)
	endif
endif

# # # # # # # # # # # # # # # # # # # #
#			  COMPILATION			  #
# # # # # # # # # # # # # # # # # # # #

all: $(HEADERS)
ifeq ($(TESTING), 0)
	@if [ -d "object_files/tests/time" ]; then \
		$(MAKE) clean; \
	fi
else
	@if [ ! -d "object_files/tests" ]; then \
		$(MAKE) clean; \
	fi
endif
ifeq ($(ASAN), 1)
	@if [ ! -f ".has_asan" ]; then \
		$(MAKE) clean; \
	fi
else
	@if [ -f ".has_asan" ]; then \
		$(MAKE) clean; \
	fi
endif
ifeq ($(TSAN), 1)
	@if [ ! -f ".has_tsan" ]; then \
		$(MAKE) clean; \
	fi
else
	@if [ -f ".has_tsan" ]; then \
		$(MAKE) clean; \
	fi
endif
	@$(MAKE) $(NAME)
ifeq ($(DONORM), 1)
ifneq ($(NORM_OUTPUT),)
	@echo $(CSI_RED)"NORM ERRORS!"$(CSI_RESET)
	@cat normfile.txt
	@echo $(CSI_RED)"------------"$(CSI_RESET)
else
	@echo $(CSI_GREEN)" -- NORM OK --"$(CSI_RESET)
endif
endif
	@$(RM) normfile.txt
#	End of "all" rule

# compiles .c files to .o files
# put them all in a object_files directory to make it cleaner
$(OBJECT_DIR)%.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -D TESTING=$(TESTING) -c $< -o $@

$(NAME): $(OBJ) $(HEADERS)
ifeq ($(ASAN), 1)
	@touch .has_asan
endif
ifeq ($(TSAN), 1)
	@touch .has_tsan
endif
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

clean:
	$(RM) -r $(OBJECT_DIR)
	$(RM) .has_asan
	$(RM) .has_tsan

re: fclean all

.PHONY: clean fclean re all
