classdef act
    %���ݵ��δ���������
    properties
        data%����
        up_down%���л�������
        floor_start%��ʼ¥��
        floor_end%��ֹ¥��
        floor_count%������¥����
    end
    
    methods
        function this=act(selected_data)%����ɸѡ����������ĳ��ת��Ϊ��
            this.floor_start=selected_data(1,8);%�����
            [data_end,this.floor_end]=min(selected_data(:,8));
            this.floor_end=this.floor_end-1;%���յ�
            this.floor_count=abs(this.floor_end-this.floor_start);%��¥����
            this.up_down=(this.floor_start<this.floor_end);%�ж���/����
            this.data=selected_data(1:data_end,:);%������
        end
    end
        methods
        function prop=getProp(act)
            prop=[act.up_down,act.floor_start,act.floor_end,act.floor_count];
        end
    end

end

