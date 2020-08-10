/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a GNU C/C++ compiler to compile this file.   */

__asm__ (".data");
__asm__ (".global _ctors");
__asm__ (".align 4");
__asm__ ("_ctors:");
__asm__ ("    .long 0");
__asm__ (".global _dtors");
__asm__ (".align 4");
__asm__ ("_dtors:");
__asm__ ("    .long 0");
