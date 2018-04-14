from django.shortcuts import render
import socket
from interface.models import Type,SetClosetime,SetOpentime



def home(request):
    context_dict ={}
    count = Type.mode                       # To determine the mode of the system, if this is not the first time to visit the home page.
                                            # 0 is not choose yet, 1 is choose Auto mode, 2 is choose Manual mode
    if count == 1:                          # If this is not the first time, then the mode will be transfered automaticlly
        return render(request , 'interface/Auto.html', context_dict )
    if count == 2:
        return render(request , 'interface/Manual.html', context_dict )
    #print (Type.mode)
    return render(request , 'interface/home.html', context_dict )

def Auto(request):
    data = 'auto'                           # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    context_dict ={}

    Type.mode = 1                           # The Type.mode is help to record the status of the mode for the homepage
    return render(request , 'interface/Auto.html', context_dict )

def Manual(request):
    data = 'manual'                         # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    context_dict ={}
    context_dict = check()                  # The retrun value should be set by using the function check()
    Type.mode = 2                           # The Type.mode is help to record the status of the mode for the homepage
    return render(request , 'interface/Manual.html', context_dict )



def open(request):
    data = 'open'                           # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    context_dict = {}
    context_dict = check()                  # The retrun value should be set by using the function check()
    return render(request , 'interface/Manual.html', context_dict)

def close(request):
    data = 'close'                          # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    context_dict = {}
    context_dict = check()                  # The retrun value should be set by using the function check()
    return render(request , 'interface/Manual.html', context_dict)

def stop(request):
    data = 'stop'                           # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    context_dict = {}
    context_dict = check()                  # The retrun value should be set by using the function check()
    return render(request , 'interface/Manual.html', context_dict)


def opentimer(request):

    request.encoding = 'utf-8'
    context_dict = {}
    if 'opentime' in request.GET:           # The request.GET should include 'closetime', if there is a set of the closetimer
        #print(request.GET['closetime'])
        data = request.GET['opentime']      # The data includes the time that is set in the web page
        senddata = 'opentimer' + data       # The senddata inludes the message that will be sent
        send(senddata)                      # Use the send() function to send the message
        SetOpentime.mode = data
        SetOpentime.x = 1                   # 0 means the timer not set yet, 1 is already set
    context_dict = check()                  # The retrun value should be changed by using the function check()
    return render(request , 'interface/Manual.html', context_dict)  #still in the Manual page.


def closetimer(request):

    request.encoding = 'utf-8'
    context_dict = {}
    if 'closetime' in request.GET:          # The request.GET should include 'closetime', if there is a set of the closetimer
        #print(request.GET['closetime'])
        data = request.GET['closetime']     # The data includes the time that is set in the web page
        senddata = 'closetimer' + data      # The senddata inludes the message that will be sent
        send(senddata)                      # Use the send() function to send the message
        SetClosetime.mode = data
        SetClosetime.x = 1                  # 0 means the timer not set yet, 1 is already set

    context_dict = check()                  # The retrun value should be changed by using the function check()
    return render(request, 'interface/Manual.html', context_dict)   #still in the Manual page.

# The function below is used to delete all the timer set.
def deltimer(request):
    data = 'deltimer'                       # The data inludes the message that will be sent
    send(data)                              # Use the send() function to send the message
    # Then set the SetOpentime.x and SetClosetime.x to be zero, Then the retrun value should be changed by using the function check()
    SetOpentime.x = 0                       # 0 means the timer not set yet, 1 is already set
    SetClosetime.x = 0                      # 0 means the timer not set yet, 1 is already set
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)  #still in the Manual page.


# The function below is used to check the status of the timer.
def check():
    # The dictionary context_dict will contain the status of the timers.
    context_dict = {}
    # If the close timer is already set, the SetClosetime.x will be 1
    if SetClosetime.x == 1:
    # Then the return value context_dict['close'] = 1, or it should be 0
        context_dict['close'] = 1
        context_dict['closecontent'] = SetClosetime.mode
    else:
        context_dict['close'] = 0

    # If the open timer is already set, the SetClosetime.x will be 1
    if SetOpentime.x == 1:
    # Then the return value context_dict['open'] = 1, or it should be 0
        context_dict['open'] = 1
        context_dict['opencontent'] = SetOpentime.mode
    else:
        context_dict['open'] = 0
    return context_dict

# The function below is used to send the message to the control programme by using udp
def send(data):
    # The address below is the address that the message will be sent to
    address = ('192.168.1.183',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(bytes(data,'utf-8'),address)
    s.close()
    #print("sent close")
