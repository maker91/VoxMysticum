CC			= g++
CFLAGS		= -Wall -Wextra -pedantic -std=c++11 -g
LDFLAGS		= -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lsfml-network
INCPATH		= 
LIBPATH		= 
DEFINES		= 
NAME 		= VoxMysticum
INSTALLDIR 	= .

# --------- DON'T EDIT BELOW THIS LINE -----------
SOURCES		= $(shell find src/ -name *.cpp)
SRCDIRS		= $(shell find src/ -type d)
OBJECTS		= $(SOURCES:src/%.cpp=obj/%.o)
OBJDIRS 	= $(SRCDIRS:src/%=obj/%)
DEPENDS		= $(OBJECTS:.o=.d)
EXECUTABLE	= bin/$(NAME)
INSTALLPATH	= $(INSTALLDIR)/$(NAME)

.PHONY: all
all: $(EXECUTABLE)
	@echo "done!"
	
$(EXECUTABLE): bin $(OBJDIRS) $(OBJECTS)
	@echo "buiding $(EXECUTABLE)"
	@$(CC) $(LIBPATH) $(OBJECTS) $(LDFLAGS) -o $@
	
$(OBJDIRS):
	@mkdir -p $@
	
bin:
	@mkdir -p bin

.PHONY: clean	
clean:
	@echo "cleaning project"
	@rm -rf obj/
	@rm -rf bin/
	@echo "done!"

.PHONY: install
install: $(EXECUTABLE)
	@echo "installing..."
	@mkdir $(INSTALLPATH)
	@cp bin/* $(INSTALLPATH)
	@cp -r res/* $(INSTALLPATH)
	@echo "done!"

.PHONY: uninstall
uninstall:
	@echo "uninstalling..."
	@rm -rf "$(INSTALLPATH)"
	@echo "done!"

-include $(DEPENDS)

obj/%.o : src/%.cpp
	@echo "compiling $<"
	@$(CC) $(CFLAGS) $(INCPATH) $(DEFINES) -MMD -MP -c $< -o $@
