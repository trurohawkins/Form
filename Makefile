TARGET = Form

DEV_CFLAGS = -g -fsanitize=address,undefined -fno-omit-frame-pointer
DEV_LDFLAGS = -fsanitize=address,undefined

TSAN_CFLAGS = -g -O1 -fsanitize=thread -fno-omit-frame-pointer
TSAN_LDFLAGS = -fsanitize=thread

PROD_CFLAGS = -O2
PROD_LDFLAGS =

CFLAGS = -MMD -MP
LDFLAGS =

dev: CFLAGS += $(DEV_CFLAGS)
dev: LDFLAGS += $(DEV_LDFLAGS)
dev: $(TARGET)

tsan: CFLAGS += $(TSAN_CFLAGS)
tsan: LDFLAGS += $(TSAN_LDFLAGS)
tsan: $(TARGET)

prod: CFLAGS += $(PROD_CFLAGS)
prod: LDFLAGS += $(PROD_LDFLAGS)
prod: $(TARGET)

ENGINEDIR = ../GameCore/
RENDERER = TUI
RENDERDIR = ../$(RENDERER)/
RENDERLIB = lib$(RENDERER).a


# Linking
$(TARGET): FormNetwork.h $(RENDERER).h libForm.a libGame.a $(RENDERLIB) libOIB.a libMoltnCore.a libHelper.a  main.o  
	gcc main.o -o $@ $(LDFLAGS) libForm.a $(RENDERLIB) libGame.a libOIB.a libMoltnCore.a libHelper.a -lm

libHelper.a:
	$(MAKE) -C ../FormNetwork/
	cp ../FormNetwork/libHelper.a .

libMoltnCore.a:
	$(MAKE) -C $(ENGINEDIR)
	cp $(ENGINEDIR)libMoltnCore.a .

libOIB.a:
	$(MAKE) -C $(ENGINEDIR)
	cp $(ENGINEDIR)libOIB.a .

libGame.a:
	$(MAKE) -C $(ENGINEDIR)
	cp $(ENGINEDIR)libGame.a .

GameCore.h:
	$(MAKE) -C $(ENGINEDIR)
	cp $(ENGINEDIR)GameCore.h .

$(RENDERLIB):
	$(MAKE) -C $(RENDERDIR)
	cp $(RENDERDIR)$(RENDERLIB) .

$(RENDERER).h:
	$(MAKE) -C $(RENDERDIR)
	cp $(RENDERDIR)$(RENDERER).h .

FormNetwork.h: GameCore.h 
	@echo "Generating Form header"
	@echo "#pragma once" > $@
	@cat GameCore.h form.h cell.h world.h WorldManager.h >> $@

# Static lib
libForm.a: form.o cell.o world.o WorldManager.o  
	ar rs $@ $^

# Compiling
main.o: main.c
	gcc $(CFLAGS) -c main.c -o $@

form.o: $(FD)form.c $(FD)form.h
	gcc $(CFLAGS) -c $(FD)form.c -o $@

cell.o: $(FD)cell.c $(FD)cell.h
	gcc $(CFLAGS) -c $(FD)cell.c -o $@

world.o: $(FD)world.c $(FD)world.h
	gcc $(CFLAGS) -c $(FD)world.c -o $@

WorldManager.o: $(FD)WorldManager.c $(FD)WorldManager.h
	gcc $(CFLAGS) -c $(FD)WorldManager.c -o $@


# tools
clean:
	rm -f *.o *.a *.d

fclean:
	rm -f $(TARGET) *.o *.a *.d GameCore.h FormNetwork.h $(RENDERER).h

fixTerminal:
	stty sane

# merges .d files into dependency graph
-include *.d
