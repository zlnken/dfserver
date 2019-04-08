# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.
from django.contrib import admin
from django.shortcuts import render
from django import forms
import sys
sys.path.append("../")
from common import Config
# -*- coding: utf-8 -*-

class RolePage(forms.Form):
	ip_addr = forms.CharField(max_length = 64,
	widget=forms.Select(
		choices = Config.IpAddrDatas,
		attrs={
                "class": "form-control",
                "style": "width:100%"
            }
        ),
		required=False,
		label = "选择数据库"

	)

	role_id = forms.CharField(max_length = 32, label = "角色ID",widget=forms.TextInput(
		attrs={'class': 'form-control', "style": "width:98%"}))

	
	role_values = forms.CharField(max_length = 64, 
	widget=forms.Select(
		choices = Config.RoleValues,
		attrs={
                "class": "form-control",
                "style": "width:100%"
            }
        ),
		required=False,
		label = "单一数据"
	)


	role_objects = forms.CharField(max_length = 64, 
	widget=forms.Select(
		choices = Config.ObjectValues,
		attrs={
                "class": "form-control",
                "style": "width:100%"
            }
        ),
		required=False,
		label = "角色复杂数据"
	)

	role_objects = forms.CharField(max_length = 64, 
	widget=forms.Select(
		choices = Config.ObjectValues,
		attrs={
                "class": "form-control",
                "style": "width:100%"
            }
        ),
		required=False,
		label = "复杂数据"
	)

	role_mails = forms.CharField(max_length = 32, required=False, label = "邮件名", widget=forms.TextInput(
		attrs={'class': 'form-control', 'placeholder':u'输入邮件名字', "style": "width:98%"}))

	log_begin_time = forms.CharField(max_length = 32, required=False, label = "日志起始时间", widget=forms.TextInput(
		attrs={'class': 'form-control', 'placeholder':u'起始时间(2017-8-12 0:0:0)', "style": "width:98%"}))

	log_end_time = forms.CharField(max_length = 32, required=False, label = "日志结束时间", widget=forms.TextInput(
		attrs={'class': 'form-control', 'placeholder':u'结束时间(2017-8-12 0:0:0)', "style": "width:98%"}))

class ResultPage(forms.Form):
	val = forms.CharField(label="")

	def __init__(self, *args, **kwargs):
	 	super(ResultPage, self).__init__(args, kwargs)
	 	self.fields['val'].label = args
	 	self.fields['vdl'] = forms.CharField(label="12")
	 	


