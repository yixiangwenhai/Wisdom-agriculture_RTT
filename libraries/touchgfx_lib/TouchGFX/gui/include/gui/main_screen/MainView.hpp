#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <stdint.h>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void diandeng();
    virtual void jiashiqi();
    virtual void fenshan();

    virtual void setshiju(uint32_t Ch1,uint16_t Ch2,uint16_t Ch3,uint16_t Ch4,uint16_t Ch5);

protected:
    int tickCounter;

    void handleTickEvent();
    virtual void sliderValueChanged(int value);
};

#endif // MAINVIEW_HPP
