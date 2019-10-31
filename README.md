# Core-war
Veni Vidi Vici - juochen, julee, sechang, and kradoste<br>

### How to clone
```
git clone --recursive https://github.com/pootitan/Core-war.git
```

### Encoding
```
r2 -> register  / 01  / 1 byte
23 -> indirect  / 11  / 2 bytes
%34 -> direct   / 10  / 4 bytes

Each instruction is encoded by three parts
1. the instruction code
See op_tab

2. Instruction to coding byte
r2, 23, %34 -> 0b 01 11 10 00 -> 0x78

3. Instruction to arguments
r2, 23, %34 -> 0x02 | 0x00 0x17 | 0x00 0x00 0x00 0x22

// Complete instruction to machine code, for instance:
sti r1,\%:live,\%1 ->  0x0b,      0x68,     0x01,0x00,0x0f,0x00,0x01
                    ins_code | coding byte | r1 | \%:live |   \%1
                    
and r1,\%0,r1 ->  0x06,      0x64,      0x01,0x00,0x00,0x00,0x00,0x01
                ins_code | coding byte | r1 |        \%0        | r1
```

### pesudo
Champion: hold instructions<br>
asm: encode instruction to machine code<br>
vm: read machine code and execute the game


### Reference
[Using submodules in Git - Tutorial](https://www.vogella.com/tutorials/GitSubmodules/article.html)<br>
[Core war wiki](https://en.wikipedia.org/wiki/Core_War)<br>
[Introduction to Core War](http://vyznev.net/corewar/guide.html#introduction)<br>
