close all;clear all;clc; 
I=imread('image4.tif'); 
PSF=fspecial('motion',8,0);
luc=deconvlucy(I,PSF);
lwnr=deconvwnr(I,PSF);
lreg=deconvreg (I,PSF);
figure
subplot(2,2,1);
imshow(I);
title('ԭʼͼ��');
subplot(2,2,2); 
imshow(luc); 
title('Lucy-Richardson�˲�');
subplot(2,2,3); 
imshow(lwnr); 
title('ά���˲�');
subplot(2,2,4); 
imshow(lreg); 
title('��Լ����С�����˲�');
