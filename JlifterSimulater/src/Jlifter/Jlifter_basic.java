package Jlifter;
import java.util.Date;

public class Jlifter_basic
{
    /**
     * 此类在物理层面模拟电梯运行
     * 指令只有上升/下降/停止
     */
    //运行指令列表
    public enum CommandList
    {
        up, down, stop
    }
    //状态相关变量
    private Date time_last;//上次收到指令的时间
    private CommandList command;//电梯当前状态：向上行或向下行或停止
    //电梯自身相关变量
    private double h;//当前电梯轿厢底部离地高度
    private double v;//速度，向上为正向下为负

    //电梯自身相关常量
    public final double vMax;//最大运行速度
    public final double a;//运行时加速度(恒定加速度)
    //电梯井相关常量
    public final int top_floor;//最高楼层
    public final int bottom_floor;//最低楼层
    public final double height_prefloor;//层高
    public final double top_altitude;//电梯井最高处有多高
    public final double bottom_altitude;//电梯井最低处有多低
    public final double top_altitude_lifter;//电梯能到的最大高度
    //运动过程相关常量
    public final double accelerate_time;
    public final double height_brake;//从最高速度减速到0经过的距离
    public final double top_brakealtitude;//顶端刹车位置=楼房最高相对高度-一层高度-刹车距离
    public final double bottom_brakealtitude;//底端刹车位置=楼房最低相对高度+刹车距离

    /**
     * 构造函数
     *
     * @param vmax         最大运行速度
     * @param acceleration 运行时加速度
     * @param h_prefloor   层高
     * @param topfloor     最高层数
     * @param bottomfloor  最低层数
     */
    Jlifter_basic(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor)
    {
        if (vmax <= 0)
            throw new IllegalArgumentException("最大运行速度必须大于0");
        if (acceleration < 0)
            throw new IllegalArgumentException("运行加速度必须大于0");
        if (h_prefloor <= 0)
            throw new IllegalArgumentException("层高必须大于0");
        if (topfloor <= bottomfloor)
            throw new IllegalArgumentException("最高楼层必须大于最低楼层");

        vMax = vmax;
        a = acceleration;
        height_prefloor = h_prefloor;
        top_floor = topfloor;
        bottom_floor = bottomfloor;

        top_altitude = top_floor * height_prefloor;
        bottom_altitude = bottom_floor * height_prefloor;
        top_altitude_lifter = top_altitude - height_prefloor;
        accelerate_time=vMax/a;
        height_brake = accelerate_time*vMax/2;
        top_brakealtitude = top_altitude_lifter - height_brake;
        bottom_brakealtitude = bottom_altitude + height_brake;

        time_last = new Date();
        command = CommandList.stop;
        h = bottom_altitude;
        v = 0;
    }


    /**
     * 设置状态
     *
     * @param height       当前高度
     * @param velocity     当前速度
     * @param acceleration 当前加速度
     * @param cmd          当前指令
     * @param time         当前时间
     */
    void setCondition(double height, double velocity, double acceleration, CommandList cmd, Date time)
    {
        if (height > top_altitude_lifter || height < bottom_altitude)
            throw new IllegalArgumentException("电梯所在位置必须在" + top_altitude_lifter + '和' + bottom_altitude + "之间");
        if (Math.abs(velocity) > vMax)
            throw new IllegalArgumentException("电梯速度绝对值必须小于等于最大运行速度" + vMax);
        if (acceleration != 0 && Math.abs(acceleration) != a)
            throw new IllegalArgumentException("电梯加速度绝对值必须为" + a + "或" + 0);
        double brakeplace = height - (Math.pow(velocity, 2)) / (2 * velocity < 0 ? a : -a);
        if (brakeplace > top_altitude_lifter || brakeplace < bottom_altitude)
            throw new IllegalArgumentException("当前状况电梯无法在电梯井内停止");
        h = height;
        v = velocity;
        time_last.setTime(time.getTime());
        command = cmd;
    }

    /**
     * 在指定时间输入指令
     *
     * @param time 指定的时间
     * @param cmd  输入的指令
     */
    void giveCommand(Date time, CommandList cmd)
    {
        if (time.before(time_last))
            throw new IllegalArgumentException("不能向上一条指令之前的时间点输入指令");
        double[] condition = getCondition(time);
        h = condition[0];
        v = condition[1];
        time_last.setTime(time.getTime());
        command = cmd;
    }

    /**
     * 计算time时刻的状态
     *
     * @param time 时刻
     * @return 返回双精度数组, 依次为位置，速度，加速度
     */
    double[] getCondition(Date time)
    {
        long tdelta = time.getTime() - time_last.getTime();
        if (tdelta < 0)
            throw new IllegalArgumentException("不能获取上一条指令之前的状态");
        switch (command)
        {
            case stop:
                return getCondition_stop(tdelta);
            case up:
                return getCondition_up(tdelta);
            case down:
                return getCondition_down(tdelta);
            default:
                throw new IllegalStateException("指令错误");
        }
    }

    /**
     * 如果上一条指令是stop,计算一段时间后的状态
     *
     * @param tdelta 指定时间段,单位毫秒
     * @return 返回双精度数组, 依次为位置，速度，加速度
     */
    private double[] getCondition_stop(long tdelta)
    {
        double[] r = {0, 0, 0};
        double t = tdelta / 1000.;
        if (v == 0)
        {
            r[0] = h;
            return r;
        }
        else if (v > 0) r[2] = -a;
        else if (v < 0) r[2] = a;
        else throw new IllegalArgumentException("速度值错误");
        double t_speed_changing = -v / r[2];
        if (t < t_speed_changing)
        {
            r[1] = v + r[2] * t;
            r[0] = h + (v + r[2] * t / 2) * t;
            return r;
        }
        else
        {
            r[1] = 0;
            r[0] = h - Math.pow(v, 2) / r[2] / 2;
            return r;
        }
    }

    /**
     * 如果上一条指令是up,计算一段时间后的状态
     *
     * @param tdelta 指定时间段,单位毫秒
     * @return 返回双精度数组, 依次为位置，速度，加速度
     */
    private double[] getCondition_up(long tdelta)
    {
        double[] r = {h, v, a};
        double t = tdelta / 1000.;
        double t_speed_up = (vMax - r[1]) / r[2];
        double x_speed_up = (vMax + r[1]) * t_speed_up / 2;
        if (r[0] + x_speed_up <= top_brakealtitude)
        {
            if (t < t_speed_up)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v) * t / 2;
                return r;
            }
            r[1] = vMax;
            r[0] += x_speed_up;
            t -= t_speed_up;
            double x_speed_constant = top_brakealtitude - r[0];
            double t_speed_constant = x_speed_constant / r[1];
            if (t < t_speed_constant)
            {
                r[0] += r[1] * t;
                return r;
            }
            r[2] = -a;
            h = top_brakealtitude;
            t -= t_speed_constant;
            double t_speed_down = -r[1] / r[2];
            if (t < t_speed_down)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + vMax) * t / 2;
                return r;
            }
            r[0] = top_altitude_lifter;
            return new double[]{r[0], 0, 0};
        }
        else
        {
            double h_to_top = top_altitude_lifter - r[0];
            double v_max = Math.sqrt(r[2] * h_to_top + r[1] * r[1] / 2);
            t_speed_up = (v_max - r[1]) / r[2];
            x_speed_up = (v_max + r[1]) * t_speed_up / 2;
            if (t < t_speed_up)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v) * t / 2;
                return r;
            }
            r[2] = -a;
            r[1] = v_max;
            r[0] += x_speed_up;
            t -= t_speed_up;
            double t_speed_down = -v_max / r[2];
            if (t < t_speed_down)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v_max) / 2 * t;
                return r;
            }
            r[0] = top_altitude_lifter;
            return new double[]{r[0], 0, 0};
        }
    }

    /**
     * 如果上一条指令是down,计算一段时间后的状态
     *
     * @param tdelta 指定时间段,单位毫秒
     * @return 返回双精度数组, 依次为位置，速度，加速度
     */
    private double[] getCondition_down(long tdelta)
    {
        double[] r = {h, v, -a};
        double t = tdelta / 1000.;
        double t_speed_up = (-vMax - r[1]) / r[2];
        double x_speed_up = (-vMax - r[1]) / 2 * t_speed_up;
        if (r[0] + x_speed_up >= bottom_brakealtitude)
        {
            if (t < t_speed_up)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v) * t / 2;
                return r;
            }
            r[2] = 0;
            r[1] = -vMax;
            r[0] += x_speed_up;
            t -= t_speed_up;
            double x_speed_constant = bottom_brakealtitude - r[0];
            double t_speed_constant = x_speed_constant / r[1];
            if (t < t_speed_constant)
            {
                r[0] += r[1] * t;
                return r;
            }
            r[2] = a;
            r[0] = bottom_brakealtitude;
            t -= t_speed_constant;
            double t_speed_down = -r[1] / r[2];
            if (t < t_speed_down)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] - vMax) * t / 2;
                return r;
            }
            r[0] = bottom_altitude;
            return new double[]{r[0], 0, 0};
        }
        else
        {
            double h_to_bottom = bottom_altitude - r[0];
            double v_max = -Math.sqrt(r[2] * h_to_bottom + r[1] * r[1] / 2);
            t_speed_up = (v_max - r[1]) / r[2];
            x_speed_up = (v_max + r[1]) * t_speed_up / 2;
            if (t < t_speed_up)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v) * t / 2;
                return r;
            }
            r[2] = a;
            r[1] = v_max;
            r[0] += x_speed_up;
            t -= t_speed_up;
            double t_speed_down = -v_max / r[2];
            if (t < t_speed_down)
            {
                r[1] += r[2] * t;
                r[0] += (r[1] + v_max) / 2 * t;
                return r;
            }
            r[0] = bottom_altitude;
            return new double[]{r[0], 0, 0};
        }
    }
}
