
C_SRCS += \
../src/card.c \
../src/index.c \
../src/node.c \
../src/rect.c \
../src/split_l.c \
../src/test.c

OBJS += \
./obj/card.o \
./obj/index.o \
./obj/node.o \
./obj/rect.o \
./obj/split_l.o \
./obj/test.o

C_DEPS += \
./obj/card.d \
./obj/index.d \
./obj/node.d \
./obj/rect.d \
./obj/split_l.d \
./obj/test.d

all: $(OBJS)

obj/%.o: ../src/%.c ./obj/%.d
	@echo 'start building $< ...'
	@echo 'Invoking : GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" \
-MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $< '
	@echo ''

-include $(C_DEPS)

./obj/%.d: ../src/%.c
	@echo 'start building $(notdir $@)...'
	$(CC) $< $(INCLUDE) -MM -MD -o $@






