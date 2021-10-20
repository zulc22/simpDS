#!/usr/bin/env python3

import PIL.Image
# import glob
import math
import sys
import os.path

f = sys.argv[1]

# Skip non-existing files
if not os.path.exists(f):
    print("File",f,"doesn't exist")
    exit(1)

# Open image
fim = PIL.Image.open(f)
fim = fim.convert('RGB')

# Construct file path and open file for writing
with open( sys.argv[2], 'wb' ) as cfh:
    for p in fim.getdata():
        # Lower bit depth from 24bpp to 15bpp
        p5 = [math.floor(i/256*32) for i in p]
        # Encode color value as the DS understands it (set 15th bit for bg)
        rgb15 = (p5[0] | p5[1]<<5 | p5[2]<<10) + (1<<15)
        cfh.write(
            # Write as little endian
            rgb15.to_bytes(2, 'little')
        )
    