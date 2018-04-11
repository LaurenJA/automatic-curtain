from django.conf.urls import url
from interface import views


urlpatterns = [
    url(r'^$', views.home, name='home'),
    url(r'^Auto/', views.Auto, name='auto'),
    url(r'^Manual/', views.Manual, name='manual'),
    url(r'^Open/',views.open, name='open'),
    url(r'^Close/',views.close, name='close'),
    url(r'^Stop/',views.stop, name='stop'),
    url(r'^Opentimer/',views.opentimer, name='opentimer'),
    url(r'^Closetimer/',views.closetimer, name='closetimer'),
    url(r'^Deltimer/',views.deltimer, name='deltimer'),
]