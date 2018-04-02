from django.shortcuts import render
from dwebsocket.decorators import accept_websocket, require_websocket
from django.http import HttpResponse
import paramiko
import socket
from interface.models import Type, Status

# Create your views here.

def home(request):
    context_dict ={}
    count = Type.mode
    context_dict['count'] = count
    if count == 1:
        return render(request , 'interface/Auto.html', context_dict )
    if count == 2:
        Status.condition = 0
        account = Status.condition
        context_dict['account'] = account
        return render(request , 'interface/Manual.html', context_dict )
    #print (Type.mode)
    return render(request , 'interface/home.html', context_dict )

def Auto(request):
    address = ('192.168.1.16',10000)
    addr = ('127.0.0.1',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = 'auto'
    #s.sendto(bytes(data,'utf-8'),address)
    s.sendto(bytes(data,'utf-8'),addr)
    s.close()

    #print("sent close")
    context_dict ={}

    Type.mode = 1
    return render(request , 'interface/Auto.html', context_dict )

def Manual(request):
    address = ('192.168.1.16',10000)
    addr = ('127.0.0.1',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = 'manual'
    #s.sendto(bytes(data,'utf-8'),address)
    s.sendto(bytes(data,'utf-8'),addr)
    s.close()
    #print("sent close")
    context_dict ={}

    Type.mode = 2
    Status.condition = 0
    account = Status.condition
    context_dict['account'] = account
    return render(request , 'interface/Manual.html', context_dict )



def open(request):
    address = ('192.168.1.16',10000)
    addr = ('127.0.0.1',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = 'open'
    #s.sendto(bytes(data,'utf-8'),address)
    s.sendto(bytes(data,'utf-8'),addr)
    s.close()
    #print("sent open")
    context_dict = {}
    Status.condition = 1
    account = Status.condition
    context_dict['account'] = account
    return render(request , 'interface/Manual.html', context_dict)

def close(request):
    address = ('192.168.1.16',10000)
    addr = ('127.0.0.1',10000)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = 'close'
    #s.sendto(bytes(data,'utf-8'),address)
    s.sendto(bytes(data,'utf-8'),addr)
    s.close()
    #print("sent close")
    context_dict = {}
    Status.condition = 2
    account = Status.condition
    context_dict['account'] = account
    return render(request , 'interface/Manual.html', context_dict)
