for i=1:MAX
    input=rand(INPUTN,1);
    output=test_func(input,INPUTN);
    nw=nw.BackPropagation(input,output,LearningDegree);
    %y(:,i,k)=min(nw.costs,0.5);
    y(:,i,k)=nw.costs;
end

for i=1:OUTPUTN
    subplot(1,OUTPUTN,i);
    for k=1:K
        hold on;
        plot(x,y(i,:,k));
    end
end
nw.record('record.txt');