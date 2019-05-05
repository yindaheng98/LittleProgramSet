import Jlifter.Jlifter;

import java.sql.SQLException;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MyLifter extends Jlifter
{
    MyLifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor) throws SQLException
    {
        super(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
    }

    protected void record(Date time, double h, double v, double a, int floor)
    {
        String timestring = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(time);
        String SQL = "insert into 运行信息(时间,楼层,位置,速度)values('" + timestring + "'," + floor + "," + h + "," + v + ")";
        Main.writeData(SQL);
    }
}
