#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xadc764fd, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x7d051508, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x6a8cf606, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xe1c0244b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x433fbf3d, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xc8fca27, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x9a8313f8, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0x44366cfc, __VMLINUX_SYMBOL_STR(simple_write_to_buffer) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DFB79E93B452939FC7178FF");
