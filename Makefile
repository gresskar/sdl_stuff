CC := clang
CFLAGS += -std=c99 -Wall -Wextra -pedantic -pedantic-errors -march=native -fPIC -fstack-clash-protection -fstack-protector-all -fcf-protection=full -flto=full -fvisibility=hidden -fsanitize=cfi -D_FORTIFY_SOURCE=3 -O3 -s
LDFLAGS += -l SDL3 -L /usr/local/lib -fuse-ld=lld -rtlib=compiler-rt -Wl,-pic-executable -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack

sdl_test: bin/sdl_test bin/sdl_test
bin/sdl_test: src/main.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
bin/sdl_test: src/main.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY clean:
	rm -vf bin/*