#!/usr/bin/python3

a = 1
for i in range(0, 170):
    a = (a*85)%256
print(hex(a))

b = 1
for i in range(0, 170):
    b = (b*a)%256

print(hex(b))
