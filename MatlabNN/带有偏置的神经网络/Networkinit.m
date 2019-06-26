function [weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal]=Networkinit(inputnum,outputnum,hidenum,layernum)
%建立一个神经网络
%inputnum是输入位数,outputnum是输出位数,hidenum是隐藏层神经元个数,layernum是隐藏层数
weightfirst=rand(hidenum,inputnum);
offsetfirst=rand(hidenum,1);
weighthide=rand(layernum,hidenum,hidenum);
offsethide=rand(hidenum,layernum);
weightfinal=rand(outputnum,hidenum);
offsetfinal=rand(outputnum,1);
end