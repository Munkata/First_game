build_dir := build
executable := MyGame

.PHONY: all clean run rebuild

all:
	mkdir -p $(build_dir) && cd $(build_dir) && cmake .. && make

run:
	./$(build_dir)/$(executable)

clean:
	rm -rf $(build_dir)

rebuild: clean all run