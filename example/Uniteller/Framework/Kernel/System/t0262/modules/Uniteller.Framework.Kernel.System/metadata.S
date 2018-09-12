  .global metadata
  .global metadata_size
  .section .rodata
metadata:
  .incbin "Uniteller.Framework.Kernel.System.utc"
1:
metadata_size:
  .int 1b - metadata