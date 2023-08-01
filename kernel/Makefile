# boot files
boot_ASM_sources := $(shell find src/boot -name *.asm)
boot_ASM_objects := $(patsubst src/boot/%.asm, build/boot/%.o, $(boot_ASM_sources))

boot_C_sources := $(shell find src/boot -name *.c)
boot_C_objects := $(patsubst src/boot/%.c, build/boot/%.o, $(boot_C_sources))

# core libs
core_C_sources := $(shell find src/core -name *.c)
core_C_objects := $(patsubst src/core/%.c, build/core/%.o, $(core_C_sources))

core_ASM_sources := $(shell find src/core -name *.asm)
core_ASM_objects := $(patsubst src/core/%.asm, build/core/%.o, $(core_ASM_sources))

# kernel files
kernel_C_sources := $(shell find src/kernel -name *.c)
kernel_C_objects := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_C_sources))

kernel_ASM_sources := $(shell find src/kernel -name *.asm)
kernel_ASM_objects := $(patsubst src/kernel/%.asm, build/kernel/%.o, $(kernel_ASM_sources))


boot_objects := $(boot_ASM_objects) $(boot_C_objects)
core_objects := $(core_ASM_objects) $(core_C_objects)
kernel_objects := $(kernel_ASM_objects)  $(kernel_C_objects)

objects := $(boot_objects) $(core_objects) $(kernel_objects)

kernel = out/kernel.bin
iso = out/output.iso

linker_s = build/linker.ld

all:
	@echo "if you want to build iso file call 'make iso'"
	@exit
# boot build
$(boot_ASM_objects): build/boot/%.o : src/boot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/boot/%.o, src/boot/%.asm, $@) -o $@
$(boot_C_objects): build/boot/%.o : src/boot/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/include -ffreestanding $(patsubst build/boot/%.o, src/boot/%.c, $@) -o $@

# core build
$(core_ASM_objects): build/core/%.o : src/core/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/core/%.o, src/core/%.asm, $@) -o $@
$(core_C_objects): build/core/%.o : src/core/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/include -ffreestanding $(patsubst build/core/%.o, src/core/%.c, $@) -o $@

# kernel build
$(kernel_ASM_objects): build/kernel/%.o : src/kernel/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/kernel/%.o, src/kernel/%.asm, $@) -o $@
$(kernel_C_objects): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/include -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@


clean:
	rm -Rf ./out/*
	rm -Rf ./build/boot/*  ./build/core/*  ./build/kernel/*
.PHONY: iso
iso: $(iso)
$(iso): $(objects) boot/grub/grub.cfg $(linker_s)
	mkdir -p out
	ld -n -o $(kernel) -T $(linker_s) $(objects)
	cp $(kernel) boot/kernel.bin
	grub-mkrescue /usr/lib/grub/i386-pc -o $(iso) .
