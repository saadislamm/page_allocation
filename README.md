# New page maps at the last freed physical address

This project maps 10 pages of 4KB each, frees them and map 10 new pages.

It is observed that the new pages are mapped to the same physical addresses in reverse order.


## Steps to run
```
$ make
$  sudo ./map_unmap_map
```

## Output
```
____________________________________________________

			MAP
____________________________________________________
Virtual : 0x7fcdc42dd000 	Physical : 2a72df000 
Virtual : 0x7fcdc42de000 	Physical : 28dbef000 
Virtual : 0x7fcdc42df000 	Physical : 29ea7a000 
Virtual : 0x7fcdc42e0000 	Physical : 2a561d000 
Virtual : 0x7fcdc42e1000 	Physical : 2841ae000 
Virtual : 0x7fcdc42e2000 	Physical : 2a6c9e000 
Virtual : 0x7fcdc42e3000 	Physical : 2a7302000 
Virtual : 0x7fcdc42e4000 	Physical : 27d0b1000 
Virtual : 0x7fcdc42e5000 	Physical : 2a43df000 
Virtual : 0x7fcdc42e6000 	Physical : 2a4d67000 
____________________________________________________

			MUNMAP
____________________________________________________
Virtual : 0x7fcdc42dd000 	Physical : 0 
Virtual : 0x7fcdc42de000 	Physical : 0 
Virtual : 0x7fcdc42df000 	Physical : 0 
Virtual : 0x7fcdc42e0000 	Physical : 0 
Virtual : 0x7fcdc42e1000 	Physical : 0 
Virtual : 0x7fcdc42e2000 	Physical : 0 
Virtual : 0x7fcdc42e3000 	Physical : 0 
Virtual : 0x7fcdc42e4000 	Physical : 0 
Virtual : 0x7fcdc42e5000 	Physical : 0 
Virtual : 0x7fcdc42e6000 	Physical : 0 
____________________________________________________

			MAP
____________________________________________________
Virtual : 0x7fcdc42dd000 	Physical : 2a4d67000 
Virtual : 0x7fcdc42de000 	Physical : 2a43df000 
Virtual : 0x7fcdc42df000 	Physical : 27d0b1000 
Virtual : 0x7fcdc42e0000 	Physical : 2a7302000 
Virtual : 0x7fcdc42e1000 	Physical : 2a6c9e000 
Virtual : 0x7fcdc42e2000 	Physical : 2841ae000 
Virtual : 0x7fcdc42e3000 	Physical : 2a561d000 
Virtual : 0x7fcdc42e4000 	Physical : 29ea7a000 
Virtual : 0x7fcdc42e5000 	Physical : 28dbef000 
Virtual : 0x7fcdc42e6000 	Physical : 2a72df000 
```
