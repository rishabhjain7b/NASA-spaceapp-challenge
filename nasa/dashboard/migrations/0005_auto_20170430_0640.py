# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2017-04-30 06:40
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('dashboard', '0004_userappliances_user'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='userappliances',
            options={'verbose_name': 'Appliance', 'verbose_name_plural': 'Appliances'},
        ),
    ]