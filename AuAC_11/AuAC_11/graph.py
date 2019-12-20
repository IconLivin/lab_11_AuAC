import matplotlib.pyplot as plt
from scipy import interpolate 
import numpy as np

def max(x,y,z):
    if x > y:
        if x > z:
            return x
    if x > y:
        if x < z:
            return z
    if y > x:
        if y > z:
            return y


def find_max(x,y,z):
    maxim = max(x[0],y[0],z[0])
    for i in range(1,len(x)):
        local_m = max(x[i],y[i],z[i])
        if local_m>maxim:
            maxim=local_m
            
    return maxim    
x = []
y1 = []
y2 = []
y3 = []





file = open('OUTPUT.txt')

string = file.read().split('\n')

for i in range(0,len(string)):
    if (i+1)%4==1:
        x.append(int(string[i]))
    if(i+1)%4==2:
        y1.append(float(string[i]))
    if(i+1)%4==3:
        y2.append(float(string[i]))
    if(i+1)%4==0:
        y3.append(float(string[i]))

new_x=np.arange(x[0],x[-1],0.1)
y1_smooth = interpolate.interp1d(x,y1,'cubic')
y2_smooth = interpolate.interp1d(x,y2,'cubic')
y3_smooth = interpolate.interp1d(x,y3,'cubic')
m=find_max(y1,y2,y3)
plt.axis([x[0],x[-1],0,m])
        
plt.title("График")
plt.xlabel("Длина поисковой строки")
plt.ylabel("Время поиска")
line_1, line_2, line_3 = plt.plot(new_x,y1_smooth(new_x), new_x,y2_smooth(new_x),new_x,y3_smooth(new_x))
plt.legend( (line_1,line_2,line_3), ('Rabin-Karp', 'KMP', 'Naive'),loc = 'best')
plt.show()
