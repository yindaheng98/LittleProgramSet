function [weightfirst,weighthide,weightfinal]=Networkinit(inputnum,outputnum,hidenum,layernum)
%����һ��������
%inputnum������λ��,outputnum�����λ��,hidenum�����ز���Ԫ����,layernum�����ز���
weightfirst=rand(hidenum,inputnum);
weighthide=rand(layernum,hidenum,hidenum);
weightfinal=rand(outputnum,hidenum);
end