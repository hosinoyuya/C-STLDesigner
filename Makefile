COMPILER  = g++49
CFLAGS    = -Wall -std=c++11
ifeq "$(shell getconf LONG_BIT)" "64"
	  LDFLAGS = -L /opt/boost/default/lib -lboost_system -lboost_filesystem -lyaml-cpp
  else
	  LDFLAGS =
  endif
  LIBS      =
  INCLUDE   = -DBOOST_SYSTEM_NO_DEPRECATED
  TARGET    = ./run
  SRCDIR    = ./
  ifeq "$(strip $(SRCDIR))" ""
	  SRCDIR  = .
  endif
  SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
  OBJDIR    = ./obj
  ifeq "$(strip $(OBJDIR))" ""
	  OBJDIR  = .
  endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
	DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
		$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
		-mkdir -p $(OBJDIR)
			$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
		-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
