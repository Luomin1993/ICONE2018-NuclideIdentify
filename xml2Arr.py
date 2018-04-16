#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import re
import csv
import sys

def xml2str(path_xml):
    fh     = open(path_xml, "r") 
    fh_str = fh.read()
    return fh_str

def getTurple(xml_str):
    ValueAndCnt_r = re.compile(r'<Double_t (.*)/>')
    ValueAndCnt   = ValueAndCnt_r.findall(xml_str)
    cnt_r         = re.compile(r'cnt="(.*?)"')
    val_r         = re.compile(r'v="(.*?)"')
    xml_tur       = []
    for m in ValueAndCnt:
        if 'cnt=' in m:
           xml_tur.append(( float(val_r.findall(m)[0]),int(cnt_r.findall(m)[0]) ))
        else:
           xml_tur.append(( float(val_r.findall(m)[0]),1 ))
    return xml_tur

def getArr(xml_tur):
    Arr = []
    for m in xml_tur:
        Arr+=[m[0]]*m[1]
        if len(Arr)>=1500:break
    return np.array(Arr[0:1500])*10                      

def test():
    path_xml = 'Example.xml'
    Arr = getArr(getTurple(xml2str(path_xml)))
    print len(np.array(Arr)*10)
    print np.array(Arr)*10
    print len(Arr)


def writeToCsv(Arr,way):
    csvFile = open(way,'w') # 设置newline，否则两行之间会空一行
    writer = csv.writer(csvFile)
    for m in Arr:
        writer.writerow([str(m)])
    csvFile.close()

if __name__ == '__main__':
    #test()    
    writeToCsv(getArr(getTurple(xml2str(sys.argv[1]+'.xml'))),sys.argv[1]+'.csv')

    
