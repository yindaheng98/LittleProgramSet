close all;clear all;clc; 
I=imread('image4.tif'); 
PSF=fspecial('motion',8,0);
lwnr=deconvlucy(I,PSF,10);
imwrite(lwnr,'deconvlucy1.png','png') 
lwnr=deconvlucy(I,PSF,100);
imwrite(lwnr,'deconvlucy2.png','png') 
lwnr=deconvlucy(I,PSF,200);
imwrite(lwnr,'deconvlucy3.png','png') 
lwnr=deconvlucy(I,PSF,1000);
imwrite(lwnr,'deconvlucy4.png','png') 