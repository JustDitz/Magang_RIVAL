import numpy as np
import math
def round_matrix(matriks):
    return [[0.0 if -1e-4 < element < 1e-4 else round(element, 3) for element in r] for r in matriks]

name, tetha_1, tetha_2, tetha_3 = input().split()
tetha = [(int(tetha_1)/180)*math.pi, (int(tetha_2)/180)*math.pi, (int(tetha_3)/180)*math.pi]

match name:
    case "L":
                # alpha | a | d | theta 
        DH_Table = [[90, 0, 5, tetha[0]],
                    [0, 3, 0, tetha[1]],
                    [0, 2, 0, tetha[2]]
                    ]
    case "D":
        DH_Table = [[90, 0, 6, tetha[0]],
                    [0, 3, 0, tetha[1]],
                    [0, 2, 0, tetha[2]]
                    ]


for i in DH_Table:
    print(i)
# Tabel Homogen
i = 0
Homogen0_1 = round_matrix([
    [math.cos(DH_Table[i][3]), -math.sin(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), math.sin(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.cos(DH_Table[i][3])],
    [math.sin(DH_Table[i][3]), math.cos(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), -math.cos(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.sin(DH_Table[i][3])],
    [0, math.sin(math.radians(DH_Table[i][0])), math.cos(math.radians(DH_Table[i][0])), DH_Table[i][2]],
    [0, 0, 0, 1]
])

i+=1
Homogen1_2 = round_matrix([
    [math.cos(DH_Table[i][3]), -math.sin(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), math.sin(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.cos(DH_Table[i][3])],
    [math.sin(DH_Table[i][3]), math.cos(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), -math.cos(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.sin(DH_Table[i][3])],
    [0, math.sin(math.radians(DH_Table[i][0])), math.cos(math.radians(DH_Table[i][0])), DH_Table[i][2]],
    [0, 0, 0, 1]
])

i+=1
Homogen2_3 = round_matrix([
    [math.cos(DH_Table[i][3]), -math.sin(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), math.sin(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.cos(DH_Table[i][3])],
    [math.sin(DH_Table[i][3]), math.cos(DH_Table[i][3]) * math.cos(math.radians(DH_Table[i][0])), -math.cos(DH_Table[i][3]) * math.sin(math.radians(DH_Table[i][0])), DH_Table[i][1] * math.sin(DH_Table[i][3])],
    [0, math.sin(math.radians(DH_Table[i][0])), math.cos(math.radians(DH_Table[i][0])), DH_Table[i][2]],
    [0, 0, 0, 1]
])
    
Homogen0_2 = np.dot(Homogen0_1, Homogen1_2)
Homogen0_3 = np.dot(Homogen0_2, Homogen2_3)
    
print(round(Homogen0_3[0][3],3))
print(round(Homogen0_3[1][3],3))
print(round(Homogen0_3[2][3],3))