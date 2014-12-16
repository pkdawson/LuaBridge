# Update the below with paths to your installation of lua/luabridge
# Based on makefiles from https://github.com/merlinblack/LuaBridgeTest
LIBS=-L/usr/local/lib -llua -ldl
CXXFLAGS=-g -std=c++11 -Wall -Wno-deprecated -I/usr/local/include/lua -I$(HOME)/LuaBridge/Source/LuaBridge
EXECUTABLE=functional
SOURCES=functional.cpp
OBJDIR=obj
DEPDIR=deps

# ###################################################################

.SILENT: $(DEPS) $(DEPDIR) $(OBJDIR) clean

OBJECTS=$(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(DEPDIR)/,$(SOURCES:.cpp=.d))

.PHONY: all
all:	$(OBJDIR) $(SOURCES) $(DEPS) $(EXECUTABLE)

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.PHONY: clean
clean:
	echo 'Cleaning'
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR)/%.d: %.cpp | $(DEPDIR)
	@echo "Caching dependency info for: $<"
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

$(DEPDIR):
	mkdir -p $(DEPDIR)

ifeq (0,$(words $(findstring clean, $(MAKECMDGOALS))))
	# Don't make these, only to clean them out again.
-include $(DEPS)
endif
