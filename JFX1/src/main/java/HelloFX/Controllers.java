package HelloFX;

import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.Initializable;
import javafx.scene.control.Slider;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Polyline;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.util.Duration;

import java.net.URL;
import java.util.*;

public class Controllers implements Initializable
{
    public Text flowNum1;
    public Text flowNum2;
    public Text flowNum3;
    public List<Text> flowNums = new ArrayList<>(3);

    public Text h1Text;
    public Text h2Text;
    public Text h3Text;
    public List<Text> hTexts = new ArrayList<>(3);

    public Text p1Text;
    public Text p2Text;
    public Text p3Text;
    public List<Text> pTexts = new ArrayList<>(3);

    public Text outText1;
    public Text outText2;

    public Slider valveSliderp;
    public Slider valveSliderh;

    public Rectangle liquidRectangle1;
    public Rectangle liquidRectangle2;
    public Rectangle liquidRectangle3;
    public List<Rectangle> liquidRectangle = new ArrayList<Rectangle>(3);

    public Polyline pArrow1;
    public Polyline pArrow2;
    public Polyline pArrow3;

    public Polyline lArrow1;
    public Polyline lArrow2;
    public Polyline lArrow3;

    public Polyline lArrow01;
    public Polyline lArrow02;
    public Polyline lArrow03;

    public Line lPath11;
    public Line lPath12;
    public Line lPath13;
    public double[][] lPath1 = new double[4][2];
    public Line lPath21;
    public Line lPath22;
    public Line lPath23;
    public Line lPath24;
    public Line lPath25;
    public double[][] lPath2 = new double[6][2];
    public Line lPath31;
    public Line lPath32;
    public Line lPath33;
    public Line lPath34;
    public double[][] lPath3 = new double[5][2];
    public Line lPath0a;
    public Line lPath0b;
    public double[][] lPath01 = new double[2][2];
    public double[][] lPath02 = new double[2][2];
    public double[][] lPath03 = new double[2][2];


    public Line pPath11;
    public double[][] pPath1 = new double[2][2];
    public Line pPath21;
    public double[][] pPath2 = new double[2][2];
    public Line pPath31;
    public Line pPath32;
    public double[][] pPath3 = new double[3][2];

    public double maxHeight1;
    public double maxHeight2;
    public double maxHeight3;
    double[] maxHeights = new double[3];
    public double duration = 1000;

    public double hMax;
    public double pMax;
    public double pMin;


    private List<Timeline> timelines = new Vector<>();

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        flowNums.add(flowNum1);
        flowNums.add(flowNum2);
        flowNums.add(flowNum3);
        hTexts.add(h1Text);
        hTexts.add(h2Text);
        hTexts.add(h3Text);
        pTexts.add(p1Text);
        pTexts.add(p2Text);
        pTexts.add(p3Text);
        liquidRectangle.add(liquidRectangle1);
        liquidRectangle.add(liquidRectangle2);
        liquidRectangle.add(liquidRectangle3);
        maxHeight1 = liquidRectangle1.getHeight();
        maxHeight2 = liquidRectangle2.getHeight();
        maxHeight3 = liquidRectangle3.getHeight();
        maxHeights[0] = maxHeight1;
        maxHeights[1] = maxHeight2;
        maxHeights[2] = maxHeight3;
        hMax = valveSliderh.getMax();
        pMax = valveSliderp.getMax();
        pMin = valveSliderp.getMin();

        lPath01[0][0] = lPath0a.getLayoutX() + lPath0a.getStartX();
        lPath01[0][1] = lPath0a.getLayoutY() + lPath0a.getStartY();
        lPath01[1][0] = lPath0a.getLayoutX() + lPath0a.getEndX();
        lPath01[1][1] = lPath0a.getLayoutY() + lPath0a.getEndY();

        lPath02[0][0] = lPath0a.getLayoutX() + lPath0a.getEndX();
        lPath02[0][1] = lPath0a.getLayoutY() + lPath0a.getEndY();
        lPath02[1][0] = lPath0b.getLayoutX() + lPath0b.getStartX();
        lPath02[1][1] = lPath0b.getLayoutY() + lPath0b.getStartY();

        lPath03[0][0] = lPath0a.getLayoutX() + lPath0a.getEndX();
        lPath03[0][1] = lPath0a.getLayoutY() + lPath0a.getEndY();
        lPath03[1][0] = lPath0b.getLayoutX() + lPath0b.getEndX();
        lPath03[1][1] = lPath0b.getLayoutY() + lPath0b.getEndY();

        lPath1[0][0] = lPath11.getLayoutX() + lPath11.getStartX();
        lPath1[0][1] = lPath11.getLayoutY() + lPath11.getStartY();
        lPath1[1][0] = lPath12.getLayoutX() + lPath12.getStartX();
        lPath1[1][1] = lPath12.getLayoutY() + lPath12.getStartY();
        lPath1[2][0] = lPath13.getLayoutX() + lPath13.getStartX();
        lPath1[2][1] = lPath13.getLayoutY() + lPath13.getStartY();
        lPath1[3][0] = lPath13.getLayoutX() + lPath13.getEndX();
        lPath1[3][1] = lPath13.getLayoutY() + lPath13.getEndY();


        lPath2[0][0] = lPath21.getLayoutX() + lPath21.getStartX();
        lPath2[0][1] = lPath21.getLayoutY() + lPath21.getStartY();
        lPath2[1][0] = lPath22.getLayoutX() + lPath22.getStartX();
        lPath2[1][1] = lPath22.getLayoutY() + lPath22.getStartY();
        lPath2[2][0] = lPath23.getLayoutX() + lPath23.getStartX();
        lPath2[2][1] = lPath23.getLayoutY() + lPath23.getStartY();
        lPath2[3][0] = lPath24.getLayoutX() + lPath24.getStartX();
        lPath2[3][1] = lPath24.getLayoutY() + lPath24.getStartY();
        lPath2[4][0] = lPath25.getLayoutX() + lPath25.getStartX();
        lPath2[4][1] = lPath25.getLayoutY() + lPath25.getStartY();
        lPath2[5][0] = lPath25.getLayoutX() + lPath25.getEndX();
        lPath2[5][1] = lPath25.getLayoutY() + lPath25.getEndY();

        lPath3[0][0] = lPath31.getLayoutX() + lPath31.getStartX();
        lPath3[0][1] = lPath31.getLayoutY() + lPath31.getStartY();
        lPath3[1][0] = lPath32.getLayoutX() + lPath32.getStartX();
        lPath3[1][1] = lPath32.getLayoutY() + lPath32.getStartY();
        lPath3[2][0] = lPath33.getLayoutX() + lPath33.getStartX();
        lPath3[2][1] = lPath33.getLayoutY() + lPath33.getStartY();
        lPath3[3][0] = lPath34.getLayoutX() + lPath34.getStartX();
        lPath3[3][1] = lPath34.getLayoutY() + lPath34.getStartY();
        lPath3[4][0] = lPath34.getLayoutX() + lPath34.getEndX();
        lPath3[4][1] = lPath34.getLayoutY() + lPath34.getEndY();

        pPath1[0][0] = pPath11.getLayoutX() + pPath11.getStartX();
        pPath1[0][1] = pPath11.getLayoutY() + pPath11.getStartY();
        pPath1[1][0] = pPath11.getLayoutX() + pPath11.getEndX();
        pPath1[1][1] = pPath11.getLayoutY() + pPath11.getEndY();

        pPath2[0][0] = pPath21.getLayoutX() + pPath21.getStartX();
        pPath2[0][1] = pPath21.getLayoutY() + pPath21.getStartY();
        pPath2[1][0] = pPath21.getLayoutX() + pPath21.getEndX();
        pPath2[1][1] = pPath21.getLayoutY() + pPath21.getEndY();

        pPath3[0][0] = pPath31.getLayoutX() + pPath31.getStartX();
        pPath3[0][1] = pPath31.getLayoutY() + pPath31.getStartY();
        pPath3[1][0] = pPath32.getLayoutX() + pPath32.getStartX();
        pPath3[1][1] = pPath32.getLayoutY() + pPath32.getStartY();
        pPath3[2][0] = pPath32.getLayoutX() + pPath32.getEndX();
        pPath3[2][1] = pPath32.getLayoutY() + pPath32.getEndY();
    }

    public void valveValueChange()
    {
        lArrow1.setLayoutX(lPath1[0][0]);
        lArrow1.setLayoutY(lPath1[0][1]);
        lArrow2.setLayoutX(lPath2[0][0]);
        lArrow2.setLayoutY(lPath2[0][1]);
        lArrow3.setLayoutX(lPath3[0][0]);
        lArrow3.setLayoutY(lPath3[0][1]);
        pArrow1.setLayoutX(pPath1[0][0]);
        pArrow1.setLayoutY(pPath1[0][1]);
        pArrow2.setLayoutX(pPath2[0][0]);
        pArrow2.setLayoutY(pPath2[0][1]);
        pArrow3.setLayoutX(pPath3[0][0]);
        pArrow3.setLayoutY(pPath3[0][1]);
        double[] p = new double[4];
        double[] h = new double[4];
        double[] f = new double[4];
        double[] vl = new double[4];
        double[] vout = new double[2];
        double[] vp = new double[4];
        vl[0] = valveSliderh.getValue();
        p[0] = valveSliderp.getValue();

        h[1] = vl[0] / 1.4;
        vl[1] = 1.2 * h[1];

        h[3] = vl[1] / 1.4;
        vl[3] = 1.2 * h[3];

        h[2] = vl[3] / 1.4;
        vl[2] = 1.2 * h[2];

        p[3] = (100 * p[0] + h[3]) / 101;
        p[2] = (100 * p[3] + h[2]) / 101;
        p[1] = (100 * p[2] + h[1]) / 101;
        vp[0] = p[0] - p[3] + hMax * 0.1;
        vp[3] = p[3] - p[2] + hMax * 0.1;
        vp[2] = p[2] - p[1] + hMax * 0.1;

        vout[0] = vl[2] * Math.min(p[2], h[2])*2 / (p[2] + h[2]);
        vout[1] = vl[2] * Math.abs(p[2] - h[2]) / (p[2] + h[2]);

        f[0] = vl[1];
        f[1] = vl[2];
        f[2] = vl[3];

        outText1.setText(String.format("%.6f", vout[0]));
        outText2.setText(String.format("%.6f", vout[1]));
        for (int i = 1; i <= 3; i++)
        {
            bucketMove(i - 1, h[i], p[i]);
            flowNums.get(i - 1).setText(String.format("%.6f", f[i - 1]));
        }
        for (Timeline timeline : timelines)
            timeline.stop();
        timelines.clear();
        arrowUpdate(lArrow1, vl[0] / 100, lPath1);
        arrowUpdate(lArrow2, vl[3] / 100, lPath2);
        arrowUpdate(lArrow3, vl[1] / 100, lPath3);
        arrowUpdate(pArrow1, vp[2] / 100, pPath1);
        arrowUpdate(pArrow2, vp[3] / 100, pPath2);
        arrowUpdate(pArrow3, vp[0] / 100, pPath3);
        arrowUpdate(lArrow01, vl[2] / 100, lPath01);
        arrowUpdate(lArrow02, vout[0] / 100, lPath02);
        arrowUpdate(lArrow03, vout[1] / 100, lPath03);
    }

    private void bucketMove(int which, double h_to, double p_to)
    {
        Rectangle lqRect = liquidRectangle.get(which);
        double hRect = maxHeights[which] * (1 - h_to / hMax);
        KeyValue kv_hRect = new KeyValue(lqRect.heightProperty(), hRect);
        int colorParam = (int) ((p_to - pMin) * 255 / (pMax - pMin));
        Color colorRect = Color.rgb(colorParam, 0, 255 - colorParam);
        KeyValue kv_colorRect = new KeyValue(lqRect.fillProperty(), colorRect);

        Text hText = hTexts.get(which);
        double yText = lqRect.getY() - maxHeights[which] + hRect;
        KeyValue kv_yText = new KeyValue(hText.yProperty(), yText);
        KeyValue kv_h = new KeyValue(hText.textProperty(), String.format("h=%.6f", h_to/10));

        Text pText = pTexts.get(which);
        KeyValue kv_p = new KeyValue(pText.textProperty(), String.format("p=%.6f", p_to));

        Timeline timeline = new Timeline();
        KeyFrame keyFrame = new KeyFrame(Duration.millis(duration), kv_hRect, kv_colorRect, kv_yText, kv_h, kv_p);
        timeline.getKeyFrames().add(keyFrame);
        timeline.play();
    }

    private void arrowUpdate(Polyline arrow, double v, double[][] path)
    {
        arrow.setLayoutX(path[0][0]);
        arrow.setLayoutY(path[0][1]);
        arrowUpdate(arrow, v, path, 1);
    }


    private void arrowUpdate(Polyline arrow, double v, double[][] path, int i)
    {
        if (i >= path.length)
        {
            i = 1;
            arrow.setLayoutX(path[0][0]);
            arrow.setLayoutY(path[0][1]);
        }
        Timeline timeline = new Timeline();
        double vx = path[i][0] - path[i - 1][0];
        double vy = path[i][1] - path[i - 1][1];
        double rotate = Math.atan2(vy, vx) / Math.PI * 180 + 90;
        KeyValue keyValueR = new KeyValue(arrow.rotateProperty(), rotate);
        KeyValue keyValueX = new KeyValue(arrow.layoutXProperty(), path[i][0]);
        KeyValue keyValueY = new KeyValue(arrow.layoutYProperty(), path[i][1]);
        final int ii = i + 1;
        EventHandler<ActionEvent> nextAnmition = event -> arrowUpdate(arrow, v, path, ii);
        KeyFrame keyFrameR = new KeyFrame(Duration.millis(1), keyValueR);
        KeyFrame keyFrame = new KeyFrame(Duration.millis(Math.sqrt(vx * vx + vy * vy) / v), nextAnmition, keyValueX, keyValueY);
        timeline.getKeyFrames().addAll(keyFrameR, keyFrame);
        timeline.play();
        timelines.add(timeline);
    }
}
