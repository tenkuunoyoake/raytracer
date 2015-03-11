SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o .d .h

CXXFLAGS = -g -Wall -Iinclude
LDFLAGS =
LDLIBS =
VPATH = src

TARGET = bin/raytracer
SRCEXT = cpp
SRCDIR = src
BUILDDIR = build
DEPDIR = dep

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(BUILDDIR)/%.o, $(SOURCES))
DEPENDS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(DEPDIR)/%.d, $(SOURCES))

all: main 

main: $(OBJECTS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEPDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(DEPDIR)
	$(CXX) -M $(CXXFLAGS) $< > $@

-include $(DEPENDS)

.PHONY: clean all
clean: 
	$(RM) -r $(BUILDDIR) $(TARGET) $(DEPDIR) *.png
