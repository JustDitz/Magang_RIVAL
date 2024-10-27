import math

name = str(input())
kec_rob = []
Roda_TP = 0.15
def lildan(kec_rob):
    print("∇")
    ans = []
    sudut = [(3 * math.pi/4),(3 * math.pi/2),(math.pi / 4)]
    Radius = 0.0635
        
    for i in range(len(kec_rob)):
        vx = int(kec_rob[i][0])
        vy = int(kec_rob[i][1])
        w = int(kec_rob[i][2])
        for j in range(3):
            m = ((math.cos(sudut[j])*vx) + (math.sin(sudut[j])*vy) + Roda_TP*w)/Radius
            ans.append(round(m,2))
    
    for i in ans:
        print(i)
        
def dharmi(kec_rob):
    print("∆")
    ans = []
    sudut = [(7 * math.pi/6),(11 * math.pi/6),(math.pi / 2)]
    Radius = 0.024
        
    for i in range(len(kec_rob)):
        vx = int(kec_rob[i][0])
        vy = int(kec_rob[i][1])
        w = int(kec_rob[i][2])
        for j in range(3):
            m = ((math.cos(sudut[j])*vx) + (math.sin(sudut[j])*vy) + Roda_TP*w)/Radius
            ans.append(round(m,2))
    
    for i in ans:
        print(i)                

    
# Main Program
match name:
    case "LILDAN":
        while True:
            x = input()
            if(x == "GAS"):
                break
            vx,vy,w = map(int, x.split())
            kec_rob.append([vx,vy,w])
        lildan(kec_rob)
    case "DHARMI":
        while True:
            x = input()
            if(x == "GAS"):
                break
            vx,vy,w = map(int, x.split(','))
            kec_rob.append([vx,vy,w])
        dharmi(kec_rob)
    case _:
        print("Error")