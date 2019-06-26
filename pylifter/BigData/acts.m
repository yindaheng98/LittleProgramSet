classdef acts
    %运行数据集
    
    properties
        data%运行数据，act数组
        count%数据量
    end
    
    methods 
        function this=acts(selected_data)
            [data_max,x,y]=size(selected_data);
            for count=1:data_max
               if selected_data(count,:,:)==zeros(x,y)
                   break;
               end
            end%计算数据量
            for i=1:count
            this.data(i)=act(selected_data(i,:,:));
            end%存数据
        end
    end
    
    methods 
        function this=acts(path)
        end
    
end

