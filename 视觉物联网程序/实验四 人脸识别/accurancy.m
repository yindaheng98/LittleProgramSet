function a = accurancy( testing_set,V,W,img_pj,wts,training_num )
%计算正确率
path = testing_set;
img_path = dir(strcat(path,'*.pgm'));
img_num = length(img_path);
if img_num >0
    total=0;
    testing_num=10-training_num;
    for j = 1:img_num
        img_name = img_path(j).name;
        im = imread(strcat(path, '/', img_name));
        c=classify(im,V,W,img_pj,wts);
        if floor(c/training_num)==floor(j/testing_num)
            total=total+1;
        end
        a=total/img_num;
    end
end
end

