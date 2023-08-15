
with open("fs.img","w") as f:
    for i in range(1024):
        f.write('\x61')
