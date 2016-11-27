
SHELL = /bin/sh

INCLUDE_DIR :=
LIB_DIR := -lm
EXEC = ../ir_tree

-include obj/subdir.mk

# something

all:${EXEC}

${EXEC}: ${OBJS}
	@echo ' Building target: $@ '
	@echo 'Invoking : GCC Linker'
	gcc -o $@ $(OBJS) $(LIB_DIR)
	@echo 'Finished building target: $@'
	@echo ''

clean:
	@echo 'start rm objs and deps ...'
	$(RM) $(OBJS) \
	$(C_DEPS)
	@echo 'Finish rm objs and deps ...'

.PHONY: all clean
.SECONDARY:

