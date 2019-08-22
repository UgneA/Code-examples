"""
ex2.py
game hangman
created by Ugne Aleknaviciute
"""

import random

#--------------------------1stFunction----------------------------------------------
def makeDict(secretW,liv): 
    """
    generates and returns a dictionary object
    argument: secretW: string
    argument: liv: integer
    returns dictionary object
    """
    
    sw = []
    for i in secretW :
        if i!="\n":
            sw.append(i)
        
    cw = []
    for i in secretW :
        if i!="\n":
            cw.append("*")
        
    rl = liv
    
    wordLives = {"secrWord":sw,"currWord":cw,"remLives":rl}
    return wordLives

#------------------------2ndFunction------------------------------------------------
def guessed(wordLives) :
    """
    checks whether the word is guessed
    argument: wordLives: dictionary object
    returns boolean value
    """
    list1=wordLives.get("secrWord")
    list2=wordLives.get("currWord")
    n=0
    for i in range(0,len(list1)):
        if list1[i] == list2[i] : n+=1 
        else : n=n
    if n==len(list1) : return True
    else : return False
        
#------------------------3rdFunction-------------------------------------------------
def livesLeft(wordLives) :
    """
    from a dictionary object returns the value of lives that are left
    argument: wordLives: dictionary object
    returns integer representing remaining lives
    """
    lives=wordLives.get("remLives")
    return lives

#------------------------4thFunction-------------------------------------------------
def secretWo(wordLives) :
    """
    from a dictionary object returns the value of a secret word
    argument: wordLives: dictionary object
    returns list containing letters of secret word
    """
    word=wordLives.get("secrWord")
    return word

#------------------------5thFunction-------------------------------------------------
def currState(wordLives) :
    """
    makes and returns a game state string
    argument: wordLives: dictionary object
    returns game state string
    """
    
    currWoStr = ''.join(wordLives.get("currWord"))
    gameState = "WORD: "+str(currWoStr)+'; '+'you have '+str(wordLives.get\
        ("remLives"))+' life/lives left\n'
    return gameState

#------------------------6thFunction-------------------------------------------------
def updCurrS(wordLives,lett):
    """
    updates game state values
    argument: wordLives: dictionary object
    argument: lett: string
    returns letter occurances
    """
    list1 = wordLives.get("secrWord")
    list2 = wordLives.get("currWord")
    lives = wordLives.get("remLives")
    occs=0
    n=0
#checks  if letter occurs in a word
    for i in range(0,len(list1)):
        
        if lett in list1[i]  :
            occs +=1
            list2[i]=lett
            
        elif occs>0 and i ==len(list1)-1  :
            print("The letter "+str(lett)+" occurs "+str(occs)+\
                  " time/times in the word\n")
            
        elif lett not in list1[i] and n==len(list1)-1 :
            print("The letter "+str(lett)+" does not occur in the word\n")
            wordLives["remLives"]=wordLives["remLives"]-1
            
        else : n += 1
        
    
    return occs
#------------------playGameFunction------------------------------------------
def playGame(secretW, liv):
    """
    uses all other functions to manipulate current guess and print game result
    argument: secretW: string
    argument: liv: integer
    """
    
    wordLiv = makeDict(secretW,liv)
   
    while livesLeft(wordLiv)>0 and not guessed(wordLiv):
        
       print(currState(wordLiv))
       
       letter=input("Guess a letter: ")
       
       if len(letter) == 1 and letter.isupper() == True :
           updCurrS (wordLiv,letter)
           
       elif len(letter) != 1 or letter.isupper() == False:
           print("Invalid input")
#game result message    
    if guessed and livesLeft(wordLiv)>0:
        res=currState(wordLiv).split(';')
        print(format(res[0]))
        print("Well done – you have guessed the word correctly\n")
    else :
        print("You have no lives left – you have been hung!")
        print("The word was "+str("".join(secretWo(wordLiv))))
#------------------MainBody----------------------------------------------------
#tries to open file and read lines from it.
filename=input("Write a file name: ")
try:
   f=open(filename)
   wList=[]
   rLine=f.readline()
   while (len(rLine)>0):
       wList.append(rLine)
       rLine=f.readline()
#--------------------Loop-------------------------------------------------------
   running = True
   while running :
#asks user to choose difficulty level        
        level=input("Choose level.\nFor easy level type'1'\nFor intermediate \
level type '2'\nFor hard level type '3' :\n")
        
        if  level =="1" :
            liv = 10
            
        elif level =="2" :
            liv = 7
            
        elif level =="3" :
            liv = 5
            
        else : print("Invalid input - try again")
#generates a random word              
        x=wList
        n=random.randrange(0,len(wList))
        secretW=wList[n]
       
        playGame(secretW, liv)
        
        playOrQ=input("If you want to play again type '1'\nIf you want \
to quit type '0'\n")
        if   playOrQ == "1" :running = True
        elif playOrQ == "0" : running = False
        else: print("Invalid input")
#---------------------------------------------------------------------------------   
except IOError as e:
   print("Problem opening file")
