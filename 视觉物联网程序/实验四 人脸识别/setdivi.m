function setdivi(pathfrom,training_num,training_set,testing_set)
%’˚¿ÌÕº∆¨
n = 1;
p=1;
try
rmdir(training_set, 's');
catch
end
try
rmdir(testing_set, 's');
catch
end
mkdir(training_set);
mkdir(testing_set);
for i=1:40
    a=1:10;
    Ind = a(:,randperm(size(a,2)));
    for h = 1:training_num
        j=  Ind(1,h);
        File=[pathfrom,'\s',sprintf('%d',i),'\',sprintf('%d',j),'.pgm'];
        Filesave=[training_set,sprintf('%03d',n),'.pgm'];
        copyfile(File,Filesave)
        n = n + 1;
    end
    for h = training_num+1:10
        j=  Ind(1,h);
        File=[pathfrom,'\s',sprintf('%d',i),'\',sprintf('%d',j),'.pgm'];
        Filesave=[testing_set,sprintf('%03d',p),'.pgm'];
        copyfile(File,Filesave)
        p = p + 1;
    end
end
end

