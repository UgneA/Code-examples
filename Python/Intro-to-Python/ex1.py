"""
ex1.py
created by Ugne Aleknaviciute
"""
import operator 

#--------------------------------func1---------------------------------------
def studCre() :
        """
        creates and returns a tuple containing details of the student
        returns a tuple with information about student
        """
              
        studStr=studLine.split()
        
        regNo   = studStr[0]
        year    = studStr[1]
        course  = studStr[2]
        surN    = studStr[-1]
        firNsub = studStr[3:-1]
        firN    = ' '.join(firNsub)
        
        myTup=(regNo,year,course,firN,surN) 
                   
        return myTup
    
#----------------------------------func2-------------------------------------
def studDet(studList) :
    """
    prints the details of a student
    prints and returns information about students
    argument: studList: list of tuples
    """
    
    for tup in studList :
       print(formating (tup))    
        
    return formating (tup)
#-------------------------------formating function----------------------------
def formating (tup):
        """
        forms and returns information about students in requested format
        argument: tup: tuple
        """
        regNo,year,course,firN,surN = tup
        name = surN+", "+firN
        x = format(name,"32s")+format(regNo,"7s")+\
                  format(course,"6s")+"Year "+year
        return x
#---------------------------------mainBody-----------------------------------
#tries to open file and read lines from it.
fileN=input("Write a file name from which you wish to read information: ")

try :
    f=open(fileN) 
    studLine  = f.readline()
    studList  = []
    studList2 = []
    while (len(studLine)>0) :
        studList.append(studCre())
        studList2.append(studCre())
        studLine=f.readline()
    studDet(studList)
    studList2 = sorted(studList2, key=operator.itemgetter(4,3))
#------------------------------LoopForRequests-------------------------------
    running = True
    while running :
        line = input("\nIf you want information about student(s):\nWith particular \
degree scheme write 1,\nWith year in particular range write 2,\n\
With particular registration number write 3\nTo quit write 0: ")
       
        if line == "0" : running = False
        
        elif "1"<=line<="3" :
                
            #---------------------degreeScheme----------------------------------
            #searches list for students with certain degree scheme
            if line== "1" :
                degSc=input("Write student's degree scheme: ")
                n=0
                for tup in studList2 : 
                       if degSc == tup[2]  :
                            print(formating(tup))
                       elif (degSc != tup) and n==len(studList2)-1 :
                            print ("There is no such degree scheme - try again")
                       elif degSc != tup:
                                n+=1
            #--------------------------yearRange--------------------------------                    
            #searches list for students in certain year range
            elif line=="2" :
                yearLo=input("Write upper and then lower bounds \
of the year range:\n")
                yearUp=input()
                n=0
                for tup in studList :
                        if yearLo<=tup[1]<=yearUp  and "1"<=yearUp<="4" and "1"<=yearLo<="4" :
                             print(formating(tup))
                             
                        elif   n==len(studList)-1 :
                             print("Invalid year range - try again")
                        else :
                             n+=1
                            
            #------------------------registrationNumber-------------------------    
            #searches list for a student with certain registration number
            elif line=="3" :
                regNum=input("Write student's registration number: ")
                n=0
                for tup in studList :
                        if regNum == tup[0]  :
                                a,b,c,firN,surN = tup
                                name = firN+" "+surN
                                print(name)
                             
                        elif (regNum != tup) and n==len(studList)-1 :
                            print ("There is no such registration \
number - try again")
                        elif regNum != tup:
                                n+=1
                                
            #Message that is dispalyed if user provides invalid input------------        
        else : print("Invalid input - try again.\n")
#------------------------------------fileCloses----------------------------------
    f.close
    
except IOError as e :
    print("Problem opening file")


    






