function [weightfirst,weighthide,weightfinal]=Networkinit(inputnum,outputnum,hidenum,layernum)
%建立一个神经网络
%inputnum是输入位数,outputnum是输出位数,hidenum是隐藏层神经元个数,layernum是隐藏层数
weightfirst=rand(hidenum,inputnum);
weighthide=rand(layernum,hidenum,hidenum);
weightfinal=rand(outputnum,hidenum);
end