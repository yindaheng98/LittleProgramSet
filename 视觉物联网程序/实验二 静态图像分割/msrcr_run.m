pathname='data/img2.jpg';
d=2.5;
nscals=100;
maxscals=100;

img = imread(pathname);
result = msrcr(img,d,nscals,maxscals);
imshow(result)

imwrite(result,'msrcr/img2.jpg')