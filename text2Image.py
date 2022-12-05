import cv2
import numpy as np

n = 8
filename=open("output.txt","r")
outputimage = np.zeros([n,n,3])


#create checkerboard
count = 0
for i in range(n):
    for j in range(n):
        if (count % 2) == 0:
            outputimage[i][j] = (74, 139, 184) #white square
        else:
            outputimage[i][j]= (111,193,227) #black square
        count += 1
    count += 1

#replace Q with red square
linecount = 0
for line in filename:
    linesplit = line.strip().split()
    charcount = 0
    for x in linesplit:
        if x == "Q":
            outputimage[linecount][charcount] = (0,0,255) #red
        charcount+=1
    linecount+=1

outputimage = rescaled = cv2.resize(outputimage, (1000, 1000), interpolation = cv2.INTER_AREA)

cv2.imwrite(str(n)+ "_queens" + ".jpg",outputimage)
filename.close()