import PIL.Image
import glob
import math

for f in glob.glob("*.png"):
    fim = PIL.Image.open(f)
    fim = fim.convert('RGB')
    with open( '.'.join(f.split('.')) + '.dsbmp', 'wb' ) as cfh:
        for p in fim.getdata():
            p5 = [math.floor(i/256*32) for i in p]
            rgb15 = (p5[0] | p5[1]<<5 | p5[2]<<10)
            cfh.write(
                rgb15.to_bytes(2, 'little')
            )
        