#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void led();

    void jsq();

    void fs();

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
