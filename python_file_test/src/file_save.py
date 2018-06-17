#! /usr/bin/env python\
#coding=UTF-8
import os
import sys
import rospy
import shelve
datafile=shelve.open('mydata')
point1=[1.1,2.1,3.1,4.1,5.0,6.0]
point2=[0.1,0.2,0.3,0.4,0.5,0.6]
point3=[0.2,0.2,0.3,0.4,0.5,0.6]
ps=[point1,point2]
ps.append(point3)
# print "%d"%(ps[2][0])
for i in range(2):
    temp='ps['+str(i)+']'
    datafile[temp]=ps[i]
    print i
# datafile['point2']=point2
datafile.close()
# path=os.getcwd()
# print (path)

