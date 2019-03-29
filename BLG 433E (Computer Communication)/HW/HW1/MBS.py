#########################
#       150130032       #
#       Baran Kaya      #
#########################

from socket import *
import re
#re -> for spliting messages at ':'

MBS_PORT = 12345

serverSocket = socket(AF_INET, SOCK_DGRAM)

serverSocket.bind(('', MBS_PORT))

#User & password list - 20 users
class User:
       username = ""
       password = ""
       def __init__(self, name, pw):
               self.username = name
               self.password = pw
#User list for storing registered users as a list
UserList = []

#Message Board
class messageBoard:
        #boardName = ""
        #msg_owner = []
        #messages = []
        def __init__(self, name):
                self.boardName = name
                self.msg_owner = []
                self.messages = []
        def add_msg(self, owner, content):
                self.msg_owner.append(owner)
                self.messages.append(content)
#messageBoards list for storing created message boards
messageBoards = []

print ("MBS started...")

#Infinite loop
while True:
        message, clientAddress = serverSocket.recvfrom(2048)
        messageStr = message.decode('utf-8') #Byte to str

        # Get message's code (e.g REG, CREATE)
        splitMessage = messageStr.split(':')

        #REG - Register new user
        if splitMessage[0] == "REG":
                #If code is REG then splitMessage[1] is USER_NAME and splitMessage[1] is PASSWORD
                USER_NAME = splitMessage[1]
                PASSWORD = splitMessage[2]
                print ("Registiration request arrived from user " + splitMessage[1])

                emptyList = False
                foundUser = False
                foundUserNPw = False
                if not UserList:
                        emptyList = True
                else:
                        for item in UserList:
                                #Search for username
                                if item.username == USER_NAME:
                                        foundUser = True
                                        #Check password
                                        if item.password == PASSWORD:
                                                foundUserNPw = True

                #No users OR not found username OR username with same password
                if emptyList or not foundUser or foundUserNPw:
                        msg = "ACCEPT:" + USER_NAME
                        serverSocket.sendto(msg.encode('utf-8'), clientAddress)
                        if not foundUser:
                                UserList.append(User(USER_NAME, PASSWORD))
                        print ("Successful user registration: " + USER_NAME)
                #Found username with different password
                elif foundUser and not foundUserNPw:
                        msg = "REJECT:" + USER_NAME
                        serverSocket.sendto(msg.encode('utf-8'), clientAddress)
                        print ("Rejected user registration: " + USER_NAME)

        # CREATE - User creates new message board
        elif splitMessage[0] == "CREATE":

                BOARD_NAME = splitMessage[1]
                emptyBoard = False
                foundBoardName = False

                #Search for board name if it already exists
                if not messageBoards:
                        emptyBoard = True
                else:
                        for item in messageBoards:
                                if item.boardName == BOARD_NAME:
                                        foundBoardName = True

                #If board name couldn't find then create message board
                if emptyBoard or not foundBoardName:
                        msg = "ACCEPT:" + BOARD_NAME
                        print (BOARD_NAME + " Message Board Was Created!")
                        #Create message board and add it to the messageBoards list
                        messageBoards.append(messageBoard(BOARD_NAME))

                #If board name already exists
                elif foundBoardName:
                        msg = "REJECT:" + BOARD_NAME
                        print (BOARD_NAME + " Message Board Couldn't Be Created!")
                #Send accepted or rejected message to the client
                serverSocket.sendto(msg.encode('utf-8'), clientAddress)

        #LIST - User lists message boards or message contents
        elif splitMessage[0] == "LIST":

                #LIST:BOARDS - List message boards
                if splitMessage[1] == "BOARDS":
                        #Message's first codes
                        msg = "LIST:BOARDS"
                        #If there are message boards, add board names to the msg
                        if messageBoards:
                                for item in messageBoards:
                                        msg += ":"
                                        msg += item.boardName
                        #Empty message boards
                        else:
                                msg += ":" #add : to the end -> "LIST:BOARDS:"
                        print("Sending message to the client: " + msg)
                        serverSocket.sendto(msg.encode('utf-8'), clientAddress)


                #LIST:MESSAGES - List message contents
                elif splitMessage[1] == "MESSAGES":
                        validUNnP = False
                        validBoard = False
                        currentUser = "Invalid_user"

                        # Check username and password from user list
                        for user in UserList:
                                if splitMessage[2] == user.username and splitMessage[3] == user.password:
                                        validUNnP = True
                                        currentUser = user.username
                                        break
                        # Check message boards for that name exists or not
                        if messageBoards:
                                for item in messageBoards:
                                        if item.boardName == splitMessage[4]:
                                                validBoard = True
                                                listThatBoard = item
                                                break

                        #If they both valid, send messages to the client
                        if validUNnP and validBoard:
                                #Message num is equal to messages lists size
                                MESSAGE_NUM = len(listThatBoard.messages)
                                #If there are messages on that board send them
                                if MESSAGE_NUM != 0:
                                        for i in range (0, MESSAGE_NUM):
                                                msg = "MESSAGE:" + listThatBoard.boardName + ":" + listThatBoard.msg_owner[i] +  ":" + str(i+1) + ":" + listThatBoard.messages[i]
                                                print("Sending message to the client" + currentUser + ": " + msg)
                                                serverSocket.sendto(msg.encode('utf-8'), clientAddress)
                                #End message -> MESSAGE_NUM = -1
                                msg = "MESSAGE:" + listThatBoard.boardName + ":" + currentUser + ":-1:"
                                print("Sending message to the client" + currentUser + ": " + msg)
                                serverSocket.sendto(msg.encode('utf-8'), clientAddress)

                        #If one of the username/password or board name is not valid
                        else:
                                msg = "REJECT:"
                                # add username
                                if validUNnP:
                                        msg += currentUser
                                msg += ":"
                                # add board name
                                if validBoard:
                                        msg += listThatBoard.boardName
                                # Send rejected message to the client -> REJECT:USER_NAME:BOARD_NAME
                                print("Sending message to the client: " + msg)
                                serverSocket.sendto(msg.encode('utf-8'), clientAddress)




                #Invalid list operation
                else:
                        print("Invalid list operation.")

        # ADD - User adds new message content
        elif splitMessage[0] == "ADD":

                validUNnP = False
                validBoard = False
                currentUser = "Invalid_user"

                #Check username and password
                for user in UserList:
                        if splitMessage[1] == user.username and splitMessage[2] == user.password:
                                validUNnP = True
                                currentUser = user.username
                                break
                #Check message boards for that name exists or not
                if messageBoards:
                        for item in messageBoards:
                                if item.boardName == splitMessage[3]:
                                        validBoard = True
                                        addThatBoard = item
                                        break

                #If they both valid, add message to the board
                if validUNnP and validBoard:
                        msg = "ACCEPT:" + splitMessage[1] + ":" + splitMessage[3] + ":" + splitMessage[4]
                        print(currentUser + " added the message -" + splitMessage[4] + "- on " + addThatBoard.boardName + " Message board!")
                        #Add message content and the owner to the board
                        addThatBoard.add_msg(currentUser, splitMessage[4])

                # If one of the username/password or board name is not valid
                else:
                        msg = "REJECT:"
                        #add username
                        if validUNnP:
                                msg += currentUser
                        msg += ":"
                        #add board name
                        if validBoard:
                                msg += addThatBoard.boardName
                        msg += ":"
                        #add message content
                        msg += splitMessage[4]
                #Send accepted or rejected message to the client
                print("Sending message to the client: " + msg)
                serverSocket.sendto(msg.encode('utf-8'), clientAddress)

        #Operation code is not valid
        else:
                print("Invalid operation code!")
