CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g

BUILD_DIR := builds
SRC_DIR := src

GAME_BIN := $(BUILD_DIR)/game
TEST_BIN := $(BUILD_DIR)/test_game

GAME_OBJS := \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/game.o \
	$(BUILD_DIR)/save.o \
	$(BUILD_DIR)/input.o \
	$(BUILD_DIR)/ui.o \
	$(BUILD_DIR)/story.o \
	$(BUILD_DIR)/event.o

TEST_OBJS := \
	$(BUILD_DIR)/test.o \
	$(BUILD_DIR)/game.o \
	$(BUILD_DIR)/save.o

.PHONY: all test run clean

all: $(GAME_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(GAME_BIN): $(GAME_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(GAME_OBJS)

$(TEST_BIN): $(TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

# 显式声明头文件依赖，确保修改 .h 后自动重编对应 .o
$(BUILD_DIR)/game.o: $(SRC_DIR)/game.c $(SRC_DIR)/game.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/save.o: $(SRC_DIR)/save.c $(SRC_DIR)/save.h $(SRC_DIR)/game.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/input.o: $(SRC_DIR)/input.c $(SRC_DIR)/input.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/ui.o: $(SRC_DIR)/ui.c $(SRC_DIR)/ui.h $(SRC_DIR)/game.h $(SRC_DIR)/save.h $(SRC_DIR)/input.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/story.o: $(SRC_DIR)/story.c $(SRC_DIR)/story.h $(SRC_DIR)/ui.h $(SRC_DIR)/game.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/event.o: $(SRC_DIR)/event.c $(SRC_DIR)/event.h $(SRC_DIR)/story.h $(SRC_DIR)/ui.h $(SRC_DIR)/input.h $(SRC_DIR)/game.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/game.h $(SRC_DIR)/save.h $(SRC_DIR)/input.h $(SRC_DIR)/ui.h $(SRC_DIR)/story.h $(SRC_DIR)/event.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/test.o: $(SRC_DIR)/test.c $(SRC_DIR)/game.h $(SRC_DIR)/save.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_BIN)
	./$(TEST_BIN)

# 固定在 game1/ 根目录启动，确保 save.txt 不被生成到 builds/ 里
run: $(GAME_BIN)
	./$(GAME_BIN)

clean:
	rm -rf $(BUILD_DIR)
