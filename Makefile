.PHONY: all clean fclean re debug release run submodules

GENERATOR = "Unix Makefiles"
OUTPUT_DIR = .
DEBUG_DIR = build-debug
RELEASE_DIR = build-release

all: debug

clean:
	$(RM) -r $(DEBUG_DIR) $(RELEASE_DIR)

fclean: clean
	$(RM) $(shell find . -type f -iname "voxelfactory")

re: fclean all

submodules:
	git submodule update --init --recursive

debug: submodules
	cmake . -G $(GENERATOR)	\
		-DCMAKE_BUILD_TYPE=Debug	\
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(OUTPUT_DIR)	\
		-B $(DEBUG_DIR)
	cmake --build $(DEBUG_DIR)

release: submodules
	cmake . -G $(GENERATOR)	\
		-DCMAKE_BUILD_TYPE=Release	\
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(OUTPUT_DIR)	\
		-B $(RELEASE_DIR)
	cmake --build $(RELEASE_DIR)
	cp $(RELEASE_DIR)/src/voxelfactory .

run: debug
	./$(DEBUG_DIR)/src/voxelfactory
