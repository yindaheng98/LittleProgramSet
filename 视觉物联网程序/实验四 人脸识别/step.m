clear;
pathfrom='images';
training_num=5;
training_set='sets/training/';
testing_set='sets/testing/';
setdivi(pathfrom,training_num,training_set,testing_set);
[ V,W,img_pj,wts ] = train( training_set );

faces=zeros(112,92,0);
for i=1:size(V,2)
    temp=V(:,i);
    faces(:,:,end+1)=mapminmax(reshape(temp,[112,92]),0,1);
end
for i=1:9
    subplot(3,3,i)
    imshow(faces(:,:,i));
    title(sprintf('特征脸%d',i))
end

test( [testing_set,'001.pgm'],training_set,V,W,img_pj,wts );

a=accurancy(testing_set,V,W,img_pj,wts,training_num);

fprintf('正确率为%f\n',a);