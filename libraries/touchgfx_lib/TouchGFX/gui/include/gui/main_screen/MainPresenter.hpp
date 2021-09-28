#ifndef MAINPRESENTER_HPP
#define MAINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <stdint.h>

using namespace touchgfx;

class MainView;

class MainPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainPresenter(MainView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainPresenter() {};

    virtual void pbutton();

    virtual void pbutton1();

    virtual void pbutton2();

    virtual void shuju(uint32_t Ch1,uint16_t Ch2,uint16_t Ch3,uint16_t Ch4,uint16_t Ch5);

private:
    MainPresenter();

    MainView& view;
};

#endif // MAINPRESENTER_HPP
