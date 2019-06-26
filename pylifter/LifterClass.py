import datetime
import math


class Lifter_linear_constant_a:
    """电梯模拟器，线性"""
    # 状态相关变量
    __time_last = 0  # 上次收到指令的时间
    __command_last = '停止'  # 电梯当前状态：向上行或向下行或停止

    # 运行指令列表
    __Command_list = {'上行', '下行', '停止'}

    # 电梯自身相关变量
    __h = 0  # 当前电梯轿厢底部离地高度
    __v = 0  # 速度，向上为正向下为负

    # 电梯自身相关常量
    __v_Max = 0  # 最大运行速度
    __A = 0  # 运行时加速度(恒定加速度)

    # 电梯井相关常量
    __floor_Top = 0  # 最高楼层
    __floor_Bottom = 0  # 最低楼层
    __h_Top = 0  # 电梯井最高处有多高
    __h_Bottom = 0  # 电梯井最低处有多低
    __h_perFloor = 0  # 层高
    __h_Top_lifter = 0  # 电梯能到的最大高度

    # 运动过程相关常量
    __x_Brake = 0  # 从最高速度减速到0经过的距离
    __h_Brake_top = 0  # 顶端刹车位置=楼房最高相对高度-一层高度-刹车距离
    __h_Brake_bottom = 0  # 底端刹车位置=楼房最低相对高度+刹车距离


    def __init__(self,
                 v_max,  # 最大运行速度
                 a,  # 运行时加速度
                 floor_height,  # 层高
                 top_floor,  # 最高楼层
                 bottom_floor  # 最低楼层
                 ):
        """初始化电梯和电梯井的尺寸常量"""
        if v_max <= 0:
            raise Exception('最大运行速度必须大于0')
        if a <= 0:
            raise Exception('最大运行加速度必须大于0')
        if floor_height <= 0:
            raise Exception('层高必须大于0')
        if top_floor <= bottom_floor:
            raise Exception('最高楼层必须大于最低楼层')
        self.__v_Max = v_max
        self.__A = a
        self.__h_perFloor = floor_height
        self.__floor_Top = top_floor
        self.__floor_Bottom = bottom_floor
        self.__h_Top = self.__floor_Top * self.__h_perFloor
        self.__h_Bottom = self.__floor_Bottom * self.__h_perFloor
        self.__h_Top_lifter = self.__h_Top - self.__h_perFloor
        self.__time_last = datetime.datetime.now()
        self.__x_Brake = self.__v_Max * self.__v_Max / 2 / self.__A
        self.__h_Brake_top = self.__h_Top_lifter - self.__x_Brake
        self.__h_Brake_bottom = self.__h_Bottom + self.__x_Brake


    def setCondition(self,
                     time=datetime.datetime.now(),  # 时间
                     h=0,  # 电梯所在的高度
                     v=0,  # 电梯的速度
                     a=0,  # 电梯的加速度，向上表示上行，向下表示下行
                     command='停止'  # 指令
                     ):
        """设置运行时变量(电梯当前状况+给电梯的指令)"""
        if type(time) == type(datetime.datetime):
            raise Exception('时间必须是datetime.datetime类型')
        if h > self.__h_Top_lifter or h < self.__h_Bottom:
            raise Exception('电梯所在位置必须在' + str(self.__h_Bottom) + '~' + str(self.__h_Top_lifter) + '之间')
        if abs(v) > self.__v_Max:
            raise Exception('电梯速度绝对值必须小于等于最大运行速度' + str(self.__v_Max))
        if a != 0 and abs(a) != self.__A:
            raise Exception('电梯加速度的绝对值必须为运行加速度' + str(self.__A) + '或0')
        if not (command in self.__Command_list):
            raise Exception('不存在“' + command + '”指令')
        # 计算若从此处开始刹车，在何处可以停下
        brake_h = h - (v * v) / 2 / (self.__A if v < 0 else -self.__A)
        # 若停下的位置超过电梯井范围
        if brake_h > self.__h_Top_lifter or brake_h < self.__h_Bottom:
            raise Exception('当前状况下电梯无法在电梯井内停止')
        self.__time_last = time
        self.__h = h
        self.__v = v
        self.__command_last = command


    def giveCommand(self, command, time):
        """接收运行指令"""
        if type(time) == type(datetime.datetime):
            raise Exception('时间必须是datetime.datetime类型')
        if not (command in self.__Command_list):
            raise Exception('不存在“' + command + '”指令')
        if time < self.__time_last:
            raise Exception('上次接收到指令的时间为' + self.__time_last.strftime('%Y-%m-%d %H:%M:%S') + ',不可向此时间之前发出指令')
        self.__h, self.__v, a = self.getCondition(time)
        # 更新状态
        self.__time_last = time
        self.__command_last = command
        # 更新时间和命令记录


    def __getCondition_stop(self, t):
        """如果上一条命令是停止，计算t秒后的状态"""
        # 如果就是停止的，直接返回位置，速度加速度都是0
        if self.__v == 0:
            return self.__h, 0, 0
        # 否则让加速度与速度相反，计算位置和速度
        elif self.__v > 0:
            a = -self.__A
        elif self.__v < 0:
            a = self.__A
        else:
            raise Exception('速度值非法')
        # 计算从当前速度减速至0(作匀加速运动)的时间
        t_speed_changing = -self.__v / a
        if t < t_speed_changing:  # 如果所给时间在匀变速时间内
            v = self.__v + a * t  # 速度为v0+at
            h = self.__h + (self.__v + a * t / 2) * t  # 位置为x0+(v0+1/2*at)*t
            return h, v, a
        else:  # 如果所给时间不在匀变速时间内
            v = 0  # 速度为0
            h = self.__h - (self.__v * self.__v) / 2 / a  # 位置为x0-v0^2/2a
            return h, v, a


    def __getCondition_goup(self, time):
        """如果上一条命令是上行，计算t秒后的状态,返回位置，速度，加速度"""
        a = self.__A
        v = self.__v
        h = self.__h
        t = time
        t_speed_up = (self.__v_Max - v) / a  # 从当前速度加速到最大速度(作匀加速运动)的时间
        x_speed_up = (self.__v_Max + v) / 2 * t_speed_up  # 从当前速度加速到最大速度(作匀加速运动)过程中移动的距离
        if h + x_speed_up <= self.__h_Brake_top:
            # 如果加速到最大速度还没有到上刹车位置，则v-t曲线为等腰梯形，计算出两个标志时间
            if t < t_speed_up:  # 并且在t时间时还在加速过程中，则直接算出hva
                v += a * t  # v=v0+at
                h += (v + self.__v) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            a = 0  # 经过加速时间后的状态为匀速运动
            v = self.__v_Max  # 经过加速时间后的状态为匀速运动
            h += x_speed_up
            t -= t_speed_up
            x_speed_constant = self.__h_Brake_top - h
            # 作匀速运动移动的距离就是运动到上刹车位置的距离)
            t_speed_constant = x_speed_constant / v
            # 作匀速运动的时间
            if t < t_speed_constant:  # 如果t时间时是匀速运动
                h += v * t
                return h, v, a
            a = -self.__A  # 经过匀速时间后的状态为减速运动
            # v = self.__v_Max  # 经过匀速时间后的速度不变
            h = self.__h_Brake_top  # 经过匀速运动后会运动到上刹车位
            t -= t_speed_constant
            t_speed_down = -v / a  # (0-v0)/a
            # 作匀减速运动的时间
            # x_speed_down = self.__x_Brake
            # 作匀减速运动移动的距离就是刹车距离
            if t < t_speed_down:  # 如果t时间时是匀减速运动
                v += a * t  # v=v0+at
                h += (v + self.__v_Max) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            h = self.__h_Top_lifter
            return h, 0, 0  # 如果t时间时过了匀减速运动，则说明电梯停在了最高层
        else:  # 如果加速到最大速度时过了上刹车位置，则v-t曲线为等腰三角形，计算出一个标志时间
            h_to_top = self.__h_Top_lifter - h  # 到最高处的距离
            v_max = math.sqrt(a * h_to_top + v * v / 2)
            t_speed_up = (v_max - v) / a
            x_speed_up = (v_max + v) * t_speed_up / 2
            if t < t_speed_up:
                v += a * t  # v=v0+at
                h += (v + self.__v) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            a = -self.__A  # 经过加速时间后的状态为匀减速运动
            v = v_max  # 经过加速时间后的状态为匀减速运动
            h += x_speed_up
            t -= t_speed_up
            t_speed_down = -v_max / a
            if t < t_speed_down:
                v += a * t
                h += (v + v_max) / 2 * t
                return h, v, a
            h = self.__h_Top_lifter
            return h, 0, 0  # 如果t时间时过了匀减速运动，则说明电梯停在了最高层


    def __getCondition_godown(self, t):
        """如果上一条命令是下行，计算t秒后的状态,返回位置，速度，加速度"""
        a = -self.__A
        v = self.__v
        h = self.__h
        t_speed_up = (-self.__v_Max - v) / a  # 从当前速度加速到最大速度(作匀加速运动)的时间
        x_speed_up = (-self.__v_Max - v) / 2 * t_speed_up  # 从当前速度加速到最大速度(作匀加速运动)过程中移动的距离
        if h + x_speed_up >= self.__h_Brake_bottom:
            # 如果加速到最大速度还没有到下刹车位置，则v-t曲线为等腰梯形，计算出两个标志时间
            if t < t_speed_up:  # 并且在t时间时还在加速过程中，则直接算出hva
                v += a * t  # v=v0+at
                h += (v + self.__v) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            a = 0  # 经过加速时间后的状态为匀速运动
            v = -self.__v_Max  # 经过加速时间后的状态为匀速运动
            h += x_speed_up
            t -= t_speed_up
            x_speed_constant = self.__h_Brake_bottom - h  # 作匀速运动移动的距离就是运动到下刹车位置的距离
            t_speed_constant = x_speed_constant / v  # 作匀速运动的时间
            if t < t_speed_constant:  # 如果t时间时是匀速运动
                h += v * t
                return h, v, a
            a = self.__A  # 经过匀速时间后的状态为减速运动
            # v = -self.__v_Max  # 经过匀速时间后的速度不变
            h = self.__h_Brake_bottom  # 经过匀速运动后会运动到下刹车位
            t -= t_speed_constant
            t_speed_down = -v / a  # (0-v0)/a # 作匀减速运动的时间
            # x_speed_down = self.__x_Brake
            # 作匀减速运动移动的距离就是刹车距离
            if t < t_speed_down:  # 如果t时间时是匀减速运动
                v += a * t  # v=v0+at
                h += (v - self.__v_Max) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            h = self.__h_Bottom
            return h, 0, 0  # 如果t时间时过了匀减速运动，则说明电梯停在了最底层
        else:  # 如果加速到最大速度时过了下刹车位置，则v-t曲线为等腰三角形，计算出一个标志时间
            h_to_bottom = self.__h_Bottom - h  # 到最低处的距离
            v_max = -math.sqrt(a * h_to_bottom + v * v / 2)
            t_speed_up = (v_max - v) / a
            x_speed_up = (v_max + v) * t_speed_up / 2
            if t < t_speed_up:
                v += a * t  # v=v0+at
                h += (v + self.__v) * t / 2  # h=h0+(v+v0)t/2
                return h, v, a
            a = self.__A  # 经过加速时间后的状态为匀减速运动
            v = v_max  # 经过加速时间后的状态为匀减速运动
            h += x_speed_up
            t -= t_speed_up
            t_speed_down = -v_max / a
            if t < t_speed_down:
                v += a * t
                h += (v + v_max) / 2 * t
                return h, v, a
            h = self.__h_Bottom
            return h, 0, 0  # 如果t时间时过了匀减速运动，则说明电梯停在了最高层


    def getCondition(self, time):
        """获取运行状态，返回位置，速度，加速度"""
        if type(time) == type(datetime.datetime):
            raise Exception('时间必须是datetime.datetime类型')
        if time < self.__time_last:
            raise Exception('上次接收到指令的时间为' + self.__time_last.strftime('%Y-%m-%d %H:%M:%S') + ',无法获取此时间之前的状态')
        # 计算当前时间和上次收到指令时间的时间间隔
        t = (time - self.__time_last)
        t = float(str(t.seconds) + '.' + str(t.microseconds))
        if self.__command_last == '停止':  # 如果上一条命令是停止命令，则电梯状态必为加速度与速度相反，减速停下
            return self.__getCondition_stop(t)
        elif self.__command_last == '上行':  # 如果上一条命令是上行命令，则加速度向上
            return self.__getCondition_goup(t)
        elif self.__command_last == '下行':  # 下行命令，加速度向下
            return self.__getCondition_godown(t)
