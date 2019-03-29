#########################
#       150130032       #
#       Baran Kaya      #
#########################

from socket import *
import re
#re -> for spliting messages at ':'

MBS_ADDRESS = '127.0.0.1'
MBS_PORT = 12345

clientSocket = socket(AF_INET, SOCK_DGRAM)

#-------------REGISTRATION-------------
USER_NAME = input("Username: ")
PASSWORD = input("Password: ")

#Create a message for sending to the server
registirationInfo = "REG:" + USER_NAME + ':' + PASSWORD
regInfoByte = registirationInfo.encode('utf-8') #Str to byte
#Send it to the server
clientSocket.sendto(regInfoByte,(MBS_ADDRESS, MBS_PORT))

#Server's response message
serverRegMsg, serverAddress = clientSocket.recvfrom(2048)
splitRegMsg = serverRegMsg.decode('utf-8').split(':')

# REJECTED server response for registration
if splitRegMsg[0] == "REJECT":
    print ("Rejected user registration: " + splitRegMsg[1])
    clientSocket.close()
    exit()

# ACCEPTED server response for registration
elif splitRegMsg[0] == "ACCEPT":
    print("Successful user registration: " + splitRegMsg[1])
    print("Operations:\nc -> Create message board\nb -> List message boards\na -> Add message content\nm -> List message contents\n0 -> Exit\n")

# INCORRECT server response for registration
else:
    print("Invalid registration response message from server. ")

#-------------OTHER OPERATIONS-------------
loopVariable = True

while loopVariable:

    operation = input("Select Operation: ")

    # CREATE - User creates new message board
    if operation.lower() == 'c':
        print("Create new message board.\n")
        boardName = input("New Message Board Name: ")
        msg = "CREATE:" + boardName
        #Send CREATE message to the server
        clientSocket.sendto(msg.encode('utf-8'), (MBS_ADDRESS, MBS_PORT))
        #Server's response message
        serverCreateMsg, serverAddress = clientSocket.recvfrom(2048)
        splitCreateMsg = serverCreateMsg.decode('utf-8').split(':')
        BOARD_NAME = splitCreateMsg[1]

        # ACCEPTED server response for create a new board
        if splitCreateMsg[0] == "ACCEPT":
            print(BOARD_NAME + " Message Board Was Created!\n")

        # REJECTED server response for create a new board
        elif splitCreateMsg[0] == "REJECT":
            print(BOARD_NAME + " Message Board Couldn't Be Created!\nThere is a message board with same name, try different name.\n")

        # INCORRECT server response for create a new board
        else:
            print("Invalid response message from server for create message board.")

    # LIST:BOARDS - User lists message boards
    elif operation.lower() == 'b':
        print("List message boards.\n")
        msg = "LIST:BOARDS"
        # Send LIST:BOARDS message to the server
        clientSocket.sendto(msg.encode('utf-8'), (MBS_ADDRESS, MBS_PORT))
        # Server's response message
        serverListBoardMsg, serverAddress = clientSocket.recvfrom(2048)
        splitListBoardMsg = serverListBoardMsg.decode('utf-8').split(':')

        # CORRECT server response for list boards
        if splitListBoardMsg[0] == "LIST" and splitListBoardMsg[1] == "BOARDS":

            if splitListBoardMsg[2] == '':
                print("There is no message board.")
            else:
                print("Message board names:")
                for i in range (2, len(splitListBoardMsg) ):
                    print("%d-%s" % (i-1,splitListBoardMsg[i] ))

        # INCORRECT server response for list boards
        else:
            print("Server's response is not valid.")

    # ADD - User adds new message content
    elif operation.lower() == 'a':
        print ("Add new message content to a message board.\n")
        BOARD_NAME = input("Board name to add new message: ")
        MESSAGE_CONTENTS = input("Message content: ")
        msg = "ADD:" + USER_NAME + ":" + PASSWORD + ":" + BOARD_NAME + ":" + MESSAGE_CONTENTS
        # Send ADD message to the server
        clientSocket.sendto(msg.encode('utf-8'), (MBS_ADDRESS, MBS_PORT))
        # Server's response message
        serverAddMsg, serverAddress = clientSocket.recvfrom(2048)
        splitAddMsg = serverAddMsg.decode('utf-8').split(':')

        # ACCEPTED server response for add message
        if splitAddMsg[0] == "ACCEPT":
            print("Message successfully added!")

        # REJECTED server response for add message
        elif splitAddMsg[0] == "REJECT":
            #Invalid username/password OR Invalid username/password AND invalid boardname
            if splitAddMsg[1] == '':
                print("Invalid username/password")
                #Check for validity of board name
                if splitAddMsg[2] == '':
                    print(" and board name!")
            #Username/password valid BUT boardname invalid
            elif splitAddMsg[2] == '':
                print ("Invalid message board name!")
            else:
                print("Invalid add message - reject response from server.")

        # INCORRECT server response for add message
        else:
            print("Invalid add message response from server.")

    # LIST:MESSAGES - List message contents
    elif operation.lower() == 'm':
        print ("List message contents.\n")
        BOARD_NAME = input("Board name to see messages: ")
        msg = "LIST:MESSAGES:" + USER_NAME + ":" + PASSWORD + ":" + BOARD_NAME
        # Send LIST:MESSAGES message to the server
        clientSocket.sendto(msg.encode('utf-8'), (MBS_ADDRESS, MBS_PORT))
        # Server's response message
        serverListMsgsMsg, serverAddress = clientSocket.recvfrom(2048)
        splitListMsgsMsg = serverListMsgsMsg.decode('utf-8').split(':')

        # REJECTED server response for list messages
        if splitListMsgsMsg[0] == "REJECT":
            #Invalid username/password OR Invalid username/password AND invalid boardname
            if splitListMsgsMsg[1] == '':
                print("Invalid username/password")
                # Check for validity of board name
                if splitListMsgsMsg[2] == '':
                    print(" and board name!")
            #Username/password valid BUT boardname invalid
            elif splitListMsgsMsg[2] == '':
                print ("Invalid message board name!")
            else:
                print("Invalid add message - reject response from server.")

        # ACCEPTED server response for list messages
        elif splitListMsgsMsg[0] == "MESSAGE":
            #If there is no message in that message board -> MESSAGE_NUM = -1
            if splitListMsgsMsg[3] == "-1":
                print("There is no message in that message board.")
            #There are messages in that message board
            else:
                #Print first message
                print(splitListMsgsMsg[3] + "-Owner:" + splitListMsgsMsg[2] + " -Msg:" + splitListMsgsMsg[4])
                #Server still sending messages, get them within infinite loop
                while True:
                    messageContent, serverAddress = clientSocket.recvfrom(2048)
                    splitMsgContent = messageContent.decode('utf-8').split(':')
                    #Check if the message is the last message - stop the loop
                    if splitMsgContent[3] == "-1":
                        break
                    else:
                        print(splitMsgContent[3] + "-Owner:" + splitMsgContent[2] + "-Msg:" + splitMsgContent[4])

        # INCORRECT server response for list messages
        else:
            print("Invalid add message response from server.")



    #TERMINATE loop and exit
    else:
        loopVariable = False

clientSocket.close()
exit()
