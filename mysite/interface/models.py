from django.db import models
from django import forms

# The type function records the status of control mode
class Type(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = 0        # 0 is not choose yet, 1 is choose Auto mode, 2 is choose Manual mode

    def __str__(self):
        return self.name

# The type function records the status of open timer
class SetOpentime(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = models.CharField(max_length=128, unique=True)    # record the time, if it is set
    x = 0                                                   # 0 means the timer not set yet, 1 is already set

    def __str__(self):
        return self.name

class SetClosetime(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = models.CharField(max_length=128, unique=True)    # record the time, if it is set
    x = 0                                                   # 0 means the timer not set yet, 1 is already set

    def __str__(self):
        return self.name
