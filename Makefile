CXXFLAGS = -g -Wall -Iinclude
LDFLAGS =
LDLIBS =
VPATH = src

TARGET = bin/raytracer
SRCEXT = cpp
SRCDIR = src
BUILDDIR = build

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(BUILDDIR)/%.o, $(SOURCES))

all: main 

main: $(OBJECTS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean: 
	$(RM) -r $(BUILDDIR) $(TARGET) *.o raytracer