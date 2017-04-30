# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render,redirect

# Create your views here.

import json,requests,urllib

from .models import UserAppliances

def dashboard(request):

	if request.method=="POST":
		data = request.POST
		print(data)
		data1 = dict(data.iterlists())
		try:
			if data1['fan'][0] == 'on':
				print("hello")
				value = data1['fan'][1]
				qty = data1['fan'][2]
				obj = UserAppliances()
				obj.user = request.user
				obj.name = 'fan'
				obj.qty = qty
				obj.value = value
				obj.save()

			else:
				pass	
		except:
			pass

		try:
			if data1['CFL'][0] == 'on':
				print("hello")
				value = data1['CFL'][1]
				qty = data1['CFL'][2]
				obj = UserAppliances()
				obj.user = request.user
				obj.name = 'CFL'
				obj.qty = qty
				obj.value = value
				obj.save()

			else:
				pass	
		except:
			pass


		try:
			if data1['tubelight'][0] == 'on':
				print("hello")
				value = data1['tubelight'][1]
				qty = data1['tubelight'][2]
				obj = UserAppliances()
				obj.user = request.user
				obj.name = 'tubelight'
				obj.qty = qty
				obj.value = value
				obj.save()

			else:
				pass	
		except:
			pass




		return redirect('/')

	else:
		context = {}
		user = request.user
		print str(user)
		context = {
			"user":user
			}
	
		return render(request, "index.html", context)


def DashboardShow(request):
	url = 'https://api.thingspeak.com/channels/210679/fields/1.json?results=2'
	output = json.load(urllib.urlopen(url))
	print(output)
	output = output['feeds']
	for i in output:
		data = i
		value = str(data['field1'])

	context = {
		"value":value
	}

	return render(request, "index2.html", context)