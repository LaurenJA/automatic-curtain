from django.db import models
from django import forms

# Create your models here.

class Type(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = 0

    def __str__(self):
        return self.name


class SetOpentime(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = models.CharField(max_length=128, unique=True)
    x = 0

    def __str__(self):
        return self.name

class SetClosetime(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = models.CharField(max_length=128, unique=True)
    x = 0

    def __str__(self):
        return self.name
