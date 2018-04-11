from django.shortcuts import render
from dwebsocket.decorators import accept_websocket, require_websocket
from django.http import HttpResponse
import paramiko
import socket
from interface.models import Type,SetClosetime,SetOpentime

# Create your views here.

def home(request):
    context_dict ={}
    count = Type.mode
    context_dict['count'] = count
    if count == 1:
        return render(request , 'interface/Auto.html', context_dict )
    if count == 2:
        return render(request , 'interface/Manual.html', context_dict )
    #print (Type.mode)
    return render(request , 'interface/home.html', context_dict )

def Auto(request):
    data = 'auto'
    send(data)
    context_dict ={}

    Type.mode = 1
    return render(request , 'interface/Auto.html', context_dict )

def Manual(request):
    data = 'manual'
    send(data)
    context_dict ={}
    context_dict = check()
    Type.mode = 2
    return render(request , 'interface/Manual.html', context_dict )



def open(request):
    data = 'open'
    send(data)
    context_dict = {}
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)

def close(request):
    data = 'close'
    send(data)
    context_dict = {}
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)

def stop(request):
    data = 'stop'
    send(data)
    context_dict = {}
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)


def opentimer(request):

    request.encoding = 'utf-8'
    context_dict = {}
    if 'opentime' in request.GET:
        print(request.GET['opentime'])
        data = request.GET['opentime']
        senddata = 'opentimer' + data
        send(senddata)
        SetOpentime.mode = data
        SetOpentime.x = 1
    else:
        context_dict['open'] = 0
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)


def closetimer(request):

    request.encoding = 'utf-8'
    context_dict = {}
    if 'closetime' in request.GET:
        print(request.GET['closetime'])
        data = request.GET['closetime']
        senddata = 'closetimer' + data
        send(senddata)
        SetClosetime.mode = data
        SetClosetime.x = 1
    else:
        context_dict['close'] = 0

    context_dict = check()
    return render(request, 'interface/Manual.html', context_dict)

def deltimer(request):
    data = 'deltimer'
    send(data)
    SetOpentime.x = 0
    SetClosetime.x = 0
    context_dict = check()
    return render(request , 'interface/Manual.html', context_dict)



def check():
    context_dict = {}
    if SetClosetime.x == 1:
        context_dict['close'] = 1
        context_dict['closecontent'] = SetClosetime.mode
    else:
        context_dict['close'] = 0

    if SetOpentime.x == 1:
        context_dict['open'] = 1
        context_dict['opencontent'] = SetOpentime.mode
    else:
        context_dict['open'] = 0
    return context_dict

def send(data):
    address = ('192.168.1.16',10000)
    addr = ('127.0.0.1',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #s.sendto(bytes(data,'utf-8'),address)
    s.sendto(bytes(data,'utf-8'),addr)
    s.close()
    #print("sent close")
