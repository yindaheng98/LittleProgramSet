function [weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal]=Networkinit(inputnum,outputnum,hidenum,layernum)
%����һ��������
%inputnum������λ��,outputnum�����λ��,hidenum�����ز���Ԫ����,layernum�����ز���
weightfirst=rand(hidenum,inputnum);
offsetfirst=rand(hidenum,1);
weighthide=rand(layernum,hidenum,hidenum);
offsethide=rand(hidenum,layernum);
weightfinal=rand(outputnum,hidenum);
offsetfinal=rand(outputnum,1);
end