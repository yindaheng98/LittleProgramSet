#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <BricktronicsMotor.h>

MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;             //加速度计陀螺仪原始数据
float aay = 0, agy = 0; //角度变量
long ayo = 0;             //加速度计偏移量
long gyo = 0;             //陀螺仪偏移量
void mpu_init()//传感器初始化
{
  Wire.begin();
  accelgyro.initialize();                 //传感器初始化
  unsigned short times = 200;             //采样次数
  for (int i = 0; i < times; i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //读取六轴原始数值
    ayo += ay;      //采样和
    gyo += gy;
  }
  ayo /= times;//计算加速度计偏移
  gyo /= times;//计算陀螺仪偏移
}

unsigned long now, lastTime = 0;
float dt;                                   //微分时间
void time_get()//计算时间
{
  now = millis();             //当前时间(ms)
  dt = (now - lastTime) / 1000.0;           //微分时间(s)
  lastTime = now;                           //上一次采样时间(ms)
}


float pi = 3.1415926;
float AcceRatio = 16384.0;                  //加速度计比例系数
float GyroRatio = 131.0;                    //陀螺仪比例系数
uint8_t n_sample = 8;                       //加速度计滤波算法采样个数
float aays[8] = {0};         //x,y轴采样队列
long aay_sum;                     //x,y轴采样和
float gyroy;
void mpu_get()//获取mpu数据
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //读取六轴原始数值
  float accx = ax / AcceRatio;              //x轴加速度
  float accy = ay / AcceRatio;              //y轴加速度
  float accz = az / AcceRatio;              //z轴加速度
  aay = atan(accx / accz) * 180 / pi;       //x轴对于z轴的夹角
  aay_sum = 0;                              // 对于加速度计原始数据的滑动加权滤波算法
  for (int i = 1; i < n_sample; i++)
  {
    aays[i - 1] = aays[i];
    aay_sum += aays[i] * i;
  }
  aays[n_sample - 1] = aay;                      //此处应用实验法取得合适的系数
  aay_sum += aay * n_sample;                     //本例系数为9/7
  aay = (aay_sum / (11 * n_sample / 2.0)) * 9 / 7.0; //角度调幅至0-90°
  gyroy = - (gy - gyo) / GyroRatio * dt; //y轴角速度
  agy += gyroy;                             //y轴角速度积分
}


float a_y[10] = {0}, g_y[10] = {0}; //加速度计协方差计算队列
float Py = 1, Ry, Ky, Sy, Vy, Qy = 0.01;         //y轴卡尔曼变量
void mpu_kalman()//计算Kalman滤波
{
  Sy = 0; Ry = 0;
  for (int i = 1; i < 10; i++)
  { //测量值平均值运算
    a_y[i - 1] = a_y[i];                    //即加速度平均值
    Sy += a_y[i];
  }
  a_y[9] = aay;
  Sy += aay;
  Sy /= 10;                                 //y轴加速度平均值

  for (int i = 0; i < 10; i++)
  {
    Ry += sq(a_y[i] - Sy);
  }
  Ry = Ry / 9;
  //求加速度方差
  Py = Py + Qy;                         // 0.0025在下面有说明...
  Ky = Py / (Py + Ry);                      //计算卡尔曼增益
  agy = agy + Ky * (aay - agy);             //陀螺仪角度与加速度计速度叠加
  Py = (1 - Ky) * Py;                       //更新p值
}

BricktronicsMotor m(4, 5, 10, 2, 8);
int16_t m_position_last;//上一循环的电机位置
void motor_init()//电机初始化
{
  m.begin();
  m_position_last = m.getAngle(); //获取电机初始角度
}

int16_t m_position;//电机位置
int16_t motor_difs[10] = {0}; //电机位置差
int16_t motor_dif = 0;
float m_speed = 0;
float motor_position = 0;
void motor_get()
{
  m_speed = 0;
  for (int i = 1; i < 10; i++)
  { //测量值平均值运算
    motor_difs[i - 1] = motor_difs[i];                    //即加速度平均值
    m_speed += motor_difs[i];
  }
  m_position = m.getAngle();
  motor_dif = m_position - m_position_last;
  if (motor_dif >= 180)motor_dif = motor_dif - 360;
  else if (motor_dif <= -180)motor_dif = 360 + motor_dif;
  motor_difs[9] = motor_dif;
  m_speed += motor_dif;
  m_speed /= dt * 10;
  m_position_last = m_position;
  motor_position += motor_dif; //计算马达位置
}

void motor_position_get()
{
  if (motor_position > 180) motor_position = 180;
  if (motor_position < -180) motor_position = -180;
}

float motor_speed = 0;
float m_s[10] = {0}; //电机速度协方差计算队列
float Pm = 1, Rm, Km, Sm, Vm, Qm = 100;         //卡尔曼变量
void motor_kalman()
{
  Sm = 0; Rm = 0;
  for (int i = 1; i < 10; i++)
  { //测量值平均值运算
    m_s[i - 1] = m_s[i];
    Sm += m_s[i];
  }
  m_s[9] = m_speed;
  Sm += m_speed;
  Sm /= 10;
  //求电机速度平均值

  for (int i = 0; i < 10; i++)
  {
    Rm += sq(m_s[i] - Sm);
  }
  Rm = Rm / 9;
  //求电机速度测量方差

  Pm = Pm + Qm;                         // 0.0025在下面有说明...
  Km = Pm / (Pm + Rm);                      //计算卡尔曼增益
  motor_speed = motor_speed + Km * (m_speed - motor_speed);
  Pm = (1 - Km) * Pm;                       //更新p值
}

void setup()
{
  Serial.begin(115200);
  mpu_init();
  motor_init();
}

int32_t PWM;
int16_t pwm;
void pwm_get()
{
  if (PWM >= 255)pwm = 255;
  else if (PWM <= -255)pwm = -255;
  else pwm = PWM;
  pwm = -pwm;
}

float error_I = 0;
float error_D = 0;
float error = 0;
float Imax=1500;
void Ierror()
{
  error_I += error;
  if (error_I > Imax)error_I = Imax;
  if (error_I < -Imax)error_I = -Imax;
}

float kp = 210;
float ki = 0;
float kd = 2300;
float ksp = 0;
float ksd = 0;
#define CMD_IMG 3
uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};
uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};
float send_out[3];
void loop()
{
  time_get();
  mpu_get();
  mpu_kalman();
  motor_get();
  motor_position_get();
  motor_kalman();
  error = agy - 0.236;
  Ierror();
  error_D = gyroy;

  PWM = error * kp + error_I * ki + error_D * kd + motor_position * ksp + motor_speed * ksd;
  pwm_get();
  m.setFixedDrive(pwm);

  send_out[0] = error;
  send_out[1] = (float)pwm;
  send_out[2] = error_I;
  Serial.write(cmdf[0]);
  Serial.write(cmdf[1]);
  Serial.write((char *)send_out, 3 * sizeof(float));
  Serial.write(cmdr[0]);
  Serial.write(cmdr[1]);


  //Serial.print(error);Serial.print(",");
  //Serial.print(pwm);Serial.print(",");
  //Serial.print(aay);Serial.print(",");
  //Serial.print(agy);Serial.print("\n");
  //Serial.print(gyroy); Serial.print(",");
  //Serial.print(m_speed); Serial.print(",");
  //Serial.print(motor_speed); Serial.print("\n");
  //Serial.print(motor_position); Serial.print("\n");
}
