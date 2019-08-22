# By Ugne Aleknaviciute 1402147
# Written using PyCharm
from random import randint
import  copy
#------------------------------Agent definition-------------
"""
dir can be equal to 0 - north  1 - east 2 - south 3 - west
"""


def generateDirection():
    return randint(0, 3)


class Agent:
    def __init__(self):
        self.dir        = generateDirection()
        self. walked    = 0
        self.health     = 10
        self.knownTrees = []
        self.turned     = 0
        self.memory     = []
        self.moves      = []

    def turnLeft(self):
        self.dir = (self.dir + 3) % 4

    def turnRight(self):
        self.dir = (self.dir + 1) % 4

    def moveForward(self, y, x):
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
        if self.dir == 0  and y != 0 and environment[y - 1][x] == '-':
            return y - 1, x
        elif self.dir == 2 and y != enviSize - 1 and environment[y + 1][x] == '-':
            return y + 1, x
        elif self.dir == 1 and x != enviSize - 1 and environment[y][x + 1] == '-':
            return y, x + 1
        elif self.dir == 3 and x != 0 and environment[y][x - 1] == '-':
            return y, x - 1
        else:
            return y, x


    def deductLife(self):
        self.health -= 1

    def isAlive(self):
        return self.health > 0

    def eatFruit(self, tree):
        self.health += tree.effect

#------------------------------Tree definition----------------
class Tree:
    def __init__(self):
        self.type = randint(0, 10)

        if(self.type == 0):
            self.effect = -5

        elif(self.type == 1):
            self.effect = -4

        elif(self.type == 2):
            self.effect = -3

        elif(self.type == 3):
            self.effect = -2

        elif(self.type == 4):
            self.effect = -1

        elif(self.type == 5):
            self.effect = 0

        elif(self.type == 6):
            self.effect = 1

        elif(self.type == 7):
            self.effect = 2

        elif(self.type == 8):
            self.effect = 3

        elif(self.type == 9):
            self.effect = 4

        elif(self.type == 10):
            self.effect = 5


#--------------------environment definition----------------
def newPosition(r):
    for i in range(0, 10):
        for j in range(0, 10):
            if (environment[i][j] == '-'):
                environment[i][j] = r
                return i, j

def treeAt(y, x):
    return trees[y][x]

enviSize = 10
environment = [['-' for x in range(enviSize)] for y in range(enviSize)]
trees       = [[Tree() for b in range(enviSize)] for c in range(enviSize)]
tick = 0
maxTicks = 15
robots = [Agent() for a in range(5)]
#-----------------------Main-----------------------------

for r in robots:
    i = randint(0,9)
    j = randint(0,9)
    if(environment[i][j] == "-"):
        environment[i][j] = r
    else:
        i,j = newPosition(r)
        environment[i][j] = r




while(tick < maxTicks):
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

    print("Life levels:")
    for a in range(0, len(found),3):
        print (found[a].health)
    print()
    print("Memory:")
    for a in range(0, len(found),3):
        print (found[a].memory)
    #agents' behaviour--------------------------------------------------
    """
    for every agent in the environment
        reduce its life level by one
        if it is still alive
            if tree at the current square is a known tree
                if it has positive effect
                    eat it
                else if the effect is negative
                    look at the trees around (starting by the one ahead and looking clockwise)
                    if the tree is unknown and the square is empty
                        walk to that square
                    else
                        turn to look at another tree
            else if tree is not known
                eat it and note its effect in knownTrees array
    """
    for a in range(0, len(found), 3):
        found[a].deductLife()
        if found[a].isAlive():
            currTree = treeAt(found[a + 1], found[a + 2])
            if currTree in found[a].knownTrees:
                if currTree.effect > 0:
                    found[a].eatFruit(currTree)
                    temp = copy.deepcopy(found[a].moves)
                    found[a].memory.append([temp, currTree.effect])
                else:
                    oldY = found[a + 1]
                    oldX = found[a + 2]
                    newY, newX = found[a].lookAhead(found[a + 1], found[a + 2])
                    if found[a].turned != 3:
                        if treeAt(newY, newY) in found[a].knownTrees:   #if tree ahead is known (meaning it is negative)
                            found[a].turnRight()
                            found[a].turned += 1
                            found[a].moves.append(1)
                            temp = copy.deepcopy(found[a].moves)
                            found[a].memory.append([temp, currTree.effect])
                        elif oldY == newY and oldX == newX:             #if a wall or taken square
                            found[a].turnRight()
                            found[a].turned += 1
                            found[a].moves.append(1)
                            temp = copy.deepcopy(found[a].moves)
                            found[a].memory.append([temp, currTree.effect])
                        elif not(treeAt(newY, newY) in found[a].knownTrees):    #if unknown tree is found
                            found[a].moveForward(oldY, oldX)
                            found[a].turned = 0
                            found[a].moves.append(0)
                            temp = copy.deepcopy(found[a].moves)
                            found[a].memory.append([temp])
                        else:
                            found[a].turnRight()
                            found[a].turned += 1
                            found[a].moves.append(1)
                            temp = copy.deepcopy(found[a].moves)
                            found[a].memory.append([temp, currTree.effect])
                    elif oldY == newY and oldX == newX:
                        found[a].turnRight()
                        found[a].moves.append(1)
                        found[a].memory.append([temp, currTree.effect])
                    elif not(oldY == newY and oldX == newX):
                        found[a].moveForward(oldY, oldX)
                        found[a].turned = 0
                        found[a].moves.append(0)
                        temp = copy.deepcopy(found[a].moves)
                        found[a].memory.append([temp, currTree.effect])
            else:
                found[a].eatFruit(currTree)
                found[a].knownTrees.append(currTree)
                temp = copy.deepcopy(found[a].moves)
                found[a].memory.append([temp, currTree.effect])
        else:
            environment[found[a + 1]][found[a + 2]] = '-'
    #agent behaviours end-----------------------------------------------
    tick += 1
    print()


print(tick)
found = []
for i in range (0, 10):
    for j in range (0, 10):
        if isinstance(environment[i][j], Agent):
            found.append(environment[i][j])
            found.append(i)
            found.append(j)
            print (environment[i][j].dir, end = " ")

        else:
            print (environment[i][j], end = " ")
    print()

print("Life levels:")
for a in range(0, len(found),3):
    print (found[a].health)
print()
print("Memory:")
for a in range(0, len(found),3):
    print (found[a].memory)