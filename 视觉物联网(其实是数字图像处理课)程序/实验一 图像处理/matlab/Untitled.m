close all;clear all;clc; 
I=imread('image4.tif'); 
PSF=fspecial('motion',8,0);
lwnr=deconvwnr(I,PSF,0);
imwrite(lwnr,'deconvwnr1.png','png') 
lwnr=deconvwnr(I,PSF,0.01);
imwrite(lwnr,'deconvwnr2.png','png') 
lwnr=deconvwnr(I,PSF,0.1);
imwrite(lwnr,'deconvwnr3.png','png') 
lwnr=deconvwnr(I,PSF,1);
imwrite(lwnr,'deconvwnr4.png','png') 