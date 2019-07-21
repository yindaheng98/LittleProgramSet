%step2;
faces=zeros(112,92,0);
for i=1:size(V,2)
    temp=V(:,i);
    faces(:,:,end+1)=mapminmax(reshape(temp,[112,92]),0,1);
end
for i=1:9
    subplot(3,3,i)
    imshow(faces(:,:,i));
    title(sprintf('ÌØÕ÷Á³%d',i))
end
