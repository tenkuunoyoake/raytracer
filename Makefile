SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o .h .d

CXXFLAGS = -g -Wall -Iinclude
LDFLAGS =
LDLIBS =
VPATH = src

TARGET = raytracer
SRCEXT = cpp
SRCDIR = src
BUILDDIR = build
DEPDIR = dep

SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(BUILDDIR)/%.o, $(SOURCES))
DEPENDS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(DEPDIR)/%.d, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPENDS)
endif

$(BUILDDIR)/%.o: | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(DEPDIR)/%.d: $(SRCDIR)/%.$(SRCEXT) | $(DEPDIR)
	$(CXX) -MM -MT $(patsubst $(DEPDIR)/%.d, $(BUILDDIR)/%.o, $@) $(CXXFLAGS) $< > $@

$(DEPDIR):
	mkdir $(DEPDIR)

.PHONY: clean all
clean:
	$(RM) -r $(DEPDIR) $(BUILDDIR) $(TARGET) *.png
