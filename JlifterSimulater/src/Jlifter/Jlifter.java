package Jlifter;

import java.util.Date;
import java.util.LinkedList;
import java.util.Queue;

/**
 * 这是一个带有基本控制单元的电梯类
 */
public abstract class Jlifter
{

    public final Jlifter_basic lifter;//物理的电梯
    private Queue<Order> orders;//运行响应队列
    private Date currenttime;//当前时间
    private int recordtime;//采样周期

    /**
     * 构造函数
     *
     * @param vmax         最大运行速度
     * @param acceleration 运行时加速度
     * @param h_prefloor   层高
     * @param topfloor     最高层数
     * @param bottomfloor  最低层数
     * @param recordt      采样周期,单位毫秒
     * @param starttime    起始时间
     */
    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor, int recordt, Date starttime)
    {
        lifter = new Jlifter_basic(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        if (Math.pow(vmax, 2) / 2 / acceleration > h_prefloor)
            throw new IllegalArgumentException("仅支持在任何楼层之间的运行都能加速到最大速度的电梯");
        orders = new LinkedList<Order>();
        currenttime = starttime;
        recordtime = recordt;
    }

    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor, int recordt)
    {
        lifter = new Jlifter_basic(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        if (Math.pow(vmax, 2) / 2 / acceleration > h_prefloor)
            throw new IllegalArgumentException("仅支持在任何楼层之间的运行都能加速到最大速度的电梯");
        orders = new LinkedList<Order>();
        currenttime = new Date();
        recordtime = recordt;
    }

    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor)
    {
        lifter = new Jlifter_basic(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        if (Math.pow(vmax, 2) / 2 / acceleration > h_prefloor)
            throw new IllegalArgumentException("仅支持在任何楼层之间的运行都能加速到最大速度的电梯");
        orders = new LinkedList<Order>();
        currenttime = new Date();
        recordtime = 1000;
    }

    public Jlifter(Jlifter_basic jb, int recordt, Date starttime)
    {
        lifter = jb;
        recordtime = recordt;
        currenttime = starttime;
    }

    /**
     * 设置采样周期
     *
     * @param recordtime 采样周期,单位毫秒
     */
    public void setRecordtime(int recordtime)
    {
        this.recordtime = recordtime;
    }

    /**
     * 设置当前状态
     *
     * @param time  当前时间
     * @param floor 当前停在哪一层
     */
    private void setCondition(Date time, int floor)
    {
        if (floor > lifter.top_floor || floor < lifter.bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        lifter.setCondition(floor * lifter.height_prefloor, 0, 0, Jlifter_basic.CommandList.stop, time);
        currenttime = new Date(time.getTime());
    }

    /**
     * 向预定队列插入数据
     *
     * @param floor    预定所在楼层
     * @param waittime 预计等待时间
     */
    public void giveOrder(int floor, long waittime)
    {
        if (floor > lifter.top_floor || floor < lifter.bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        orders.add(new Order(floor, waittime));
    }

    public void giveOrder(Order order)
    {
        if (order.floor > lifter.top_floor || order.floor < lifter.bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        orders.add(new Order(order.floor, order.waittime));
    }

    /**
     * 获取指定时间的电梯状态
     *
     * @param time 指定的时间
     * @return Status类型, 包含当前时间，当前楼层，当前位置速度加速度
     */
    public Conditions getCondition(Date time)
    {
        if (time.before(currenttime))
            throw new IllegalArgumentException("无法获取" + currenttime.toString() + "之前的电梯状态");
        return new Conditions(time, lifter.getCondition(time), lifter.height_prefloor);
    }

    public Conditions getCondition()
    {
        return new Conditions(currenttime, lifter.getCondition(currenttime), lifter.height_prefloor);
    }


    /**
     * 从预定队列中取出一个order运行一次
     */
    public void runOne()
    {
        Order order = orders.poll();
        if (order != null) run(order);
        else throw new NullPointerException("没有更多的指令可以运行");
    }

    /**
     * 运行预定队列里的所有order
     */
    public void runAll()
    {
        for (Order order = orders.poll(); order != null; order = orders.poll())
            run(order);
    }


    /**
     * 运行一个order并生成历史记录
     *
     * @param order 要运行的order
     */
    private void run(Order order)
    {
        if (order.floor > lifter.top_floor || order.floor < lifter.bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        Conditions conditions = getCondition(currenttime);
        int floor_diff = order.floor - conditions.floor;
        if (floor_diff == 0)//如果就在当前位置有预定
            runStop(order.waittime);
        else//要上或要下
            runNotStop(order, floor_diff);
    }

    /**
     * 如果不需要上行或下行
     *
     * @param waittime 等待时间
     */
    private void runStop(long waittime)
    {
        lifter.giveCommand(currenttime, Jlifter_basic.CommandList.stop);
        Date endtime = new Date(currenttime.getTime() + waittime);
        for (Date t = currenttime; t.before(endtime); t.setTime(t.getTime() + recordtime))
            setRecord(getCondition(t));
        currenttime = endtime;
    }

    /**
     * 如果需要上行或下行
     *
     * @param order      要响应的order
     * @param floor_diff 上/下楼层数
     */
    private void runNotStop(Order order, int floor_diff)
    {
        // 上行/下行时间
        long dt_run;
        long dt_stop;
        //总的移动距离
        double dh = Math.abs(floor_diff * lifter.height_prefloor);
        if (dh < 2 * lifter.height_brake)//如果运行过程到不了最大速度
        {
            dt_run = (long) (Math.sqrt(dh / lifter.a) * 1000);
            dt_stop = dt_run;
        }
        else
        {
            dt_run = (long) ((lifter.accelerate_time + (dh - lifter.height_brake * 2) / lifter.vMax) * 1000);
            dt_stop = (long) (lifter.accelerate_time * 1000);
        }

        //减速命令时间点
        Date t_stopcmd = new Date(currenttime.getTime() + dt_run);
        //停机校准时间点
        Date t_calibration = new Date(t_stopcmd.getTime() + dt_stop);
        //停止测量时间点
        Date t_end = new Date(t_calibration.getTime() + order.waittime);
        lifter.giveCommand(currenttime, floor_diff > 0 ? Jlifter_basic.CommandList.up : Jlifter_basic.CommandList.down);
        for (Date t = currenttime; t.before(t_stopcmd); t.setTime(t.getTime() + recordtime))
            setRecord(getCondition(t));
        lifter.giveCommand(t_stopcmd, Jlifter_basic.CommandList.stop);
        for (Date t = currenttime; t.before(t_calibration); t.setTime(t.getTime() + recordtime))
            setRecord(getCondition(t));
        setCondition(t_calibration, order.floor);
        for (Date t = currenttime; t.before(t_end); t.setTime(t.getTime() + recordtime))
            setRecord(getCondition(t));
        setCondition(t_end, order.floor);
    }

    /**
     * 记录，调用下面那个抽象的记录类进行记录
     *
     * @param conditions 要记录的状态
     */
    private void setRecord(Conditions conditions)
    {
        record(conditions.time, conditions.r[0], conditions.r[1], conditions.r[2], conditions.floor);
    }

    /**
     * 抽象的记录类，用于给用户自定义记录方式
     *
     * @param time  当前时间
     * @param h     电梯所在高度
     * @param v     电梯当前速度
     * @param a     电梯当前加速度
     * @param floor 电梯所在楼层
     */
    abstract protected void record(Date time, double h, double v, double a, int floor);
}
