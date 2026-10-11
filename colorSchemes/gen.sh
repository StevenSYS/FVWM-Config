#!/bin/bash
tcc -run -DOUTPUT=\"gray.cs\" generator.c
tcc -run -DOFFSET1=0x14 -DOUTPUT=\"red.cs\" generator.c
tcc -run -DOFFSET2=0x14 -DOUTPUT=\"green.cs\" generator.c
tcc -run -DOFFSET3=0x14 -DOUTPUT=\"blue.cs\" generator.c
tcc -run -DOFFSET1=0x14 -DOFFSET2=0x14 -DOUTPUT=\"yellow.cs\" generator.c
tcc -run -DOFFSET1=0x14 -DOFFSET3=0x14 -DOUTPUT=\"magenta.cs\" generator.c
tcc -run -DOFFSET2=0x14 -DOFFSET3=0x14 -DOUTPUT=\"cyan.cs\" generator.c
tcc -run -DOFFSET1=0x14 -DOFFSET3=0x28 -DOUTPUT=\"purple.cs\" generator.c
tcc -run -DOFFSET1=0x40 -DOFFSET2=0x20 -DOFFSET3=0x40 -DOUTPUT=\"pink.cs\" generator.c