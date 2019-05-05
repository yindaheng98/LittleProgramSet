package Jlifter;

import java.util.Date;

/**
 * 存储电梯状态信息的类
 * 只用在getCondition函数的返回值中
 */
public class Conditions
{
    public final double[] r;
    public final int floor;
    public final Date time;

    Conditions(Date currenttime, double[] r,double height_prefloor)
    {
        time = currenttime;
        this.r = r;
        floor = (int) (r[0] / height_prefloor);
    }
}
