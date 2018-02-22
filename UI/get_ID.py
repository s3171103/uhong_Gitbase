#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 19 15:03:04 2018

@author: uhong
"""

import requests

def get_ID():

    try:
        res = requests.get('http://192.168.1.105')
        return res.text
    except:
        return "Connection Filed"
