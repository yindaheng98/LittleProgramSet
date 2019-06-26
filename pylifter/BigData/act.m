classdef act
    %电梯单次次运行数据
    properties
        data%数据
        up_down%上行还是下行
        floor_start%起始楼层
        floor_end%终止楼层
        floor_count%经过的楼层数
    end
    
    methods
        function this=act(selected_data)%将已筛选的总数据中某个转化为类
            this.floor_start=selected_data(1,8);%读起点
            [data_end,this.floor_end]=min(selected_data(:,8));
            this.floor_end=this.floor_end-1;%读终点
            this.floor_count=abs(this.floor_end-this.floor_start);%算楼层数
            this.up_down=(this.floor_start<this.floor_end);%判断上/下行
            this.data=selected_data(1:data_end,:);%传数据
        end
    end
        methods
        function prop=getProp(act)
            prop=[act.up_down,act.floor_start,act.floor_end,act.floor_count];
        end
    end

end

