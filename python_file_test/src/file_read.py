#! /usr/bin/env python\
#coding=UTF-8
import os
import sys
import rospy
import shelve

datafile=shelve.open('mydata')
for i in range(2):
    temp='ps['+str(i)+']'
    point=datafile[temp]
    print point
# temp='point2'

