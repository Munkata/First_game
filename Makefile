build_dir := build
executable := MyGame

.PHONY: all clean run rebuild

all:
	mkdir -p $(build_dir) && \
	cd $(build_dir) && \
	cmake .. && \
	make

run: all
	./$(build_dir)/$(executable)

clean:
	rm -rf $(build_dir)

rebuild:
	$(MAKE) clean
	$(MAKE) run