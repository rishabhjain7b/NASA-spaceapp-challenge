# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.contrib.auth import (
    authenticate,
    get_user_model,
    login,
    logout,
)
from django.conf import settings

User = get_user_model()
# Create your models here.


class UserAppliances(models.Model):
	id = models.AutoField(primary_key=True)
	user = models.ForeignKey(settings.AUTH_USER_MODEL, null=True, blank=True)
	name = models.CharField(max_length=120, null=False, blank=False)
	qty = models.IntegerField()
	value = models.DecimalField(decimal_places=3, max_digits=20)

	def __unicode__(self):
		return self.name

	class Meta:
		verbose_name='Appliance'
		verbose_name_plural='Appliances'

