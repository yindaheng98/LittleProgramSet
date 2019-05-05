import Jlifter.Jlifter;
import Jlifter.Jlifter_simulator;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Main
{
    static private Connection conn = null;
    static void writeData(String SQL)
    {
        try
        {
            Statement stmt = conn.createStatement();
            System.out.println(SQL);
            stmt.execute(SQL);
        }
        catch (SQLException ex)
        {
            // handle any errors
            System.out.println("SQLException: " + ex.getMessage());
            System.out.println("SQLState: " + ex.getSQLState());
            System.out.println("VendorError: " + ex.getErrorCode());
        }
    }
    public static void main(String[] args)
    {
        try
        {
            conn = DriverManager.getConnection("jdbc:mysql://localhost/lifter?useUnicode=true&characterEncoding=UTF-8&serverTimezone=UTC&user=root&password=");
            // The newInstance() call is a work around for some
            // broken Java implementations
            Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
            //Class.forName("com.mysql.jdbc.Driver");
        }
        catch (Exception ex)
        {
            System.out.println(ex.getMessage());
        }

        writeData("create table if not exists 响应信息" +
                "(" +
                "时间 datetime not null," +
                "楼层 int not null," +
                "等待时间 bigint not null," +
                "primary key(时间,楼层,等待时间)," +
                "index(时间)" +
                ")");
        writeData("create table if not exists 运行信息" +
                "(" +
                "时间 datetime not null," +
                "楼层 int not null," +
                "位置 double not null," +
                "速度 double not null," +
                "primary key(时间)," +
                "index(时间)" +
                ")");
        try
        {
            Jlifter jlf = new MyLifter(3, 2, 3, 15, -3);
            Jlifter_simulator jsm = new MySimulator_FCFStest(jlf);
            jsm.runSimulator();
        }
        catch (SQLException ex)
        {
            // handle any errors
            System.out.println("SQLException: " + ex.getMessage());
            System.out.println("SQLState: " + ex.getSQLState());
            System.out.println("VendorError: " + ex.getErrorCode());
        }
    }
}
