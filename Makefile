MAIN_DIR = src

run-main:
	$(MAKE) -C $(MAIN_DIR) run

clean:
	$(MAKE) -C $(MAIN_DIR) clean
