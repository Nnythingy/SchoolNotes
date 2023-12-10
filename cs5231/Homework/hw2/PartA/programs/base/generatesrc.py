#!/usr/bin/python

import random
import shutil

# Grab sid

fsid = open("../../SID",'r')
sid = fsid.read().strip()
fsid.close()
if len(sid) < 8:
    print "Please put NUSNET ID in this file, using the script provided."
    exit(1)

def int32(x):
    if x>0xFFFFFFFF:
        raise OverflowError
    if x>0x7FFFFFFF:
        x=int(0x100000000-x)
    if x<2147483648:
        return -x
    else:
        return -2147483648

random.seed(sid)
seed32 = hash(sid) & 0xFFFFFFFF
random.seed(seed32)
print "randomize with seed: " + str(seed32)

# Generate basic program
def gen_target(num,reps):
    ft = open("./base/program"+num+".c",'r')
    fto = open("program"+num+".c",'w')
    t = ft.readlines()
    ft.close()
    for l in t:
        for (v,t) in reps:
            l = l.replace(v,t)
        fto.write(l)
    fto.close()



# Setup program1
p1_rep = "BUF1"
random1 = random.randrange(1,7)
p1_v = str(128*random1)

# Setup program2
p2_rep = "BUF2"
p2_r = random.randrange(0,21)
if p2_r >= 13:
    p2_v = str(200+(p2_r-13))
else:
    p2_v = str(100+p2_r)

# Setup program3
p3_rep_1 = "T3_WIDGET_NUMDUBS"
p3_v_1 = str(2**(random.randrange(2,4)) - 1)
p3_rep_2 = "T3_MAXWIDGETS"
p3_v_2 = str(513 + random.randrange(1,401))

# Setup program4
p4_rep = "BUF4"
p4_v = str(100*random.randrange(1,10))

# Setup program5 (no randomization for now)
p5_rep = "BUF5"
p5_v = "400"

#Setup program6
p6_rep = "BUF6"
p6_v = str(128*random.randrange(1,7))

# Setup program7 (no randomization for now)
p7_rep = "BUF7"
p7_v = "24"

# Generate programs
gen_target("1",[(p1_rep,p1_v)])
gen_target("2",[(p2_rep,p2_v)])
gen_target("3",[(p3_rep_1,p3_v_1),(p3_rep_2,p3_v_2)])
gen_target("4",[])
gen_target("5",[])
gen_target("6",[(p6_rep,p6_v)])
gen_target("7", [])
