close all;clear all;clc; 
I=imread('image4.tif'); 
PSF=fspecial('motion',8,0);
lwnr=deconvreg(I,PSF,0);
imwrite(lwnr,'deconvreg1.png','png') 
lwnr=deconvreg(I,PSF,0.01);
imwrite(lwnr,'deconvreg2.png','png') 
lwnr=deconvreg(I,PSF,1);
imwrite(lwnr,'deconvreg3.png','png') 
lwnr=deconvreg(I,PSF,100);
imwrite(lwnr,'deconvreg4.png','png') 