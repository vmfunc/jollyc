CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
EXAMPLES = examples

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/jollyc

.PHONY: all clean run-examples

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run all examples in the examples directory
run-examples: $(TARGET)
	@echo "Running examples..."
	@for example in $(EXAMPLES)/*.jc; do \
		if [ -f "$$example" ]; then \
			echo "\nCompiling and running $$example:"; \
			filename=$$(basename "$$example" .jc); \
			$(TARGET) "$$example" "$(OBJDIR)/$$filename.c" "$(BINDIR)/$$filename" && \
			"$(BINDIR)/$$filename"; \
		fi \
	done

clean:
	rm -rf $(OBJDIR) $(BINDIR)