#!/usr/bin/env python
# encoding: utf-8
"""
ratePlottingUtils.py

Created by Chris Lucas on 2012-10-10.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

import sys
import os
import ROOT as r
import math
import configuration as conf


def GetRateVal(h1=None, thresh=0):
  ibin = h1.FindBin(thresh)
  return h1.GetBinContent(ibin), h1.GetBinError(ibin)


class RatePlot(object):
  """Rate plot producer"""
  def __init__(self, hists = None, upHists = []):
    super(RatePlot, self).__init__()
    self.hists = hists
    self.upHists = upHists
    self.listColors = [r.kBlack, r.kRed, r.kBlue, r.kGreen, r.kYellow-2, r.kMagenta]
    self.xRange = []
    self.xRebin = 1
    self.Debug = False
    self.DoGrid = True
    self.PUScen = 0
    self.sampName = ""
    self.histName = ""
    self.numPlots = len(hists) + len(upHists)
    self.lg = r.TLegend()
    self.c1 = r.TCanvas()
    self.SetStyle()

  def MakeRatePlot(self):
    """docstring for MakeRatePlot"""
    self.c1.SetLogy()

    if not self.DoGrid: c1.SetGrid(kFALSE)

    self.MakeLegend()

    ctr=0
    for h, kCol in zip(self.hists, self.listColors):
      if self.Debug: print "*** Hist: ", h
      if ctr==0:
        h.Draw()
        h.GetYaxis().SetRangeUser(100,100000)
        h.GetYaxis().SetLabelSize(0.04)
        h.GetXaxis().SetTitleSize(0.04)
      h.SetLineColor(kCol)
      h.SetLineWidth(1)
      h.SetFillColor(0)
      h.Rebin(self.xRebin)
      h.DrawCopy("histsame")

      if self.xRange:
        h.GetXaxis().SetRangeUser(self.xRange[0], self.xRange[1])

      self.lg.AddEntry(h, h.GetTitle(), "L")

      ctr+=1
    
    if self.Debug: print "*** Upgrade Hist List:", self.upHists

    for uh, kCol in zip(self.upHists, self.listColors):
      if self.Debug: print "*** Upgrade Hist: ", uh
      
      uh.SetLineColor(kCol)
      uh.SetLineStyle(2)
      uh.SetFillColor(0)
      uh.DrawCopy("histsame")
      uh.SetFillColor(r.kViolet)
      uh.Draw("same")
      self.lg.AddEntry(uh, uh.GetTitle(), "L")

    self.lg.Draw()

    if self.Debug: print "*** Canvas: ", self.c1

    if conf.switches()["indivPlots"]:
      self.c1.Print("plotDump/%s_%s.png"%(self.sampName, self.histName))
    
    return self.c1
  

  def SetStyle(self):
    """docstring for SetStyle"""
    r.gStyle.SetOptStat(0)
    r.gStyle.SetOptTitle(0)
    pass


  def MakeLegend(self):
    """docstring for MakeLegend"""
    if self.numPlots <= 6:
      self.lg = r.TLegend(0.55, 0.7, 0.89, 0.89)
    elif self.numPlots > 6:
      self.lg = r.TLegend(0.55, 0.65, 0.89, 0.89)

    if self.PUScen != 0:
      self.lg.SetHeader(str(self.PUScen)+"PU Scenario")

    self.lg.SetFillColor(0)
    self.lg.SetFillStyle(0)
    self.lg.SetLineColor(0)
    self.lg.SetLineStyle(0)



class Print(object):
  """docstring for printPDF"""
  def __init__(self, Fname):
    super(Print, self).__init__()
    self.canvas = r.TCanvas()
    self.DoPageNum = True
    self.fname = Fname
    # self.rfile = r.TFile(self.fname[:-4]+".root",'RECREATE')
    self.pageCounter = 1
    self.open()


  def toFile(self,ob,title):
    """docstring for toFile"""
    # self.rfile.cd()
    # ob.SetName(title)
    # ob.SetTitle(title)
    # ob.Write()
    # ob = None
    pass

  def cd(self):
    """docstring for cd"""
    self.canvas.cd()
    pass


  def open(self, frontText = "<none>"):
    """docstring for open"""
    tpt1 = r.TText(0.07, 0.26, frontText)
    tpt2 = r.TText(0.07, 0.2, "Chris Lucas")
    tpt1.Draw()
    tpt2.Draw()
    self.canvas.Print(self.fname+"[")
    r.gPad.SetRightMargin(0.15)
    r.gPad.SetLeftMargin(0.15)
    r.gPad.SetTopMargin(0.1)
    r.gPad.SetBottomMargin(0.2)   

    pass


  def close(self):
    """docstring for close"""
    # self.rfile.Write()
    # self.rfile.Close()
    self.canvas.Print(self.fname+"]")
    pass


  def Clear(self):
    """docstring for Clear"""
    self.canvas.Clear()
    pass

  def SetLog(self,axis,BOOL):
    """docstring for SetLog"""
    if 'x' in axis:
      if BOOL:
        self.canvas.SetLogx()
      else:
        self.canvas.SetLogx(r.kFALSE)
    if 'y' in axis:
      if BOOL:
        self.canvas.SetLogy()
      else:
        self.canvas.SetLogy(r.kFALSE)
    pass

  def SetGrid(self,BOOL):
    """docstring for SetGrid"""
    if BOOL:
      self.canvas.SetGrid()
    else:
      self.canvas.SetGrid(r.kFALSE)
    pass


  def Print(self):
    """docstring for Print"""
    num = r.TLatex(0.95,0.01,"%d"%(self.pageCounter))
    num.SetNDC()
    if self.DoPageNum: num.Draw("same")
    # self.canvas.SetGridx()
    # self.canvas.SetGridy()
    self.canvas.Print(self.fname)
    self.pageCounter += 1
    pass

  def PrintCanvas(self, c1):
    """docstring for PrintCanvas"""

    self.canvas = c1

    num = r.TLatex(0.95,0.01,"%d"%(self.pageCounter))
    num.SetNDC()
    if self.DoPageNum: num.Draw("same")
    self.canvas.Print(self.fname)
    self.pageCounter += 1
    pass


###-------------------------------------------------------------------###

def getHistOrder(hList=None):
  """returns a list of the reverse order of hList"""

  maxVals = []
  myOrder = []

  for h, i in zip(hList, range( len(hList) )):
    maxVals.append(h.GetMaximum())
  tmpMax = sorted(maxVals, reverse=True)

  for i in range(len(tmpMax)):
    for k in range(len(maxVals)):
      if tmpMax[i] == maxVals[k]:
        myOrder.append(k)

  return myOrder

###-------------------------------------------------------------------###

def comparPlots(hList=None, debug=None, doLogy=False):

  sSamp = conf.comparSamps()

  if debug:
    print "comparPlots: %s"%hList[0].GetName()

  #defult colors
  #colors = [r.kRed, r.kBlue, r.kGreen, r.kCyan, r.kMagenta]
  colors = []

  #swap in specific colors
  for s in sSamp:
    colors.append( conf.samples()[s][1] )

  c1 = r.TCanvas()
  r.gStyle.SetOptStat(0)

  if len(hList)==2:
    lg = r.TLegend(0.68, 0.73, 0.895, 0.89)
  elif len(hList)==3:
    lg = r.TLegend(0.65, 0.73, 0.895, 0.89)
  elif len(hList)==4:
    lg = r.TLegend(0.64, 0.64, 0.895, 0.89)
  elif len(hList)==5:
    lg = r.TLegend(0.65, 0.61, 0.895, 0.89)

  hOrder = getHistOrder(hList)

  pd1 = r.TPad("pd1", "pd1", 0., 0.3, 1., 1.)
  pd1.SetBottomMargin(0.01)
  pd1.Draw()
  pd1.SetLogy()

  pd2 = r.TPad("pd2", "pd2", 0., 0., 1., 0.3)
  pd2.SetTopMargin(0.05)
  pd2.SetBottomMargin(0.22)
  pd2.SetGridx(1)
  pd2.SetGridy(1)
  pd2.Draw()

  pd1.cd()

  ctr=0
  for i in hOrder:
    hList[i].SetFillColor(0)
    hList[i].SetLineWidth(2)
    hList[i].SetLineColor(colors[i])
    hList[i].GetYaxis().SetRangeUser(100, 100000)
    lg.Draw()

    for key, val in conf.plots().iteritems():
      if key in hList[i].GetName():
        ranges = val["xRange"]
        hList[i].GetXaxis().SetRangeUser(ranges[0], ranges[1])
        hList[i].Rebin(val["rebinX"])

    lg.AddEntry(hList[i], sSamp[i], "L")
    if ctr==0: hList[i].DrawCopy("hist")
    else: hList[i].Draw("histsame")
    #if "up_" in hList[i].GetTitle():
    #  hList[i].SetLineStyle(2)

    
    ctr+=1

  hList[hOrder[0]].SetFillStyle(0)
  hList[hOrder[1]].SetFillStyle(0)

  lg.SetFillColor(0)
  lg.SetFillStyle(0)
  lg.SetLineColor(0)
  lg.SetLineStyle(0)
  lg.Draw()

  pd2.cd()

  hList[hOrder[0]].Divide( hList[hOrder[1]] )
  hList[hOrder[0]].SetMarkerStyle(7)
  hList[hOrder[0]].SetMarkerSize(1)
  hList[hOrder[0]].SetLineWidth(1)
  hList[hOrder[0]].SetLineColor(r.kRed)
  hList[hOrder[0]].GetXaxis().SetTitle("Threshold p_{T} / GeV")
  #hList[hOrder[0]].GetYaxis().SetTitle("Full/Fast")
  hList[hOrder[0]].GetYaxis().SetRangeUser(0,2)
  hList[hOrder[0]].SetLabelSize(0.08, "X")
  hList[hOrder[0]].SetLabelSize(0.07, "Y")
  hList[hOrder[0]].SetTitleSize(0.09, "X")
  hList[hOrder[0]].SetTitleSize(0.09, "Y")
  hList[hOrder[0]].SetTitleOffset(0.25, "Y")
  hList[hOrder[0]].Draw("pe1")
  
  c1.Print("plotDump/compare_%s.png"%(hList[0].GetName()))
  if doLogy:
    c1.SetLogy(1)
    c1.Print("plotDump/compare_%s_log.png"%(hList[0].GetName()))  

  del c1
