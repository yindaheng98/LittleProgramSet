classdef acts
    %�������ݼ�
    
    properties
        data%�������ݣ�act����
        count%������
    end
    
    methods 
        function this=acts(selected_data)
            [data_max,x,y]=size(selected_data);
            for count=1:data_max
               if selected_data(count,:,:)==zeros(x,y)
                   break;
               end
            end%����������
            for i=1:count
            this.data(i)=act(selected_data(i,:,:));
            end%������
        end
    end
    
    methods 
        function this=acts(path)
        end
    
end

