import math
import string
f = open("sinerom.mem","w") #'w' creates sinerom.mem or overwrites it if alr exists
for i in range(256): #2**8 elements
    #2π * i/256 converts position i to angle in radians 
    # *127 scales to between -127 to 127
    # +127 shift wave upward to between 0 to 254
    v = int(math.cos(2*3.1416*i/256)*127+127) #127cos(2πi/256) + 127

    if (i+1)%16 == 0: #every 16th element
        #placeholder format: hex = name of placeholder format
        # #2 = min no. of character (e.g. if '5' then ' 5')
        # #X = uppercase hex letters
        s = "{hex:2X}\n" #after every 16 elements, insert a newline
    else:
        s = "{hex:2X} " #space between each element

    #passes in decimal val to be converted to hex 
    #written into sinerom.mem
    f.write(s.format(hex=v))

f.close()