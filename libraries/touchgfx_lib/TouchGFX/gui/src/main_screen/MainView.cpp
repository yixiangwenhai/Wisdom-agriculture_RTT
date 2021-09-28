#include <gui/main_screen/MainView.hpp>
#include <math.h>
#include <stdlib.h>

MainView::MainView()
{
    tickCounter = 0;
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();

    // Initialize graph range with default slider value at start up
    sliderValueChanged(sliderResolution.getValue());
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent()
{
    tickCounter++;

    // Insert each second tick
    if (tickCounter % 2 == 0)
    {
        float yMax = graph.getGraphRangeYMaxAsFloat();

        // Insert "random" points along a sine wave
        graph.addDataPoint((int)((sinf(tickCounter * .02f) + 1) * (yMax / 2.2f)) + rand() % (int)(yMax / 10.f));
    }
}

void MainView::sliderValueChanged(int value)
{
    // Adjust the Y-axis max value according to the slider value
    graph.setGraphRangeY(0, value);
    graph.invalidate();

    // Adjust the interval of the labels/grid lines on the Y-axis
    // to match the new range.
    if (value > 199)
    {
        graphMajorYAxisLabel.setInterval(50);
        graphMajorYAxisGrid.setInterval(50);
    }
    else if (value > 100)
    {
        graphMajorYAxisLabel.setInterval(20);
        graphMajorYAxisGrid.setInterval(20);
    }
    else
    {
        graphMajorYAxisLabel.setInterval(10);
        graphMajorYAxisGrid.setInterval(10);
    }

    graphMajorYAxisLabel.invalidate();
    graphMajorYAxisGrid.invalidate();
}

void MainView::diandeng()
{
    presenter->pbutton();
}

void MainView::jiashiqi()
{
    presenter->pbutton1();
}
void MainView::fenshan()
{
    presenter->pbutton2();
}

void MainView::setshiju(uint32_t Ch1,uint16_t Ch2,uint16_t Ch3,uint16_t Ch4,uint16_t Ch5)
{
    Unicode::snprintfFloat(textGuangZhaoBuffer, TEXTGUANGZHAO_SIZE,"%f",(float)Ch1);
    textGuangZhao.invalidate();

    Unicode::snprintfFloat(textErYangHuaTanBuffer, TEXTERYANGHUATAN_SIZE,"%.1f",(float)Ch2);
    textErYangHuaTan.invalidate();

    Unicode::snprintfFloat(textJiaQuanBuffer, TEXTJIAQUAN_SIZE,"%.1f", (float)Ch3);
    textJiaQuan.invalidate();

    Unicode::snprintfFloat(textWenDuBuffer, TEXTWENDU_SIZE,"%.2f", (float)Ch4);
    textWenDu.invalidate();


    Unicode::snprintfFloat(textShiDuBuffer, TEXTSHIDU_SIZE,"%.1f", (float)Ch5/10.0);
    textShiDu.invalidate();

}
