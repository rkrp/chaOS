.PHONY: all
all: chaOS.iso

.PHONY: all-hdd
all-hdd: chaOS.hdd

.PHONY: run
run: chaOS.iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom chaOS.iso -boot d

.PHONY: run-uefi
run-uefi: ovmf-x64 chaOS.iso
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -cdrom chaOS.iso -boot d

.PHONY: run-hdd
run-hdd: chaOS.hdd
	qemu-system-x86_64 -M q35 -m 2G -hda chaOS.hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 chaOS.hdd
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -hda chaOS.hdd

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

chaOS.iso: limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel/kernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o chaOS.iso
	limine/limine-deploy chaOS.iso
	rm -rf iso_root

chaOS.hdd: limine kernel
	rm -f chaOS.hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=chaOS.hdd
	parted -s chaOS.hdd mklabel gpt
	parted -s chaOS.hdd mkpart ESP fat32 2048s 100%
	parted -s chaOS.hdd set 1 esp on
	limine/limine-deploy chaOS.hdd
	sudo losetup -Pf --show chaOS.hdd >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v kernel/kernel.elf limine.cfg limine/limine.sys img_mount/
	sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root chaOS.iso chaOS.hdd
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf-x64
	$(MAKE) -C kernel distclean
