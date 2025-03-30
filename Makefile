# === Compilateur ===
CC = gcc

# === Répertoires ===
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# === Recherche récursive des .c ===
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

# === Fichiers objets correspondants (dans build/) ===
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# === Nom de l'exécutable ===
TARGET = MidiVideo

# === Flags compilation (warnings, includes, récursifs) ===
INCLUDE_PATHS = $(shell find $(INCLUDE_DIR) -type d)
INCLUDES = $(foreach dir, $(INCLUDE_PATHS), -I$(dir))
CFLAGS = -Wall -Wextra -g -std=c99 $(INCLUDES)

# === Flags linkage ===
LDFLAGS = -lSDL2 -lavcodec -lavformat -lavutil -lportmidi

# === Règle par défaut ===
all: $(BUILD_DIR) $(TARGET)

# === Edition de lien finale ===
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# === Compilation des .c en .o dans build/ ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Création du dossier build/ si nécessaire ===
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# === Nettoyage ===
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

