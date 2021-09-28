#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{

}

void MainPresenter::activate()
{

}

void MainPresenter::deactivate()
{

}

void MainPresenter::pbutton()
{
    model->led();
}

void MainPresenter::pbutton1()
{
    model->jsq();
}

void MainPresenter::pbutton2()
{
    model->fs();
}

void MainPresenter::shuju(uint32_t Ch1,uint16_t Ch2,uint16_t Ch3,uint16_t Ch4,uint16_t Ch5)
{
    view.setshiju( Ch1, Ch2, Ch3, Ch4, Ch5);
}
