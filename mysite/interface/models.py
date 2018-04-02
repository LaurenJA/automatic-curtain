from django.db import models


# Create your models here.

class Type(models.Model):
    name = models.CharField(max_length=128, unique=True)
    mode = 0

    def __str__(self):
        return self.name


class Status(models.Model):
    title = models.CharField(max_length=128)
    condition = 0

    def __str__(self):
        return self.title
