# By Ugne Aleknaviciute 1402147
# Written using PyCharm
from random import randint

#------------------------------Agent definition-------------
"""
dir can be equal to 0 - north  1 - east 2 - south 3 - west
"""

def generateDirection():
    return randint(0, 3)


class Agent:
    def __init__(self):
        self.dir    = generateDirection()
        self. walked = 0

    def turnLeft(self):
        self.dir = (self.dir + 3) % 4

    def turnRight(self):
        self.dir = (self.dir + 1) % 4

    def moveFoward(self, y, x):
        aheadY, aheadX = self.lookAhead(y,x)
        if aheadY == y-1 and aheadX == x:       #north
            environment[y][x] = '-'
            environment[y-1][x] = self
        elif aheadY == y + 1 and aheadX == x:   #south
            environment[y][x] = '-'
            environment[y+1][x] = self
        elif aheadY == y and aheadX == x + 1:   #east
            environment[y][x] = '-'
            environment[y][x+1] = self
        elif aheadY == y and aheadX == x-1:     #west
            environment[y][x] = '-'
            environment[y][x-1] = self

    def lookAhead(self, y, x):
        if  self.dir == 0 and y != 0 and environment[y-1][x] == '-':
            return y-1, x
        elif self.dir == 2 and y != enviSize-1 and environment[y+1][x] == '-':
            return y+1, x
        elif self.dir == 1 and x != enviSize-1 and environment[y][x+1] == '-':
            return y, x+1
        elif self.dir == 3 and x != 0 and environment[y][x-1] == '-':
            return y, x-1
        else:
            return y, x

#--------------------environment definition----------------

def newPosition(r):
    for i in range(0, 10):
        for j in range(0, 10):
            if (environment[i][j] == '-'):
                environment[i][j] = r
                return i, j

tick = 0
maxTicks = 25
enviSize = 10
environment = [['-' for x in range(enviSize)] for y in range(enviSize)]
robots = [Agent() for a in range(10)]
#-----------------------Main-----------------------------

for r in robots:
    i = randint(0,9)
    j = randint(0,9)
    if(environment[i][j] == "-"):
        environment[i][j] = r
    else:
        i,j = newPosition(r)
        environment[i][j] = r



"""
Uncomment rule based or random agent blocks and run the program to see
how they behave
"""
while(tick < maxTicks):
    found = []

    print(tick)
    for i in range (0, 10):
        for j in range (0, 10):
            if(isinstance(environment[i][j], Agent)):
                found.append(environment[i][j])
                found.append(i)
                found.append(j)
                print (environment[i][j].dir, end = " ")

            else:
                print (environment[i][j], end = " ")
        print()

    #-------------------------------random agent----------------------------------
    # for a in range (0, len(found), 3):
    #     action = randint(0,3) # 0-do nothing 1- turn left 2-turn right 3-move forward
    #     if(action == 0):
    #         pass
    #     elif(action == 1):
    #         found[a].turnLeft()
    #     elif(action == 2):
    #         found[a].turnRight()
    #     else:
    #         found[a].moveFoward(found[a+1], found[a+2])
    #random agent end

    #------------------------------rule based agent-------------------------------
    # for a in range(0, len(found), 3):
    #     oldY = found[a + 1]
    #     oldX = found[a + 2]
    #     newY, newX = found[a].lookAhead(found[a + 1], found[a + 2])
    #
    #     if (oldY == newY and oldX == newX) or found[a].walked == 2:
    #         found[a].turnRight()
    #         found[a].walked = 0
    #     elif found[a].walked != 2:
    #         found[a].moveFoward(found[a + 1], found[a + 2])
    #         found[a].walked = (found[a].walked+1)
    #rule based agent end
    tick += 1
    print()


print(tick)
found = []
for i in range (0, 10):
    for j in range (0, 10):
        if(isinstance(environment[i][j], Agent)):
            found.append(environment[i][j])
            found.append(i)
            found.append(j)
            print (environment[i][j].dir, end = " ")

        else:
            print (environment[i][j], end = " ")
    print()